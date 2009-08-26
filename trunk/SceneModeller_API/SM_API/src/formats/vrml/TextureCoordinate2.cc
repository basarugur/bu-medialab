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

#include "TextureCoordinate2.hh"

namespace vrml1
{

TextureCoordinate2::TextureCoordinate2()
{
}

void TextureCoordinate2::setPoint(vector<SFVec2f> point) {
	m_point = point;
}

vector<SFVec2f> TextureCoordinate2::point() const {
	return m_point;
}
	
void TextureCoordinate2::setAttribute(Attribute *A) {
	
	if (A->Name() == "point") {
		m_point = A->MVec2f();
	}
} 
	
}
