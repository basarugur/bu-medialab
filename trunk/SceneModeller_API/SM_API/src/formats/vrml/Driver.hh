/**
 * VRML1 Parser
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

#ifndef VRML1DRIVER_H_
#define VRML1DRIVER_H_

#include <iostream>
#include <vector>
#include <map>
#include "vrml1-parser.hh"
#include "SubStack.hh"
#include "Document.hh"
#include "Node.hh"

using namespace std;

namespace vrml1 {
	class Driver;
}

// Announce to Flex the prototype we want for lexing function, ...
#define YY_DECL \
	vrml1::vrml1_parser::token_type                	\
		vrml1lex (vrml1::vrml1_parser::semantic_type* yylval,	\
			vrml1::vrml1_parser::location_type* yylloc,		\
		 	vrml1::Driver& driver)
     // ... and declare it for the parser's sake.
     YY_DECL;


namespace vrml1 {

class Driver
{
public:
	Driver();
	virtual ~Driver();
	
	// Handling the scanner
	void scan_begin();
    void scan_end();
    bool trace_scanning;

	// Handling the parser
	void parse (const std::string& f);
    std::string file;
    bool trace_parsing;
	
	// Error handling
    void error (const location& l, const std::string& m);
    void error (const std::string& m);
    
    // VRML Document handling
    Document *getVRML1Doc();
    
    // Node handling
    void pushVRMLDoc();
    void pushNodeSeparator();
    void pushNodeSwitch();
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
	bool pushDEF();
	bool pushUSE();

	// Attribute handling
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
    
    // Value handling
    void pushString(string s);
    void pushFloat(float f);
    void pushInteger(int i);
    void pushBool(bool b);
    
    // Stack handling
    void StackUp();
    void StackDown();
    
private:
	bool m_Error;

	SubStack *m_StackRoot;
	SubStack *m_Stack;
	
	Document *m_VRML1Doc;
	
	map<string, Node*> m_DefMap;
};

}

#endif /*VRML1DRIVER_H_*/
