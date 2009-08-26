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

#include "PerspectiveCamera.hh"

namespace vrml1
{

PerspectiveCamera::PerspectiveCamera()
{
	m_position.setValues(0,0,1);
	m_orientation.setValues(0,0,1,0);
	m_focalDistance = 5;
	m_heightAngle = 0.785398;
}

void PerspectiveCamera::setPostion(SFVec3f position) {
	m_position = position;
}

SFVec3f PerspectiveCamera::position() const {
	return m_position;
}

void PerspectiveCamera::setOrientation(SFRotation orientation) {
	m_orientation = orientation;
}

SFRotation PerspectiveCamera::orientation() const {
	return m_orientation;
}
	
void PerspectiveCamera::setFocalDistance(float focalDistance) {
	m_focalDistance = focalDistance;
}

float PerspectiveCamera::focalDistance() const {
	return m_focalDistance;
}
	
void PerspectiveCamera::setHeightAngle(float heightAngle) {
	m_heightAngle = heightAngle;
}

float PerspectiveCamera::heightAngle() const {
	return m_heightAngle;
}
	
void PerspectiveCamera::setAttribute(Attribute *A) {
	
	if (A->Name() == "position") {
		m_position = A->Vec3f();
	} else 	if (A->Name() == "orientation") {
		m_orientation = A->Rotation();
	} else 	if (A->Name() == "") {
		m_focalDistance = A->Float();
	} else 	if (A->Name() == "heightAngle") {
		m_heightAngle = A->Float();
	}	
}
	
}
