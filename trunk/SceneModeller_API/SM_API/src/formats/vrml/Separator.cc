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

#include "Separator.hh"

namespace vrml1 {
	
Separator::Separator()
{
	m_renderCulling = AUTO;
}

Separator::~Separator()
{
	for (int i=0; i<m_Nodes.size(); i++) {
		if (m_Nodes.at(i) != 0) {
			delete m_Nodes.at(i);
		}	
	}
}

void Separator::setAttribute(Attribute *A) {
	if (A->Name() == "renderCulling") {
		if (A->String() == "ON") m_renderCulling = ON;
		else if (A->String() == "OFF") m_renderCulling = OFF;
		else if (A->String() == "AUTO") m_renderCulling = AUTO;
	}
}

void Separator::addNode(Node * &N) {
	m_Nodes.push_back(N);
	N = 0;
}

unsigned int Separator::getNodeCount() const {
	return m_Nodes.size();
}

const Node* Separator::getNode(unsigned int idx) const {
	if (idx < m_Nodes.size()) {
		return m_Nodes[idx];
	} else {
		return 0;
	}
		
}


}
