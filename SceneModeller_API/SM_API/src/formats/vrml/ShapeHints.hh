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

#ifndef VRML1SHAPEHINTS_HH_
#define VRML1SHAPEHINTS_HH_

#include "Node.hh"

namespace vrml1
{

class ShapeHints : public vrml1::Node
{
public:
	enum e_VertexOrdering { UNKNOWN_ORDERING=0, CLOCKWISE, COUNTERCLOCKWISE };
	enum e_ShapeType { UNKNOWN_SHAPE_TYPE=0, SOLID };
	enum e_FaceType { UNKNOWN_FACE_TYPE=0, CONVEX }; 

	ShapeHints();

	void setVertexOrdering(e_VertexOrdering vertexOrdering);
	e_VertexOrdering vertexOrdering() const;
	
	void setShapeType(e_ShapeType shapeType);
	e_ShapeType shapeType() const;	
	
	void setFaceType(e_FaceType faceType);
	e_FaceType faceType() const;	
	
	void setCreaseAngle(float creaseAngle);
	float creaseAngle() const;	
	
	virtual void setAttribute(Attribute *A);
	
private:
	e_VertexOrdering m_vertexOrdering;
	e_ShapeType m_shapeType;
	e_FaceType m_faceType;
	float m_creaseAngle;
};

}

#endif /*VRML1SHAPEHINTS_HH_*/
