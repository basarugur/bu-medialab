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

#include "WWWInline.hh"

namespace vrml1
{

WWWInline::WWWInline()
{
}

void WWWInline::setName(string name) {
	m_name = name;
}

string WWWInline::name() const {
	return m_name;
}
	
void WWWInline::setBboxSize(SFVec3f bboxSize) {
	m_bboxSize = bboxSize;
}

SFVec3f WWWInline::bboxSize() const {
	return m_bboxSize;
}
	
void WWWInline::setBboxCenter(SFVec3f bboxCenter) {
	m_bboxCenter = bboxCenter; 
}

SFVec3f WWWInline::bboxCenter() const {
	return m_bboxCenter;
}
	
void WWWInline::setAttribute(Attribute *A) {
	
	if (A->Name() == "name") {
		m_name = A->String();
	} else if (A->Name() == "bboxSize") {
		m_bboxSize = A->Vec3f();
	} else if (A->Name() == "bboxCenter") {
		m_bboxCenter = A->Vec3f();
	}
}

}
