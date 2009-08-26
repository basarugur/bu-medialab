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

#include "FontStyle.hh"

namespace vrml1
{

FontStyle::FontStyle()
{
	m_size = 10;
	m_family = SERIF;
	m_style = NONE;
}
  
void FontStyle::setSize(float size) {
	m_size = size;
}

float FontStyle::size() const {
	return m_size;
}
	
void FontStyle::setFamily(e_Family family) {
	m_family = family;
}
	
FontStyle::e_Family FontStyle::family() const {
	return m_family;
}
	
void FontStyle::setStyle(unsigned int style) {
	m_style = style;
}

unsigned int FontStyle::style() const {
	return m_style;
}
	
void FontStyle::setAttribute(Attribute *A) {
}

}
