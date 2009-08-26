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

#ifndef VRML1INDEXEDFACESET_HH_
#define VRML1INDEXEDFACESET_HH_

#include "Node.hh"
#include "Attribute.hh"

namespace vrml1
{

class IndexedFaceSet : public vrml1::Node
{
public:
	IndexedFaceSet();
	
	void setCoordIndex(vector<int> coordIndex);
	vector<int> coordIndex() const;
	
	void setMaterialIndex(vector<int> materialIndex);
	vector<int> materialIndex() const;
	
	void setNormalIndex(vector<int> normalIndex);
	vector<int> normalIndex() const;
	
	void setTextureCoordIndex(vector<int> textureCoordIndex);
	vector<int> textureCoordIndex() const;
	
	virtual void setAttribute(Attribute *A);
	
private:
	vector<int> m_coordIndex;
	vector<int> m_materialIndex;
	vector<int> m_normalIndex;
	vector<int> m_textureCoordIndex;
};

}

#endif /*VRML1INDEXEDFACESET_HH_*/
