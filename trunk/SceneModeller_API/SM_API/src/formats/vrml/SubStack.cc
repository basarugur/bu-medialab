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

#include <iostream>
#include "SFMatrix.hh"
#include "SFVec2f.hh"
#include "SFImage.hh"
#include "SubStack.hh"
#include "Separator.hh"
#include "Switch.hh"
#include "USE.hh"
#include "Cube.hh"
#include "Cone.hh"
#include "Sphere.hh"
#include "Cylinder.hh"
#include "Material.hh"
#include "MaterialBinding.hh"
#include "Translation.hh"
#include "Rotation.hh"
#include "Scale.hh"
#include "MatrixTransform.hh"
#include "Transform.hh"
#include "OrthographicCamera.hh"
#include "PerspectiveCamera.hh"
#include "PointLight.hh"
#include "SpotLight.hh"
#include "DirectionalLight.hh"
#include "Texture2Transform.hh"
#include "ShapeHints.hh"
#include "NormalBinding.hh"
#include "FontStyle.hh"
#include "LOD.hh"
#include "Normal.hh"
#include "Coordinate3.hh"
#include "TextureCoordinate2.hh"
#include "PointSet.hh"
#include "IndexedLineSet.hh"
#include "IndexedFaceSet.hh"
#include "Texture2.hh"
#include "WWWInline.hh"
#include "WWWAnchor.hh"
#include "AsciiText.hh"


using namespace std;

namespace vrml1 {

SubStack::SubStack(SubStack *Parent)
{
	m_Parent = Parent;
	m_Child = 0;
}

SubStack::~SubStack()
{
	for (int i=0; i<m_Nodes.size(); i++) {
		if (m_Nodes.at(i) != 0) {
			delete m_Nodes.at(i);
		}	
	}
	
	for (int i=0; i<m_Attributes.size(); i++) {
		if (m_Attributes.at(i) != 0) {
			delete m_Attributes.at(i);
		}
	}
	
	if (m_Child != 0) delete m_Child;
}

SubStack* SubStack::up() {
	return m_Parent;
}

SubStack* SubStack::down() {
	if (m_Child == 0) {
		m_Child = new SubStack(this);	
	} 
	
	return m_Child;
}

void SubStack::pushNodeSeparator() {

	Separator *S = new Separator();
	
	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
	
		S->setAttribute(A);
		delete A;
	}

	Node *N;	
	while ((N = m_Child->getFirstNode()) != 0) {
		
		S->addNode(N);
	}
	
	m_Nodes.push_back(S);	
}

void SubStack::pushNodeSwitch() {
	
	Switch *S = new Switch();
	
	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
	
		S->setAttribute(A);
		delete A;
	}

	Node *N;	
	while ((N = m_Child->getFirstNode()) != 0) {
		
		S->addNode(N);
	}

	m_Nodes.push_back(S);
}

void SubStack::pushNodeUse(string id) {
	USE *U = new USE();
	
	U->setId(id);
	
	m_Nodes.push_back(U);
}

void SubStack::pushNodeCube() {
	Cube *C = new Cube();
	
	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		C->setAttribute(A);
		delete A;
	}
	
	m_Nodes.push_back(C);
}

void SubStack::pushNodeCone() {
	Cone *C = new Cone();
	
	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		C->setAttribute(A);
		delete A;
	}
	
	m_Nodes.push_back(C);
}

void SubStack::pushNodeSphere() {
	Sphere *S = new Sphere();
	
	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		S->setAttribute(A);
		delete A;
	}
	
	m_Nodes.push_back(S);
}

void SubStack::pushNodeCylinder() {
	Cylinder *C = new Cylinder();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		C->setAttribute(A);
		delete A;
	}
	
	m_Nodes.push_back(C);
}

void SubStack::pushNodeMaterial() {
	
	Material *M = new Material();
	
	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		M->setAttribute(A);
		delete A;
	}
	
	m_Nodes.push_back(M);
}

void SubStack::pushNodeMaterialBinding() {
	
	MaterialBinding *M = new MaterialBinding();
	
	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		M->setAttribute(A);
		delete A;
	}
	
	m_Nodes.push_back(M); 
}

void SubStack::pushNodeTranslation() {
	
	Translation *T = new Translation();
	
	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		T->setAttribute(A);
		delete A;
	}
	
	m_Nodes.push_back(T);
}

void SubStack::pushNodeRotation() {
	
	Rotation *R = new Rotation();
	
	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		R->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(R);
}

void SubStack::pushNodeScale() {
	
	Scale *S = new Scale();
	
	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		S->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(S);
}

void SubStack::pushNodeMatrixTransform() {
	
	MatrixTransform *M = new MatrixTransform();
	
	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		M->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(M);
}

void SubStack::pushNodeTransform() {
	
	Transform *T = new Transform();
	
	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		T->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(T);
}

void SubStack::pushNodeOrthographicCamera() {
	
	OrthographicCamera *O = new OrthographicCamera();
	
	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		O->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(O);
}

void SubStack::pushNodePerspectiveCamera() {

	PerspectiveCamera *O = new PerspectiveCamera();
	
	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		O->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(O);
}

void SubStack::pushNodePointLight() {
	
	PointLight *P = new PointLight();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		P->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(P);
}

void SubStack::pushNodeSpotLight() {

	SpotLight *P = new SpotLight();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		P->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(P);
}

void SubStack::pushNodeDirectionalLight() {

	DirectionalLight *D = new DirectionalLight();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		D->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(D);
}

void SubStack::pushNodeTexture2Transform() {
	
	Texture2Transform *T = new Texture2Transform();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		T->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(T);
}

void SubStack::pushNodeShapeHints() {
	
	ShapeHints *S = new ShapeHints();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		S->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(S);
}

void SubStack::pushNodeNormalBinding() {
	
	NormalBinding *N = new NormalBinding();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		N->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(N);
}

void SubStack::pushNodeFontStyle() {
	
	FontStyle *F = new FontStyle();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		F->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(F);
}

void SubStack::pushNodeLOD() {

	LOD *L = new LOD();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		L->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(L);
}

void SubStack::pushNodeNormal() {

	Normal *N = new Normal();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		N->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(N);
}

void SubStack::pushNodeCoordinate3() {

	Coordinate3 *C = new Coordinate3();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		C->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(C);
}

void SubStack::pushNodeTextureCoordinate2() {

	TextureCoordinate2 *C = new TextureCoordinate2();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		C->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(C);
}

void SubStack::pushNodePointSet() {

	PointSet *N = new PointSet();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		N->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(N);
}

void SubStack::pushNodeIndexedLineSet() {

	IndexedLineSet *N = new IndexedLineSet();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		N->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(N);
}

void SubStack::pushNodeIndexedFaceSet() {

	IndexedFaceSet *N = new IndexedFaceSet();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		N->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(N);
}

void SubStack::pushNodeTexture2() {

	Texture2 *N = new Texture2();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		N->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(N);
}

void SubStack::pushNodeWWWInline() {

	WWWInline *N = new WWWInline();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		N->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(N);
}

void SubStack::pushNodeWWWAnchor() {

	WWWAnchor *N = new WWWAnchor();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		N->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(N);
}

void SubStack::pushNodeAsciiText() {

	AsciiText *N = new AsciiText();

	Attribute *A = 0;
	
	while ((A = m_Child->getFirstAttribute()) != 0) {
		N->setAttribute(A);
		delete A;
	}

	m_Nodes.push_back(N);
}

bool SubStack::pushAttributeSFImage(string name) {
	Attribute *A = new Attribute();
	A->setName(name);
	
	SFImage image;
	
	image.setSize(m_Integers[0],m_Integers[1]);
	m_Integers.erase(m_Integers.begin());
	m_Integers.erase(m_Integers.begin());
	image.setImage(m_Integers);
	m_Integers.clear();
	
	A->setImage(image);
	
	m_Attributes.push_back(A);
	
	return image.isValid();
}

void SubStack::pushAttributeSFString(string name) {
	Attribute *A = new Attribute();
	A->setName(name);
	
	A->setString(m_Strings[0]);
	m_Strings.erase(m_Strings.begin());
	
	m_Attributes.push_back(A);
}

void SubStack::pushAttributeSFBitmask(string name) {
	Attribute *A = new Attribute();
	A->setName(name);
	
	int ival = 0;
	
	for (int i=0; i<m_Integers.size(); i++) {
		ival |= m_Integers[i];
	}
	m_Integers.clear();
	
	A->setInteger(ival);
	
	m_Attributes.push_back(A);
}

void SubStack::pushAttributeSFMatrix(string name) {
	Attribute *A = new Attribute();
	
	SFMatrix Matrix;
	
	Matrix.setValues(m_Floats);
	m_Floats.clear();
	
	A->setMatrix(Matrix);
	
	m_Attributes.push_back(A);
}

void SubStack::pushAttributeSFRotation(string name) {
	Attribute *A = new Attribute();
	
	SFRotation Rot;
	
	Rot.setValues(m_Floats[0],m_Floats[1],m_Floats[2],m_Floats[3]);
	m_Floats.erase(m_Floats.begin());
	m_Floats.erase(m_Floats.begin());
	m_Floats.erase(m_Floats.begin());
	m_Floats.erase(m_Floats.begin());
	
	A->setRotation(Rot);

	m_Attributes.push_back(A);
}

void SubStack::pushAttributeSFVec2f(string name) {
	Attribute *A = new Attribute();
	A->setName(name);
	
	SFVec2f Vec2f;
	
	Vec2f.setValues(m_Floats[0],m_Floats[1]);
	m_Floats.erase(m_Floats.begin());
	m_Floats.erase(m_Floats.begin());
	
	A->setVec2f(Vec2f);
	
	m_Attributes.push_back(A);
}

void SubStack::pushAttributeMFVec2f(string name) {
	Attribute *A = new Attribute();
	A->setName(name);
	
	vector<SFVec2f> mVec2f;
	SFVec2f Vec2f;
	
	while (m_Floats.size() >= 2) {
		Vec2f.setValues(m_Floats[0],m_Floats[1]);
		m_Floats.erase(m_Floats.begin());
		m_Floats.erase(m_Floats.begin());
		mVec2f.push_back(Vec2f);
	}
	
	A->setMVec2f(mVec2f);
	
	m_Attributes.push_back(A);
}

void SubStack::pushAttributeSFVec3f(string name) {
	Attribute *A = new Attribute();
	A->setName(name);
	
	SFVec3f Vec3f;
	
	Vec3f.setValues(m_Floats[0],m_Floats[1],m_Floats[2]);
	m_Floats.erase(m_Floats.begin());
	m_Floats.erase(m_Floats.begin());
	m_Floats.erase(m_Floats.begin());
	
	A->setVec3f(Vec3f);
	
	m_Attributes.push_back(A);
}

void SubStack::pushAttributeMFVec3f(string name) {
	Attribute *A = new Attribute();
	A->setName(name);
	
	vector<SFVec3f> mVec3f;
	SFVec3f Vec3f;
	
	while (m_Floats.size() >= 3) {
		Vec3f.setValues(m_Floats[0],m_Floats[1],m_Floats[2]);
		m_Floats.erase(m_Floats.begin());
		m_Floats.erase(m_Floats.begin());
		m_Floats.erase(m_Floats.begin());
		mVec3f.push_back(Vec3f);
	}
	
	A->setMVec3f(mVec3f);
	
	m_Attributes.push_back(A);
}

void SubStack::pushAttributeSFColor(string name) {
	Attribute *A = new Attribute();
	A->setName(name);
	A->setColor(m_Floats[0],m_Floats[1],m_Floats[2]);
	m_Floats.erase(m_Floats.begin());
	m_Floats.erase(m_Floats.begin());
	m_Floats.erase(m_Floats.begin());
	
	m_Attributes.push_back(A);
}

void SubStack::pushAttributeMFColor(string name) {
	Attribute *A = new Attribute();
	A->setName(name);

	vector<SFColor> vColor;
	SFColor Color;

	while (m_Floats.size() >= 3) {

		Color.setColor(m_Floats[0],m_Floats[1],m_Floats[2]);		
		m_Floats.erase(m_Floats.begin());
		m_Floats.erase(m_Floats.begin());
		m_Floats.erase(m_Floats.begin());
		vColor.push_back(Color);
	}	
	
	A->setMColor(vColor);
	
	m_Attributes.push_back(A);
}

void SubStack::pushAttributeSFFloat(string name) {
	Attribute *A = new Attribute();
	A->setName(name);
	A->setFloat(m_Floats[0]);
	m_Floats.erase(m_Floats.begin());
	
	m_Attributes.push_back(A); 
}

void SubStack::pushAttributeMFFloat(string name) {
	Attribute *A = new Attribute();
	A->setName(name);
	A->setMFloat(m_Floats);
	m_Floats.clear();
	
	m_Attributes.push_back(A);
}

void SubStack::pushAttributeSFLong(string name) {
	Attribute *A = new Attribute();
	A->setName(name);
	A->setInteger(m_Integers[0]);
	m_Integers.erase(m_Integers.begin());
	
	m_Attributes.push_back(A);
}

void SubStack::pushAttributeMFLong(string name) {
	Attribute *A = new Attribute();
	A->setName(name);
	
	vector<int> mInt;
	
	while (m_Integers.size() > 0) {
		mInt.push_back(m_Integers[0]);
		m_Integers.erase(m_Integers.begin());
	}

	A->setMInteger(mInt);
	
	m_Attributes.push_back(A);
}

void SubStack::pushAttributeSFBool(string name) {
	Attribute *A = new Attribute();
	A->setName(name);
	A->setBool(m_Bools[0]);
	m_Bools.erase(m_Bools.begin());
	
	m_Attributes.push_back(A);
}

void SubStack::pushString(string s) {
	m_Strings.push_back(s);
}

void SubStack::pushFloat(float f) {
	m_Floats.push_back(f);
}

void SubStack::pushInteger(int i) {
	m_Integers.push_back(i);
}

void SubStack::pushBool(bool b) {
	m_Bools.push_back(b);
}

string SubStack::popString() {
	
	string s = "";
	
	if (m_Strings.size() > 0) {
	
		s = m_Strings.back();
		m_Strings.pop_back();
		
	}
	
	return s;
}

Node* SubStack::lastNode() {
	return m_Nodes.back();
}

Node* SubStack::getFirstNode() {
	Node *N = 0;
	
	if (m_Nodes.size() > 0) {
		N = m_Nodes[0];
		m_Nodes.erase(m_Nodes.begin());
	}
	return N;
}

Attribute* SubStack::getFirstAttribute() {
	Attribute *A = 0;
	
	if (m_Attributes.size() > 0) {
		A = m_Attributes[0];
		m_Attributes.erase(m_Attributes.begin());
	}
	return A;
}

}
