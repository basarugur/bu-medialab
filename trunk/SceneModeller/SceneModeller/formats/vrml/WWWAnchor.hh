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

#ifndef VRML1WWWANCHOR_HH_
#define VRML1WWWANCHOR_HH_

#include <string>
#include "Node.hh"
#include "Attribute.hh"

using namespace std;

namespace vrml1
{

class WWWAnchor : public vrml1::Node
{
public:
	enum e_Map { NONE=0, POINT };

	WWWAnchor();
	
	void setName(string name);
	string name() const;
	
	void setDescription(string description);
	string description() const;
	
	void setMap(e_Map map);
	e_Map map() const;
	
	virtual void setAttribute(Attribute *A);
	
private:
	string m_name;
	string m_description;
	e_Map m_map;	
};

}

#endif /*VRML1WWWANCHOR_HH_*/
