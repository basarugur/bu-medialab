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

#include "PointLight.hh"

namespace vrml1
{

PointLight::PointLight()
{
	m_on = true;
	m_intensity = 1.0;
	m_color.setColor(1,1,1);
	m_location.setValues(0,0,1);
}

void PointLight::setOn(bool on) {
	m_on = on;
}

bool PointLight::on() const {
	return m_on;
}
	
void PointLight::setIntensity(float intensity) {
	m_intensity = intensity;
}

float PointLight::intensity() const {
	return m_intensity;
}
	
void PointLight::setColor(SFColor color) {
	m_color = color;
}

SFColor PointLight::color() const {
	return m_color;
}
	
void PointLight::setLocation(SFVec3f location) {
	m_location = location;
}

SFVec3f PointLight::location() const {
	return m_location;
}
	
void PointLight::setAttribute(Attribute *A) {
	
	if (A->Name() == "on") {
		m_on = A->Bool();
	} else 	if (A->Name() == "intensity") {
		m_intensity = A->Float();
	} else 	if (A->Name() == "color") {
		m_color = A->Color();
	} else 	if (A->Name() == "location") {
		m_location = A->Vec3f();
	}
}
	
}
