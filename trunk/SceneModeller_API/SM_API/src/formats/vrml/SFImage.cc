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

#include "SFImage.hh"

namespace vrml1
{

SFImage::SFImage()
{
	m_xl = 0;
	m_yl = 0;
}

void SFImage::setSize(int xl, int yl) {
	m_xl = xl;
	m_yl = yl;
}

int SFImage::xl() const {
	return m_xl;
}

int SFImage::yl() const {
	return m_yl;
}
	
void SFImage::setImage(vector<int> image) {
	m_image = image;
}

vector<int> SFImage::image() const {
	return m_image;
}

bool SFImage::isValid() {
	return ((m_xl*m_yl) == m_image.size());
}
	
}
