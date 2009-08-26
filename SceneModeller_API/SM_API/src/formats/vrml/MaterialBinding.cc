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

#include "MaterialBinding.hh"

namespace vrml1
{

MaterialBinding::MaterialBinding()
{
	m_value = DEFAULT;
}

void MaterialBinding::setValue(e_MaterialValue value) {
	m_value = value;
}

MaterialBinding::e_MaterialValue MaterialBinding::value() const {
	return m_value;
}
	
void MaterialBinding::setAttribute(Attribute *A) {
	
	if (A->Name() == "value") {
		m_value = (e_MaterialValue) A->Integer();
	}
}
	
}
