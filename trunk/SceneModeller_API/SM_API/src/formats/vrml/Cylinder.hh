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

#ifndef CYLINDER_H_
#define CYLINDER_H_

#include "Node.hh"
#include "Attribute.hh"

namespace vrml1
{

class Cylinder : public vrml1::Node
{
public:
	Cylinder();

	void setParts(int Parts);
	float Parts() const;
	
	void setHeight(float Height);
	float Height() const;
	
	void setRadius(float Radius);
	float Radius() const;
	
	virtual void setAttribute(Attribute *A);
	
	enum e_parts { SIDES=1, TOP=2, BOTTOM=4, ALL=7 };
	
private:
	int m_Parts;
	float m_Radius;
	float m_Height;
};

}

#endif /*CYLINDER_H_*/
