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

#include "SFRotation.hh"

namespace vrml1
{

SFRotation::SFRotation()
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_angle = 0;
}

void SFRotation::setValues(float x, float y, float z, float angle) {
	m_x = x;
	m_y = y;
	m_z = z;
	m_angle = angle;
} 

}
