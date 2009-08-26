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

#ifndef VRML1WWWINLINE_HH_
#define VRML1WWWINLINE_HH_

#include <string>
#include "Node.hh"
#include "Attribute.hh"
#include "SFVec3f.hh"

using namespace std;

namespace vrml1
{

class WWWInline : public vrml1::Node
{
public:
	WWWInline();
	
	void setName(string name);
	string name() const;
	
	void setBboxSize(SFVec3f bboxSize);
	SFVec3f bboxSize() const;
	
	void setBboxCenter(SFVec3f bboxCenter);
	SFVec3f bboxCenter() const;
	
	virtual void setAttribute(Attribute *A);
	
private:
	string m_name;
	SFVec3f m_bboxSize;
	SFVec3f m_bboxCenter;
};

}

#endif /*VRML1WWWINLINE_HH_*/
