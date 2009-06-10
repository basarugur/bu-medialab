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

#include "NormalBinding.hh"

namespace vrml1
{

NormalBinding::NormalBinding()
{
	m_value = DEFAULT;
}

void NormalBinding::setValue(e_Bindings value) {
	m_value = value;
} 

NormalBinding::e_Bindings NormalBinding::value() const {
	return m_value;
}
	
void NormalBinding::setAttribute(Attribute *A) {
	
	if (A->Name() == "value") {
		switch (A->Integer()) {
			case 0x00: m_value = DEFAULT; break;
			case 0x01: m_value = OVERALL; break;
			case 0x02: m_value = PER_PART; break;
			case 0x03: m_value = PER_PART_INDEXED; break;
			case 0x04: m_value = PER_FACE; break;
			case 0x05: m_value = PER_FACE_INDEXED; break;
			case 0x06: m_value = PER_VERTEX; break;
			case 0x07: m_value = PER_VERTEX_INDEXED; break;
			default: m_value = DEFAULT;
		}
	}
}

}
