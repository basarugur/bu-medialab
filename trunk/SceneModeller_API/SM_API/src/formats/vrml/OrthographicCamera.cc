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

#include "OrthographicCamera.hh"

namespace vrml1
{

OrthographicCamera::OrthographicCamera()
{
	m_position.setValues(0,0,1);
	m_orientation.setValues(0,0,1,0);
	m_focalDistance = 5;
	m_height = 2;
}

void OrthographicCamera::setPostion(SFVec3f position) {
	m_position = position;
}

SFVec3f OrthographicCamera::position() const {
	return m_position;
}

void OrthographicCamera::setOrientation(SFRotation orientation) {
	m_orientation = orientation;
}

SFRotation OrthographicCamera::orientation() const {
	return m_orientation;
}
	
void OrthographicCamera::setFocalDistance(float focalDistance) {
	m_focalDistance = focalDistance;
}

float OrthographicCamera::focalDistance() const {
	return m_focalDistance;
}
	
void OrthographicCamera::setHeight(float height) {
	m_height = height;
}

float OrthographicCamera::height() const {
	return m_height;
}
	
void OrthographicCamera::setAttribute(Attribute *A) {
	
	if (A->Name() == "position") {
		m_position = A->Vec3f();
	} else 	if (A->Name() == "orientation") {
		m_orientation = A->Rotation();
	} else 	if (A->Name() == "focalDistance") {
		m_focalDistance = A->Float();
	} else 	if (A->Name() == "height") {
		m_height = A->Float();
	}	
}
	
}
