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

#ifndef SCALE_H_
#define SCALE_H_

#include "Node.hh"
#include "Attribute.hh"
#include "SFVec3f.hh"

namespace vrml1
{

class Scale : public vrml1::Node
{
public:
	Scale();
	
	void setScaleFactor(SFVec3f Vec3f);
	SFVec3f scaleFactor() const;
	
	virtual void setAttribute(Attribute *A);
	
private:
	SFVec3f m_scaleFactor;
};

}

#endif /*SCALE_H_*/
