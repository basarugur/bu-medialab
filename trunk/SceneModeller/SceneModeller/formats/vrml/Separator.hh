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

#ifndef SEPARATOR_H_
#define SEPARATOR_H_

#include <vector>
#include "Node.hh"
#include "Attribute.hh"

using namespace std;

namespace vrml1 {
	
enum e_renderCulling { ON, OFF, AUTO };


class Separator : public vrml1::Node
{
public:
	Separator();
	virtual ~Separator();
	
	virtual void setAttribute(Attribute *A);
	void addNode(Node* &N);
	
	unsigned int getNodeCount() const;
	const Node* getNode(unsigned int idx) const;
	
private:
	e_renderCulling m_renderCulling;
	
	vector<Node*> m_Nodes;
};

}

#endif /*SEPARATOR_H_*/
