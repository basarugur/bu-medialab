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

#include "Texture2Transform.hh"

namespace vrml1
{

Texture2Transform::Texture2Transform()
{
	m_translation.setValues(0,0);
	m_rotation = 0;
	m_scaleFactor.setValues(1,1);
	m_center.setValues(0,0);
}

void Texture2Transform::setTranslation(SFVec2f translation) {
	m_translation = translation;
}

SFVec2f Texture2Transform::translation() const {
	return m_translation;
}

void Texture2Transform::setRoation(float rotation) {
	m_rotation = rotation;
}

float Texture2Transform::rotation() const {
	return m_rotation;
}
	
void Texture2Transform::setScaleFactor(SFVec2f scaleFactor) {
	m_scaleFactor = scaleFactor;
}

SFVec2f Texture2Transform::scaleFactor() const {
	return m_scaleFactor;
}

void Texture2Transform::setCenter(SFVec2f center) {
	m_center = center;
}

SFVec2f Texture2Transform::center() const {
	return m_center;
}

void Texture2Transform::setAttribute(Attribute *A) {
	if (A->Name() == "translation") {
		m_translation = A->Vec2f();
	} else if (A->Name() == "rotation") {
		m_rotation = A->Float();
	} else if (A->Name() == "scaleFactor") {
		m_scaleFactor = A->Vec2f();
	} else if (A->Name() == "center") {
		m_center = A->Vec2f();
	}
}

}
