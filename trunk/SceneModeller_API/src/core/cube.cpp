#include "cube.h"

BBox Cube::object_bound() const
{
	return BBox(Point3(-m_d/2.0,-m_d/2.0,-m_d/2.0),Point3(m_d/2.0,m_d/2.0,m_d/2.0));
}

Shape* Cube::getNewCopy()
{
    Cube* c_ = new Cube();
    c_->m_d = m_d;

    return c_;
}

void Cube::copyToMesh(TriangleMesh* msh_)
{
	Vertex* v0_ = new Vertex(m_d/2,m_d/2,m_d/2);
	Vertex* v1_ = new Vertex(m_d/2,m_d/2,-m_d/2);
	Vertex* v2_ = new Vertex(m_d/2,-m_d/2,m_d/2);
	Vertex* v3_ = new Vertex(m_d/2,-m_d/2,-m_d/2);
	Vertex* v4_ = new Vertex(-m_d/2,m_d/2,m_d/2);
	Vertex* v5_ = new Vertex(-m_d/2,m_d/2,-m_d/2);
	Vertex* v6_ = new Vertex(-m_d/2,-m_d/2,m_d/2);
	Vertex* v7_ = new Vertex(-m_d/2,-m_d/2,-m_d/2);

	msh_->vertexList().push_back(v0_);
	msh_->vertexList().push_back(v1_);
	msh_->vertexList().push_back(v2_);
	msh_->vertexList().push_back(v3_);
	msh_->vertexList().push_back(v4_);
	msh_->vertexList().push_back(v5_);
	msh_->vertexList().push_back(v6_);
	msh_->vertexList().push_back(v7_);

	Triangle* tr1_ = new Triangle(v0_,v1_,v2_);
	Triangle* tr2_ = new Triangle(v3_,v2_,v1_);
	Triangle* tr3_ = new Triangle(v6_,v5_,v4_);
	Triangle* tr4_ = new Triangle(v5_,v6_,v7_);
	Triangle* tr5_ = new Triangle(v4_,v1_,v0_);
	Triangle* tr6_ = new Triangle(v1_,v4_,v5_);
	Triangle* tr7_ = new Triangle(v2_,v3_,v6_);
	Triangle* tr8_ = new Triangle(v7_,v6_,v3_);
	Triangle* tr9_ = new Triangle(v0_,v2_,v4_);
	Triangle* tr10_ = new Triangle(v6_,v4_,v2_);

	Triangle* tr11_ = new Triangle(v5_,v3_,v1_);
	Triangle* tr12_ = new Triangle(v3_,v5_,v7_);

	msh_->faceList().push_back(tr1_);
	msh_->faceList().push_back(tr2_);
	msh_->faceList().push_back(tr3_);
	msh_->faceList().push_back(tr4_);
	msh_->faceList().push_back(tr5_);
	msh_->faceList().push_back(tr6_);
	msh_->faceList().push_back(tr7_);
	msh_->faceList().push_back(tr8_);
	msh_->faceList().push_back(tr9_);
	msh_->faceList().push_back(tr10_);
	msh_->faceList().push_back(tr11_);
	msh_->faceList().push_back(tr12_);

	msh_->calculatebounds();
}

void Cube::draw( drawType dt_ )
{

    if ( dt_ & SHADED )
        glutSolidCube( m_d );

    if ( dt_ & WIRED )
        glutWireCube( m_d );

}
