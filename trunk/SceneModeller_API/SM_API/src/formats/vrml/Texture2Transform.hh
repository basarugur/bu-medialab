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

#ifndef VRML1TEXTURE2TRANSFORM_HH_
#define VRML1TEXTURE2TRANSFORM_HH_

#include "Node.hh"
#include "Attribute.hh"
#include "SFVec2f.hh"

namespace vrml1
{

class Texture2Transform : public vrml1::Node
{
public:
	Texture2Transform();
	
	void setTranslation(SFVec2f translation);
	SFVec2f translation() const;

	void setRoation(float rotation);
	float rotation() const;
	
	void setScaleFactor(SFVec2f scaleFactor);
	SFVec2f scaleFactor() const;

	void setCenter(SFVec2f center);
	SFVec2f center() const;
	
	virtual void setAttribute(Attribute *A);

private:
	SFVec2f	m_translation;
	float m_rotation;
	SFVec2f m_scaleFactor;
	SFVec2f m_center;
};

}

#endif /*VRML1TEXTURE2TRANSFORM_HH_*/
