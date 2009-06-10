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

#include "Cylinder.hh"

namespace vrml1
{

Cylinder::Cylinder()
{
	m_Parts = ALL;
	m_Radius = 1.0;
	m_Height = 2.0;
}

void Cylinder::setParts(int Parts) {
	m_Parts = Parts;
}

float Cylinder::Parts() const {
	return m_Parts;
}
	
void Cylinder::setHeight(float Height) {
	m_Height = Height;
}

float Cylinder::Height() const {
	return m_Height;
}
	
void Cylinder::setRadius(float Radius) {
	m_Radius = Radius; 
}

float Cylinder::Radius() const {
	return m_Radius;
}
	
void Cylinder::setAttribute(Attribute *A) {
	
	if (A->Name() == "parts") {
		m_Parts = A->Integer();
	} else if (A->Name() == "height") {
		m_Height = A->Float();
	} else if (A->Name() == "radius") {
		m_Radius = A->Float();
	}
}
	
}
