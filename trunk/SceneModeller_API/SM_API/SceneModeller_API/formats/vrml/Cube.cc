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
#include "Cube.hh"

using namespace std;

namespace vrml1 {

Cube::Cube()
{
	m_Width = 1;
	m_Height = 1;
	m_Depth = 1;
}

Cube::~Cube()
{
}

void Cube::setWidth(float Width) {
	m_Width = Width;	
}

float Cube::Width() const {
	return m_Width;
}

void Cube::setHeight(float Height) {
	m_Height = Height;	
}

float Cube::Height() const {
	return m_Height;
}

void Cube::setDepth(float Depth) {
	m_Depth = Depth;	
}

float Cube::Depth() const {
	return m_Depth;
}

void Cube::setAttribute(Attribute *A) {

	if (A->Name() == "width") {
		m_Width = A->Float();
	} else if (A->Name() == "height") {
		m_Height = A->Float();
	} else if (A->Name() == "depth") {
		m_Depth = A->Float();
	}	
}

}
