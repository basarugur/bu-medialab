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

#ifndef CONE_H_
#define CONE_H_

#include "Node.hh"

namespace vrml1
{

class Cone : public vrml1::Node
{
public:
	Cone();
	virtual ~Cone();
	
	void setParts(unsigned int Parts);
	unsigned int Parts();
	
	void setbottomRadius(float Radius);
	float bottomRadius() const;
	
	void setHeight(float Height);
	float Height() const;
	
	virtual void setAttribute(Attribute *A);
	
	enum e_parts { SIDES=1, BOTTOM=2, ALL=3 };
	
private:
	unsigned int m_Parts;
	float m_BottomRadius;
	float m_Height;
};

}

#endif /*CONE_H_*/
