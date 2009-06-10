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

#include "Switch.hh"

namespace vrml1 {

Switch::Switch()
{
	m_whichChild = -1;
}

Switch::~Switch()
{
	for (int i=0; i<m_Nodes.size(); i++) {
		if (m_Nodes.at(i) != 0) {
			delete m_Nodes.at(i);
		}	
	}
}

void Switch::setAttribute(Attribute *A) {
	if (A->Name() == "whichChild") {
		m_whichChild = A->Integer();
	}
}

void Switch::addNode(Node * &N) {
	m_Nodes.push_back(N);
	N = 0;
}

}

