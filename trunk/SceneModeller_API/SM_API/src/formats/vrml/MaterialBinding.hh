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

#ifndef MATERIALBINDING_H_
#define MATERIALBINDING_H_

#include "Node.hh"
#include "Attribute.hh"

namespace vrml1
{

class MaterialBinding : public vrml1::Node
{
public:
	MaterialBinding();
	
	enum e_MaterialValue { DEFAULT=0, OVERALL, PER_PART, PER_PART_INDEXED, 
							PER_FACE, PER_FACE_INDEXED,
							PER_VERTEX, PER_VERTEX_INDEXED };
	
	void setValue(e_MaterialValue value);
	e_MaterialValue value() const;
	
	virtual void setAttribute(Attribute *A);
	
private:
	e_MaterialValue m_value;
};

}

#endif /*MATERIALBINDING_H_*/
