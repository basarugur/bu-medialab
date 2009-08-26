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

#ifndef VRML1ORTHOGRAPHICCAMERA_HH_
#define VRML1ORTHOGRAPHICCAMERA_HH_

#include "Node.hh"
#include "Attribute.hh"
#include "SFVec3f.hh"
#include "SFRotation.hh"

namespace vrml1
{

class OrthographicCamera : public vrml1::Node
{
public:
	OrthographicCamera();

	void setPostion(SFVec3f position);
	SFVec3f position() const;
	
	void setOrientation(SFRotation orientation);
	SFRotation orientation() const;
	
	void setFocalDistance(float focalDistance);
	float focalDistance() const;
	
	void setHeight(float height);
	float height() const;
	
	virtual void setAttribute(Attribute *A);
	
private:
	SFVec3f m_position;
	SFRotation m_orientation;
	float m_focalDistance;
	float m_height;
};

}

#endif /*VRML1ORTHOGRAPHICCAMERA_HH_*/
