#include "circle.h"

BBox Circle::object_bound() const
{
	return BBox(Point3(-m_r,-m_r,0),Point3(m_r,m_r,0));
}

Shape* Circle::getNewCopy()
{
    Circle* c_ = new Circle();
    c_->m_r = m_r;
    c_->m_loops = m_loops;
    c_->m_slices = m_slices;

    return c_;
}

void Circle::copyToMesh(TriangleMesh* msh_)
{
	double inR_ = m_r/(double)m_loops;
	int loops_ = m_loops-1;
	double deltaSlicesAng_ = 0.0174532925*(double)360.0/(double)m_slices;
	double deltaR_ = (m_r-inR_)/(double)loops_;

	double angle_,cosAng_,sinAng_;
	double x_ , y_;
	x_ = inR_;
	y_ = 0;
	for(int j=0 ; j<= loops_ ; j++ ) // circle
	{
		Vertex* vrt_ = new Vertex(0,x_+deltaR_*j,0);
		msh_->vertexList().push_back(vrt_);
	}

	for(int i=1 ; i<m_slices ; i++)
	{
		for(int j=0 ; j<= loops_ ; j++)
		{
			Vertex* vr1_ = msh_->vertexList()[j];

			angle_  = (double)(i)*deltaSlicesAng_;
			cosAng_ = cos(angle_);
			sinAng_ = sin(angle_);

			y_ = vr1_->y()*cosAng_;
			x_ = vr1_->y()*sinAng_;

			msh_->vertexList().push_back(new Vertex(x_,y_,0));
		}
	}

	for(int i=1 ; i< m_slices ; i++) // height
	{
		for(int j=0 ; j<= loops_-1 ; j++ ) // circle
		{
			Vertex* v1_ = msh_->vertexList()[ (i-1)*(loops_+1)+j+1];
			Vertex* v2_ = msh_->vertexList()[ (i-1)*(loops_+1)+j];
			Vertex* v3_ = msh_->vertexList()[ i*(loops_+1)+j+1];
			Vertex* v4_ = msh_->vertexList()[ i*(loops_+1)+j];

			Triangle* tr1_ = new Triangle(v1_,v2_,v3_);
			Triangle* tr2_ = new Triangle(v2_,v4_,v3_);

			msh_->faceList().push_back(tr1_);
			msh_->faceList().push_back(tr2_);
		}
	}
	for(int j=0 ; j<= loops_-1 ; j++ ) // circle
	{
		Vertex* v1_ = msh_->vertexList()[ (m_slices-1)*(loops_+1)+j+1];
		Vertex* v2_ = msh_->vertexList()[ (m_slices-1)*(loops_+1)+j];
		Vertex* v3_ = msh_->vertexList()[ j+1];
		Vertex* v4_ = msh_->vertexList()[ j];

		Triangle* tr1_ = new Triangle(v1_,v2_,v3_);
		Triangle* tr2_ = new Triangle(v2_,v4_,v3_);

		msh_->faceList().push_back(tr1_);
		msh_->faceList().push_back(tr2_);
	}

	Vertex* root_ = new Vertex(0,0,0);
	for(int i=1 ; i< m_slices ; i++) // height
	{
		Vertex* v1_ = msh_->vertexList()[(i-1)*m_loops];
		Vertex* v2_ = msh_->vertexList()[i*m_loops];

		msh_->faceList().push_back(new Triangle(root_,v2_,v1_));
	}

	Vertex* v1_ = msh_->vertexList()[0];
	Vertex* v2_ = msh_->vertexList()[(m_slices-1)*m_loops];
	msh_->faceList().push_back(new Triangle(root_,v1_,v2_));

	msh_->vertexList().push_back(root_);

	msh_->calculatebounds();

}


void Circle::draw( drawType dt_ )
{
    if ( dt_ & SHADED )
    {
        gluQuadricDrawStyle( p_qdr, GLU_FILL );

        gluDisk(p_qdr, 0, m_r, m_slices, m_loops );
    }

    if ( dt_ & WIRED )
    {
        gluQuadricDrawStyle( p_qdr, GLU_LINE );

        gluDisk(p_qdr, 0, m_r, m_slices, m_loops );
    }
}
