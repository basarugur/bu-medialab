#include "triangleshape.h"

BBox TriangleShape::object_bound() const
{
	double maxX = std::max(m_p1.x(),std::max(m_p2.x(),m_p3.x()));
	double maxY = std::max(m_p1.y(),std::max(m_p2.y(),m_p3.y()));
	double maxZ = std::max(m_p1.z(),std::max(m_p2.z(),m_p3.z()));

	double minX = std::min(m_p1.x(),std::min(m_p2.x(),m_p3.x()));
	double minY = std::min(m_p1.y(),std::min(m_p2.y(),m_p3.y()));
	double minZ = std::min(m_p1.z(),std::min(m_p2.z(),m_p3.z()));
	return BBox(Point3(minX,minY,minZ),Point3(maxX,maxY,maxZ));
}

void TriangleShape::copyToMesh(TriangleMesh* msh_)
{
	Vertex* v1_ = new Vertex(m_p1.x(),m_p1.y(),m_p1.z());
	Vertex* v2_ = new Vertex(m_p2.x(),m_p2.y(),m_p2.z());
	Vertex* v3_ = new Vertex(m_p3.x(),m_p3.y(),m_p3.z());

	Triangle* newTri_  = new Triangle();
	newTri_->m_a = v1_;
	newTri_->m_b = v2_;
	newTri_->m_c = v3_;
	newTri_->restoreNormalAndMidPoint();

	msh_->faceList().push_back(newTri_);
	msh_->vertexList().push_back(v1_);
	msh_->vertexList().push_back(v2_);
	msh_->vertexList().push_back(v3_);

	msh_->calculatebounds();
}

void TriangleShape::draw( drawType dt_ )
{
    if ( dt_ & SHADED )
    {
        glBegin(GL_TRIANGLES);
		glVertex3f( m_p1.x(), m_p1.y(), m_p1.z() );
		glVertex3f( m_p2.x(), m_p2.y(), m_p2.z() );
		glVertex3f( m_p3.x(), m_p3.y(), m_p3.z() );
		glEnd();
    }

    if ( dt_ & WIRED )
    {
        glBegin(GL_LINE_LOOP);
		glVertex3f( m_p1.x(), m_p1.y(), m_p1.z() );
		glVertex3f( m_p2.x(), m_p2.y(), m_p2.z() );
		glVertex3f( m_p3.x(), m_p3.y(), m_p3.z() );
		glEnd();
    }
}
