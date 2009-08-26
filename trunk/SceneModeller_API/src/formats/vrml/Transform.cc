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

#include "Transform.hh"

namespace vrml1
{

Transform::Transform()
{
}

void Transform::setTranslation(SFVec3f translation) {
	m_translation = translation;
}

SFVec3f Transform::translation() const {
	return m_translation;
}
	
void Transform::setRotation(SFRotation rotation) {
	m_rotation = rotation;
}

SFRotation Transform::rotation() const {
	return m_rotation;
}
	
void Transform::setScaleFactor(SFVec3f scaleFactor) {
	m_scaleFactor = scaleFactor;
}

SFVec3f Transform::scaleFactor() const {
	return m_scaleFactor;
}
	
void Transform::setScaleOrientation(SFRotation scaleOrientation) {
	m_scaleOrientation = scaleOrientation;
}

SFRotation Transform::scaleOrientation() const {
	return m_scaleOrientation;
}
	
void Transform::setCenter(SFVec3f center) {
	m_center = center;
}

SFVec3f Transform::center() const {
	return m_center;
}
	
void Transform::setAttribute(Attribute *A) {
	
	if (A->Name() == "translation") {
		m_translation = A->Vec3f();
	} else if (A->Name() == "rotation") {
		m_rotation = A->Rotation();
	} else if (A->Name() == "scaleFactor") {
		m_scaleFactor = A->Vec3f();
	} else if (A->Name() == "scaleOrientation") {
		m_scaleOrientation = A->Rotation();
	} else if (A->Name() == "center") {
		m_center = A->Vec3f();
	} 
}

}
