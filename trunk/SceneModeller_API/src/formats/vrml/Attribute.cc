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

#include <sstream>
#include "Attribute.hh"


namespace vrml1 {

Attribute::Attribute()
{
	m_Name = "";
	m_String = "";
	m_Float = 0.0;
	m_Integer = 0;
}

Attribute::~Attribute()
{
}

void Attribute::setImage(SFImage image) {
	m_image = image;
}

void Attribute::setName(string Name) {
	m_Name = Name;
}

void Attribute::setString(string s) {
	m_String = s;	
}

void Attribute::setFloat(float f) {
	m_Float = f;
}

void Attribute::setMFloat(vector<float> vf) {
	m_MFloat = vf;
}

void Attribute::setInteger(int i) {
	m_Integer = i;
}

void Attribute::setMInteger(vector<int> vi) {
	m_MInteger = vi;
}

void Attribute::setBool(bool b) {
	m_Bool = b;
}

void Attribute::setColor(float c0, float c1, float c2) {
	m_Color.setColor(c0,c1,c2);
}

void Attribute::setMColor(vector<SFColor> vColor) {
	m_MColor = vColor;
}

void Attribute::setVec2f(SFVec2f Vec2f) {
	m_Vec2f = Vec2f;
}

void Attribute::setMVec2f(vector<SFVec2f> MVec2f) {
	m_MVec2f = MVec2f;
}

void Attribute::setVec3f(SFVec3f Vec3f) {
	m_Vec3f = Vec3f;
}

void Attribute::setMVec3f(vector<SFVec3f> MVec3f) {
	m_MVec3f = MVec3f;
}

void Attribute::setRotation(SFRotation Rot) {
	m_Rotation = Rot;
}

void Attribute::setMatrix(SFMatrix Matrix) {
	m_Matrix = Matrix;
}

SFImage Attribute::Image() const {
	return m_image;
}

string Attribute::Name() const {
	return m_Name;
}

string Attribute::String() const {
	return m_String;
}

float Attribute::Float() const {
	return m_Float;
}

vector<float> Attribute::MFloat() const {
	return m_MFloat;
}

int Attribute::Integer() const {
	return m_Integer; 
}

vector<int> Attribute::MInteger() const {
	return m_MInteger; 
}

bool Attribute::Bool() const {
	return m_Bool;
}

SFColor Attribute::Color() const {
	return m_Color;
}

vector<SFColor> Attribute::MColor() const {
	return m_MColor;
}

SFVec2f Attribute::Vec2f() const {
	return m_Vec2f;
}

vector<SFVec2f> Attribute::MVec2f() const {
	return m_MVec2f;
}

SFVec3f Attribute::Vec3f() const {
	return m_Vec3f;
}

vector<SFVec3f> Attribute::MVec3f() const {
	return m_MVec3f;
}

SFRotation Attribute::Rotation() const {
	return m_Rotation;
}

SFMatrix Attribute::Matrix() const {
	return m_Matrix;
}

}
