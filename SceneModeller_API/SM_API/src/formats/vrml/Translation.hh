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

#ifndef TRANSLATION_H_
#define TRANSLATION_H_

#include "Node.hh"
#include "Attribute.hh"
#include "SFVec3f.hh"

namespace vrml1
{

class Translation : public vrml1::Node
{
public:
	Translation();
	
	void setTranslation(SFVec3f translation);
	SFVec3f translation() const;
	
	virtual void setAttribute(Attribute *A);
	
private:
	SFVec3f m_translation;
};

}

#endif /*TRANSLATION_H_*/
