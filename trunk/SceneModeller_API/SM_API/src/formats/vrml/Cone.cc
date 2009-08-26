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

#include "Cone.hh"

namespace vrml1
{

Cone::Cone()
{
	m_Parts = ALL;
	m_BottomRadius = 1.0; 
	m_Height = 2.0;
}

Cone::~Cone()
{
}

void Cone::setParts(unsigned int Parts) {
}

unsigned int Cone::Parts() {
	return m_Parts;
}
	
void Cone::setbottomRadius(float Radius) {
	m_BottomRadius = Radius;
}

float Cone::bottomRadius() const {
	return m_BottomRadius;
}
	
void Cone::setHeight(float Height) {
	m_Height = Height;
}

float Cone::Height() const {
	return m_Height;
}
	
void Cone::setAttribute(Attribute *A) {
	
	if (A->Name() == "parts") {
		m_Parts = A->Integer();
	} else if (A->Name() == "height") {
		m_Height = A->Float();
	} else if (A->Name() == "bottomRadius") {
		m_BottomRadius = A->Float();
	}
}	


}
