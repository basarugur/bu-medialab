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

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Node.hh"
#include "SFColor.hh"

namespace vrml1
{

class Material : public vrml1::Node
{
public:
	Material();
	virtual ~Material();
	
	void setAmbientColor(vector<SFColor> aColor);
	vector<SFColor> ambientColor() const;
	bool ambientColorExist() const;
	
	void setDiffuseColor(vector<SFColor> dColor);
	vector<SFColor> diffuseColor() const;
	bool diffuseColorExist() const;
	
	void setSpecularColor(vector<SFColor> sColor);
	vector<SFColor> specularColor() const;
	bool specularColorExist() const;
	
	void setEmissiveColor(vector<SFColor> eColor);
	vector<SFColor> emissiveColor() const;
	bool emissiveColorExist() const; 
	
	void setShininess(vector<float> shininess);
	vector<float> shininess() const;
	bool shininessExist() const;
	
	void setTransparency(vector<float> transparency);
	vector<float> transparency() const;
	bool transparencyExist() const;
	
	virtual void setAttribute(Attribute *A);
	
private:
	vector<SFColor> m_ambientColor;
	vector<SFColor> m_diffuseColor;
	vector<SFColor> m_specularColor;
	vector<SFColor> m_emissiveColor;
	vector<float> m_shininess;
	vector<float> m_transparency;
};

}

#endif /*MATERIAL_H_*/
