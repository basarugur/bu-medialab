#include "rectangle.h"

BBox RectangleShape::object_bound() const 
{
	return  BBox(Point3(-m_x/2.0,-m_y/2.0,0),Point3(m_x/2.0,m_y/2.0,0));
}

void RectangleShape::copyToMesh(TriangleMesh* msh_)
{
	Vertex* v1_ = new Vertex(-m_x/2.0,-m_y/2.0,0);
	Vertex* v2_ = new Vertex(m_x/2.0,-m_y/2.0,0);
	Vertex* v3_ = new Vertex(m_x/2.0 ,m_y/2.0,0);
	Vertex* v4_ = new Vertex(-m_x/2.0 ,m_y/2.0,0);

	msh_->vertexList().push_back(v1_);
	msh_->vertexList().push_back(v2_);
	msh_->vertexList().push_back(v3_);
	msh_->vertexList().push_back(v4_);

	Triangle* tr1_ = new Triangle(v1_,v2_,v3_);
	Triangle* tr2_ = new Triangle(v3_,v4_,v1_);

	msh_->faceList().push_back(tr1_);
	msh_->faceList().push_back(tr2_);

	msh_->calculatebounds();
}


