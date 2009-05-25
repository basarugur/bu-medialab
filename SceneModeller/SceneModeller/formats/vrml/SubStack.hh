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

#ifndef SUBSTACK_H_
#define SUBSTACK_H_

#include <vector>
#include "Node.hh"
#include "Attribute.hh"

using namespace std;

namespace vrml1 {
	
class SubStack
{
public:
	SubStack(SubStack *Parent);
	virtual ~SubStack();
	
	SubStack* down();
	SubStack* up();
	
	void pushNodeSeparator();
	void pushNodeSwitch();
	void pushNodeUse(string id);
	void pushNodeCube();
	void pushNodeCone();
	void pushNodeSphere();
	void pushNodeCylinder();
	void pushNodeMaterial();
	void pushNodeMaterialBinding();
	void pushNodeTranslation();
	void pushNodeRotation();
	void pushNodeScale();
	void pushNodeMatrixTransform();
	void pushNodeTransform();
	void pushNodeOrthographicCamera();
	void pushNodePerspectiveCamera();
	void pushNodePointLight();
	void pushNodeSpotLight();
	void pushNodeDirectionalLight();
	void pushNodeTexture2Transform();
	void pushNodeShapeHints();
	void pushNodeNormalBinding();
	void pushNodeFontStyle();
	void pushNodeLOD();
	void pushNodeNormal();
	void pushNodeCoordinate3();
	void pushNodeTextureCoordinate2();
	void pushNodePointSet();
	void pushNodeIndexedLineSet();
	void pushNodeIndexedFaceSet();
	void pushNodeTexture2();
	void pushNodeWWWInline();
	void pushNodeWWWAnchor();
	void pushNodeAsciiText();

	bool pushAttributeSFImage(string name);
	void pushAttributeSFString(string name);
	void pushAttributeSFBitmask(string name);
	void pushAttributeSFMatrix(string name);
	void pushAttributeSFRotation(string name);
	void pushAttributeSFVec2f(string name);
	void pushAttributeMFVec2f(string name);
	void pushAttributeSFVec3f(string name);
	void pushAttributeMFVec3f(string name);
	void pushAttributeSFColor(string name);
	void pushAttributeMFColor(string name);
	void pushAttributeSFFloat(string name);
	void pushAttributeMFFloat(string name);
	void pushAttributeSFLong(string name);
	void pushAttributeMFLong(string name);
	void pushAttributeSFBool(string name);
	
	void pushString(string s);
	void pushFloat(float f);
	void pushInteger(int i);
	void pushBool(bool b);
	
	string popString();
	Node* lastNode();
	
	Node* getFirstNode();
	Attribute* getFirstAttribute();
	
private:
	SubStack *m_Parent;
	SubStack *m_Child;

	vector<Node*> m_Nodes;
	vector<Attribute*> m_Attributes;	

	vector<string> m_Strings;
	vector<float> m_Floats;
	vector<int> m_Integers;
	vector<bool> m_Bools;
};

}

#endif /*SUBSTACK_H_*/
