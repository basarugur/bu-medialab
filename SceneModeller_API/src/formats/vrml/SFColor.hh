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

#ifndef SFCOLOR_H_
#define SFCOLOR_H_

namespace vrml1
{

class SFColor
{
public:
	SFColor();
	virtual ~SFColor();
	
	void setColor(float c0, float c1, float c2);
	
private:
	float m_c0;
	float m_c1;
	float m_c2;
};

}

#endif /*SFCOLOR_H_*/
