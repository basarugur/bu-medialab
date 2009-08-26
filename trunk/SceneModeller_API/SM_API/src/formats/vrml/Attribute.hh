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

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include <string>
#include <vector>
#include "SFColor.hh"
#include "SFVec3f.hh"
#include "SFVec2f.hh"
#include "SFRotation.hh"
#include "SFMatrix.hh"
#include "SFImage.hh"

using namespace std;

namespace vrml1 {

class Attribute
{
public:
	Attribute();
	virtual ~Attribute();
	
	void setName(string Name);
	
	void setImage(SFImage image);
	void setString(string s);
	void setFloat(float f);
	void setMFloat(vector<float> vf);
	void setInteger(int i);
	void setMInteger(vector<int> vi);
	void setBool(bool b);
	void setColor(float c0, float c1, float c2);
	void setMColor(vector<SFColor> vColor);
	void setVec3f(SFVec3f Vec3f);
	void setMVec3f(vector<SFVec3f> MVec3f);
	void setVec2f(SFVec2f Vec2f);
	void setMVec2f(vector<SFVec2f> MVec2f);
	void setRotation(SFRotation Rot);
	void setMatrix(SFMatrix Matrix);
	
	SFImage Image() const;
	string Name() const;
	string String() const;
	float Float() const;
	vector<float> MFloat() const;
	int Integer() const;
	vector<int> MInteger() const;
	bool Bool() const;
	SFColor Color() const;
	vector<SFColor> MColor() const;
	SFVec2f Vec2f() const;
	vector<SFVec2f> MVec2f() const;
	SFVec3f Vec3f() const;
	vector<SFVec3f> MVec3f() const;
	SFRotation Rotation() const;
	SFMatrix Matrix() const;
	
private:
	string m_Name;
	
	SFImage m_image;
	
	string m_String;
	
	float m_Float;
	vector<float> m_MFloat;
	
	int m_Integer;
	vector<int> m_MInteger;
	
	bool m_Bool;
	
	SFColor m_Color;
	vector<SFColor> m_MColor;
	
	SFVec2f m_Vec2f;
	vector<SFVec2f> m_MVec2f;

	SFVec3f m_Vec3f;
	vector<SFVec3f> m_MVec3f;
	
	SFRotation m_Rotation;
	
	SFMatrix m_Matrix;
};

}

#endif /*ATTRIBUTE_H_*/
