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

#ifndef VRML1SFIMAGE_HH_
#define VRML1SFIMAGE_HH_

#include <vector>

using namespace std;

namespace vrml1
{

class SFImage
{
public:
	SFImage();
	
	void setSize(int xl, int yl);
	int xl() const;
	int yl() const;
	
	void setImage(vector<int> image);
	vector<int> image() const;
	
	bool isValid();
	
private:
	int m_xl;
	int m_yl;
	vector<int> m_image;
};

}

#endif /*VRML1SFIMAGE_HH_*/
