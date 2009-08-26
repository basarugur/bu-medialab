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

#include "WWWAnchor.hh"

namespace vrml1
{

WWWAnchor::WWWAnchor()
{
	m_name = "";
	m_description = "";
	m_map = NONE;
}

void WWWAnchor::setName(string name) {
	m_name = name;
}

string WWWAnchor::name() const {
	return m_name;
}

void WWWAnchor::setDescription(string description) {
	m_description = description;
}

string WWWAnchor::description() const {
	return m_description;
}	

void WWWAnchor::setMap(e_Map map) {
	m_map = map;
}

WWWAnchor::e_Map WWWAnchor::map() const {
	return m_map;
}
	
void WWWAnchor::setAttribute(Attribute *A) {
	
	if (A->Name() == "name") {
		m_name = A->String();
	} else if (A->Name() == "description") {
		m_description = A->String();
	} else if (A->Name() == "map") {
		switch (A->Integer()) {
			case 0x00: m_map = NONE;
			case 0x01: m_map = POINT;
			default: m_map = NONE;
		}
	}  
}

}
