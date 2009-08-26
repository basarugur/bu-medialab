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

#ifndef VRML1FONTSTYLE_HH_
#define VRML1FONTSTYLE_HH_

#include "Node.hh"
#include "Attribute.hh"

namespace vrml1
{

class FontStyle : public vrml1::Node
{
public:
	enum e_Family { SERIF=0, SANS, TYPEWRITER };
	enum e_Style { NONE=0, BOLD=1, ITALIC=2 };
	
	FontStyle();
	
	void setSize(float size);
	float size() const;
	
	void setFamily(e_Family family);
	e_Family family() const;
	
	void setStyle(unsigned int style);
	unsigned int style() const;
	
	virtual void setAttribute(Attribute *A);
	
private:
	float m_size;
	e_Family m_family;
	unsigned int m_style; 	
};

}

#endif /*VRML1FONTSTYLE_HH_*/
