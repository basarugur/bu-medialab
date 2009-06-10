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

#include "IndexedLineSet.hh"

namespace vrml1
{

IndexedLineSet::IndexedLineSet()
{
}

void IndexedLineSet::setCoordIndex(vector<int> coordIndex) {
	m_coordIndex = coordIndex;
}

vector<int> IndexedLineSet::coordIndex() const {
	return m_coordIndex;
}
	
void IndexedLineSet::setMaterialIndex(vector<int> materialIndex) {
	m_materialIndex = materialIndex;
}

vector<int> IndexedLineSet::materialIndex() const {
	return m_materialIndex;
}
	
void IndexedLineSet::setNormalIndex(vector<int> normalIndex) {
	m_normalIndex = normalIndex;
}

vector<int> IndexedLineSet::normalIndex() const {
	return m_normalIndex;
}
	
void IndexedLineSet::setTextureCoordIndex(vector<int> textureCoordIndex) {
	m_textureCoordIndex = textureCoordIndex;
}

vector<int> IndexedLineSet::textureCoordIndex() const {
	return m_textureCoordIndex;
}
	
void IndexedLineSet::setAttribute(Attribute *A) {
	
	if (A->Name() == "coordIndex") {
		m_coordIndex = A->MInteger();
	} else 	if (A->Name() == "materialIndex") {
		m_materialIndex = A->MInteger();
	} else 	if (A->Name() == "normalIndex") {
		m_normalIndex = A->MInteger();
	} else 	if (A->Name() == "textureCoordIndex") {
		m_textureCoordIndex = A->MInteger();
	}
}

}
