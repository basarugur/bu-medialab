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

#include "ShapeHints.hh"

namespace vrml1
{

ShapeHints::ShapeHints()
{
	m_vertexOrdering = UNKNOWN_ORDERING;
	m_shapeType = UNKNOWN_SHAPE_TYPE;
	m_faceType = CONVEX;
	m_creaseAngle = 0.5;
}

void ShapeHints::setVertexOrdering(e_VertexOrdering vertexOrdering) {
	m_vertexOrdering = vertexOrdering;
}

ShapeHints::e_VertexOrdering ShapeHints::vertexOrdering() const {
	return m_vertexOrdering;
}
	
void ShapeHints::setShapeType(e_ShapeType shapeType){
	m_shapeType = shapeType;
}

ShapeHints::e_ShapeType ShapeHints::shapeType() const {
	return m_shapeType;
}	
	
void ShapeHints::setFaceType(e_FaceType faceType) {
	m_faceType = faceType;
}

ShapeHints::e_FaceType ShapeHints::faceType() const {
	return m_faceType;
}	
	
void ShapeHints::setCreaseAngle(float creaseAngle) {
	m_creaseAngle = creaseAngle;
}

float ShapeHints::creaseAngle() const {
	return m_creaseAngle;
}
	
void ShapeHints::setAttribute(Attribute *A) {
	
	if (A->Name() == "vertexOrdering") {
		switch(A->Integer()) {
			case 0x00: m_vertexOrdering = UNKNOWN_ORDERING; break;
			case 0x01: m_vertexOrdering = CLOCKWISE; break;
			case 0x02: m_vertexOrdering = COUNTERCLOCKWISE;	break;
			default: m_vertexOrdering = UNKNOWN_ORDERING;
		}
	} else if (A->Name() == "shapeType") {
		switch (A->Integer()) {
			case 0x00: m_shapeType = UNKNOWN_SHAPE_TYPE; break;
			case 0x01: m_shapeType = SOLID; break;
			default: m_shapeType = UNKNOWN_SHAPE_TYPE;
		}
	} else if (A->Name() == "faceType") {
		switch (A->Integer()) {
			case 0x00: m_faceType = UNKNOWN_FACE_TYPE; break;
			case 0x01: m_faceType = CONVEX; break;
			default: m_shapeType = UNKNOWN_SHAPE_TYPE;
		}
	} else if (A->Name() == "creaseAngle") {
		m_creaseAngle = A->Float();
	}
}

}
