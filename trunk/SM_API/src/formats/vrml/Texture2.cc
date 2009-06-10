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

#include "Texture2.hh"

namespace vrml1
{

Texture2::Texture2()
{
	m_filename = "";
	m_wrapS = REPEAT;
	m_wrapT = REPEAT;
}

void Texture2::setFilename(string filename) {
	m_filename = filename;
}

string Texture2::filename() const {
	return m_filename;
}
	
void Texture2::setImage(SFImage image) {
	m_image = image;
}

SFImage Texture2::image() const {
	return m_image;
}
	
void Texture2::setWrapS(e_Wrap wrapS) {
	m_wrapS = wrapS;
}

Texture2::e_Wrap Texture2::wrapS() const {
	return m_wrapS;
}
	
void Texture2::setWrapT(e_Wrap wrapT) {
	m_wrapT = wrapT;
}

Texture2::e_Wrap Texture2::wrapT() const {
	return m_wrapT;
}
	
void Texture2::setAttribute(Attribute *A) {
	
	if (A->Name() == "filename") {
		m_filename = A->String();
	} else if (A->Name() == "image") {
		m_image = A->Image();
	} else if (A->Name() == "wrapS") {
		switch (A->Integer()) {
			case 0x00: m_wrapS = REPEAT; break;
			case 0x01: m_wrapS = CLAMP; break;
			default: m_wrapS = REPEAT;
		}
	} else if (A->Name() == "wrapT") {
		switch (A->Integer()) {
			case 0x00: m_wrapT = REPEAT; break;
			case 0x01: m_wrapT = CLAMP; break;
			default: m_wrapT = REPEAT;
		}
	}
}


}
