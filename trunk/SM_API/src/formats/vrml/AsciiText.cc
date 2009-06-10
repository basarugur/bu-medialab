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

#include "AsciiText.hh"

namespace vrml1
{

AsciiText::AsciiText()
{
	m_string = "";
	m_spacing = 1;
	m_justification = LEFT;
}

void AsciiText::setString(string str) {
	m_string = str;
}

string AsciiText::str() const {
	return m_string;
}
	
void AsciiText::setSpacing(float spacing) {
	m_spacing = spacing;
}

float AsciiText::spacing() const {
	return m_spacing;
}
	
void AsciiText::setJustification(e_Justification justification) {
	m_justification = justification;
}

AsciiText::e_Justification AsciiText::justification() const {
	return m_justification;
}
	
void AsciiText::setWidth(vector<float> width) {
	m_width = width;
}

vector<float> AsciiText::width() const {
	return m_width;
}
	
void AsciiText::setAttribute(Attribute *A) {

	if (A->Name() == "string") {
		m_string = A->String();
	} else if (A->Name() == "spacing") {
		m_spacing = A->Float();
	} else if (A->Name() == "justification") {
		switch (A->Integer()) {
			case 0x00: m_justification = LEFT; break;
			case 0x01: m_justification = CENTER; break;
			case 0x02: m_justification = RIGHT; break;
			default: m_justification = LEFT;
		}
	} else if (A->Name() == "width") {
		m_width = A->MFloat();
	}
}

}
