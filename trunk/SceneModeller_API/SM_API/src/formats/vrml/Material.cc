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

#include "Material.hh"

namespace vrml1
{

Material::Material()
{
}

Material::~Material()
{
}

void Material::setAmbientColor(vector<SFColor> aColor) {
	m_ambientColor = aColor;
}

vector<SFColor> Material::ambientColor() const {
	return m_ambientColor;
}

bool Material::ambientColorExist() const {
	return m_ambientColor.size();
}
	
void Material::setDiffuseColor(vector<SFColor> dColor) {
	m_diffuseColor = dColor;
}

vector<SFColor> Material::diffuseColor() const {
	return m_diffuseColor;
}
	
bool Material::diffuseColorExist() const {
	return m_diffuseColor.size();
}
	
void Material::setSpecularColor(vector<SFColor> sColor) {
	m_specularColor = sColor;
}

vector<SFColor> Material::specularColor() const {
	return m_specularColor;
}
	
bool Material::specularColorExist() const {
	return m_specularColor.size();
}
	
void Material::setEmissiveColor(vector<SFColor> eColor) {
	m_emissiveColor = eColor;
}

vector<SFColor> Material::emissiveColor() const {
	return m_emissiveColor;
}
	
bool Material::emissiveColorExist() const {
	return m_emissiveColor.size();
}
	
void Material::setShininess(vector<float> shininess) {
	m_shininess = shininess;
}

vector<float> Material::shininess() const {
	return m_shininess;
}
	
bool Material::shininessExist() const {
	return m_shininess.size();
}
	
void Material::setTransparency(vector<float> transparency) {
	m_transparency = transparency;
}

vector<float> Material::transparency() const {
	return m_transparency;
}

bool Material::transparencyExist() const {
	return m_transparency.size();
}
	
void Material::setAttribute(Attribute *A) {
	
	if (A->Name() == "ambientColor") {
		m_ambientColor = A->MColor();
	} else if (A->Name() == "diffuseColor") {
		m_diffuseColor = A->MColor();
	} else if (A->Name() == "specularColor") {
		m_specularColor = A->MColor();
	} else if (A->Name() == "emissiveColor") {
		m_emissiveColor = A->MColor();
	} else if (A->Name() == "shininess") {
		m_shininess = A->MFloat();
	} else if (A->Name() == "transparency") {
		m_transparency = A->MFloat();
	}
}

}
