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

#ifndef VRML1TEXTURE2_HH_
#define VRML1TEXTURE2_HH_

#include <string>
#include "Node.hh"
#include "Attribute.hh"
#include "SFImage.hh"

using namespace std;

namespace vrml1
{

class Texture2 : public vrml1::Node
{
public:
	enum e_Wrap { REPEAT=0, CLAMP };

	Texture2();
	
	void setFilename(string filename);
	string filename() const;
	
	void setImage(SFImage image);
	SFImage image() const;
	
	void setWrapS(e_Wrap wrapS);
	e_Wrap wrapS() const;
	
	void setWrapT(e_Wrap wrapT);
	e_Wrap wrapT() const;
	
	virtual void setAttribute(Attribute *A);
	
private:
	string m_filename;
	SFImage m_image;
	e_Wrap m_wrapS;
	e_Wrap m_wrapT;
};

}

#endif /*VRML1TEXTURE2_HH_*/
