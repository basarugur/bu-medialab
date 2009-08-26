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

#ifndef VRML1SPOTLIGHT_HH_
#define VRML1SPOTLIGHT_HH_

#include "Node.hh"
#include "Attribute.hh"
#include "SFVec3f.hh"

namespace vrml1
{

class SpotLight : public vrml1::Node
{
public:
	SpotLight();

	void setOn(bool on);
	bool on() const;
	
	void setIntensity(float intensity);
	float intensity() const;
	
	void setColor(SFColor color);
	SFColor color() const;
	
	void setLocation(SFVec3f location);
	SFVec3f location() const;
	
	void setDirection(SFVec3f direction);
	SFVec3f direction() const;
	
	void setDropOffRate(float dropOffRate);
	float dropOffRate() const;
	
	void setCutOffAngle(float cutOffAngle);
	float cutOffAngle() const;
	
	virtual void setAttribute(Attribute *A);
	
private:
	bool m_on;
	float m_intensity;
	SFColor m_color;
	SFVec3f m_location;
	SFVec3f m_direction;
	float m_dropOffRate;
	float m_cutOffAngle;	
};

}

#endif /*VRML1SPOTLIGHT_HH_*/
