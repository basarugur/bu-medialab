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

#ifndef VRML1ASCIITEXT_H_
#define VRML1ASCIITEXT_H_

#include <string>
#include "Node.hh"
#include "Attribute.hh"

using namespace std;

namespace vrml1
{

class AsciiText : public vrml1::Node
{
public:
	enum e_Justification { LEFT=0, CENTER, RIGHT };

	AsciiText();

	void setString(string str);
	string str() const;
	
	void setSpacing(float spacing);
	float spacing() const;
	
	void setJustification(e_Justification justification);
	e_Justification justification() const;
	
	void setWidth(vector<float> width);
	vector<float> width() const;
	
	virtual void setAttribute(Attribute *A);
	
private:
	string m_string;
	float m_spacing;
	e_Justification m_justification;
	vector<float> m_width;	
};

}

#endif /*VRML1ASCIITEXT_H_*/
