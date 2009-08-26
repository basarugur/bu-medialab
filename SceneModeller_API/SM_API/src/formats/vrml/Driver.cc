/**
 * VRML 1.0c Parser
 * Copyright (C) 2007  Wilfried Holzke
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2
 * of the License only.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include "Driver.hh"
#include "vrml1-parser.hh"

namespace vrml1 {

Driver::Driver() : trace_scanning (false), trace_parsing (false)
{
	m_Error = false;
	m_VRML1Doc = 0;
	m_StackRoot = new SubStack(0);
	m_Stack = m_StackRoot;
}

Driver::~Driver()
{
	m_Stack = 0;
	delete m_StackRoot;
}

void Driver::parse (const std::string &f) {

	file = f;
	scan_begin ();
	vrml1_parser parser (*this);
	parser.set_debug_level (trace_parsing);
	parser.parse ();
	scan_end ();
}
     
void Driver::error (const vrml1::location& l, const std::string& m) {
	m_Error = true;
	std::cerr << l << ": " << m << std::endl;
}
     
void Driver::error (const std::string& m) {
	m_Error = true;
	std::cerr << m << std::endl;
}

Document* Driver::getVRML1Doc() {
	
	Document *doc = m_VRML1Doc;
	m_VRML1Doc = 0;
	
	return doc;
}

void Driver::pushVRMLDoc() {

	m_VRML1Doc = new Document();
	
	Node *N = 0;
	while ((N = m_Stack->getFirstNode()) != 0) {
		m_VRML1Doc->addNode(N);
	}
	
}

void Driver::pushNodeSeparator() {
	m_Stack->pushNodeSeparator();
}

void Driver::pushNodeSwitch() {
	m_Stack->pushNodeSwitch();
}

void Driver::pushNodeCube() {
	m_Stack->pushNodeCube();
}

void Driver::pushNodeCone() {
	m_Stack->pushNodeCone();
}

void Driver::pushNodeSphere() {
	m_Stack->pushNodeSphere();
}

void Driver::pushNodeCylinder() {
	m_Stack->pushNodeCylinder();
}

void Driver::pushNodeMaterial() {
	m_Stack->pushNodeMaterial();
}

void Driver::pushNodeMaterialBinding() {
	m_Stack->pushNodeMaterialBinding();
}

void Driver::pushNodeTranslation() {
	m_Stack->pushNodeTranslation();
}

void Driver::pushNodeRotation() {
	m_Stack->pushNodeRotation();
}

void Driver::pushNodeScale() {
	m_Stack->pushNodeScale();
}

void Driver::pushNodeMatrixTransform() {
	m_Stack->pushNodeMatrixTransform();
}

void Driver::pushNodeTransform() {
	m_Stack->pushNodeTransform();
}

void Driver::pushNodeOrthographicCamera() {
	m_Stack->pushNodeOrthographicCamera();
}

void Driver::pushNodePerspectiveCamera() {
	m_Stack->pushNodePerspectiveCamera();
}

void Driver::pushNodePointLight() {
	m_Stack->pushNodePointLight();
}

void Driver::pushNodeSpotLight() {
	m_Stack->pushNodeSpotLight();
}

void Driver::pushNodeDirectionalLight() {
	m_Stack->pushNodeDirectionalLight();
}

void Driver::pushNodeTexture2Transform() {
	m_Stack->pushNodeTexture2Transform();
}

void Driver::pushNodeShapeHints() {
	m_Stack->pushNodeShapeHints();
}

void Driver::pushNodeNormalBinding() {
	m_Stack->pushNodeNormalBinding();
}

void Driver::pushNodeFontStyle() {
	m_Stack->pushNodeFontStyle();
}

void Driver::pushNodeLOD() {
	m_Stack->pushNodeLOD();
}

void Driver::pushNodeNormal() {
	m_Stack->pushNodeNormal();
}

void Driver::pushNodeCoordinate3() {
	m_Stack->pushNodeCoordinate3();
}

void Driver::pushNodeTextureCoordinate2() {
	m_Stack->pushNodeTextureCoordinate2();
}

void Driver::pushNodePointSet() {
	m_Stack->pushNodePointSet();
}

void Driver::pushNodeIndexedLineSet() {
	m_Stack->pushNodeIndexedLineSet();
}

void Driver::pushNodeIndexedFaceSet() {
	m_Stack->pushNodeIndexedFaceSet();
}

void Driver::pushNodeTexture2() {
	m_Stack->pushNodeTexture2();
}

void Driver::pushNodeWWWInline() {
	m_Stack->pushNodeWWWInline();
}

void Driver::pushNodeWWWAnchor() {
	m_Stack->pushNodeWWWAnchor();
}

void Driver::pushNodeAsciiText() {
	m_Stack->pushNodeAsciiText();
}

bool Driver::pushDEF() {

	bool ret = true; 
	
	string id = m_Stack->popString();

	if (m_DefMap.find(id) == m_DefMap.end()) {
		
		m_DefMap[id] = m_Stack->lastNode();
	} else {
		ret = false;
	}
	
	return ret;
}

bool Driver::pushUSE() {

	bool ret = true;

	string id = m_Stack->popString();
	
	if (m_DefMap.find(id) != m_DefMap.end()) {
		
		m_Stack->pushNodeUse(id);
	} else {
		ret = false;
	}
	
	return ret;
}

bool Driver::pushAttributeSFImage(string name) {
	return m_Stack->pushAttributeSFImage(name);
}

void Driver::pushAttributeSFString(string name) {
	m_Stack->pushAttributeSFString(name);
}

void Driver::pushAttributeSFBitmask(string name) {
	m_Stack->pushAttributeSFBitmask(name);
}

void Driver::pushAttributeSFMatrix(string name) {
	m_Stack->pushAttributeSFMatrix(name);
}

void Driver::pushAttributeSFRotation(string name) {
	m_Stack->pushAttributeSFRotation(name);
}

void Driver::pushAttributeSFVec2f(string name) {
	m_Stack->pushAttributeSFVec2f(name);
}

void Driver::pushAttributeMFVec2f(string name) {
	m_Stack->pushAttributeMFVec2f(name);
}

void Driver::pushAttributeSFVec3f(string name) {
	m_Stack->pushAttributeSFVec3f(name);
}

void Driver::pushAttributeMFVec3f(string name) {
	m_Stack->pushAttributeMFVec3f(name);
}

void Driver::pushAttributeSFColor(string name) {
	m_Stack->pushAttributeSFColor(name);
}

void Driver::pushAttributeMFColor(string name) {
	m_Stack->pushAttributeMFColor(name);
}

void Driver::pushAttributeSFFloat(string name) {
	m_Stack->pushAttributeSFFloat(name);
}

void Driver::pushAttributeMFFloat(string name) {
	m_Stack->pushAttributeMFFloat(name);
}

void Driver::pushAttributeSFLong(string name) {
	m_Stack->pushAttributeSFLong(name);
}

void Driver::pushAttributeMFLong(string name) {
	m_Stack->pushAttributeMFLong(name);
}

void Driver::pushAttributeSFBool(string name) {
	m_Stack->pushAttributeSFBool(name);
}

void Driver::pushString(string s) {
	m_Stack->pushString(s);
}

void Driver::pushFloat(float f) {
	m_Stack->pushFloat(f);
}

void Driver::pushInteger(int i) {
	m_Stack->pushInteger(i);
}

void Driver::pushBool(bool b) {
	m_Stack->pushBool(b);
}

void Driver::StackDown() {
	m_Stack = m_Stack->down();
}

void Driver::StackUp() {
	m_Stack = m_Stack->up();
}

}
