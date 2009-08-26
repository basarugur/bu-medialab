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

#ifndef VRML1COORDINATE3_HH_
#define VRML1COORDINATE3_HH_

#include <vector>
#include "Node.hh"
#include "Attribute.hh"
#include "SFVec3f.hh"

using namespace std;

namespace vrml1
{

class Coordinate3 : public vrml1::Node
{
public:
	Coordinate3();
	
	void setPoint(vector<SFVec3f> point);
	vector<SFVec3f> point() const;
	
	virtual void setAttribute(Attribute *A); 
	
private:
	vector<SFVec3f> m_point; 	
};

}

#endif /*VRML1NORMAL_HH_*/
