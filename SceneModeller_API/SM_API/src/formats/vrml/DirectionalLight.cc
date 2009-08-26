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

#include "DirectionalLight.hh"

namespace vrml1
{

DirectionalLight::DirectionalLight()
{
	m_on = true;
	m_intensity = 1.0;
	m_color.setColor(1,1,1);
	m_direction.setValues(0,0,-1);
}

void DirectionalLight::setOn(bool on) {
	m_on = on;
}

bool DirectionalLight::on() const {
	return m_on;
}
	
void DirectionalLight::setIntensity(float intensity) {
	m_intensity = intensity;
}

float DirectionalLight::intensity() const {
	return m_intensity;
}
	
void DirectionalLight::setColor(SFColor color) {
	m_color = color;
}

SFColor DirectionalLight::color() const {
	return m_color;
}
	
void DirectionalLight::setDirection(SFVec3f direction) {
	m_direction = direction;
}

SFVec3f DirectionalLight::direction() const {
	return m_direction;
}
	
void DirectionalLight::setAttribute(Attribute *A) {
	
	if (A->Name() == "on") {
		m_on = A->Bool();
	} else 	if (A->Name() == "intensity") {
		m_intensity = A->Float();
	} else 	if (A->Name() == "color") {
		m_color = A->Color();
	} else if (A->Name() == "direction") {
		m_direction = A->Vec3f();
	}
}

}
