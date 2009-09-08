#include "torus.h"

BBox Torus::object_bound() const
{
	return BBox(Point3(-m_out_r,-m_out_r,-m_in_r),Point3(m_out_r,m_out_r,m_in_r));
}

Shape* Torus::getNewCopy()
{
    Torus* trs_ = new Torus();
    trs_->m_in_r = m_in_r;
    trs_->m_out_r = m_out_r;
    trs_->m_rings = m_rings;
    trs_->m_sides = m_sides;

    return trs_;
}

void Torus::copyToMesh(TriangleMesh* msh_)
{
	double deltaSlcAng_ = 0.0174532925*(double)360.0/(double)m_sides;
	double deltaRngAng_ = 0.0174532925*(double)360.0/(double)m_rings;

	double angle_,cosAng_,sinAng_;
	double x_ , z_ , y_;
	x_ = m_in_r;
	z_ = 0;
	for(int j=0 ; j< m_sides ; j++ ) // circle
	{
		Vertex* vrt_ = new Vertex(x_+m_out_r,0,z_);
		msh_->vertexList().push_back(vrt_);

		angle_  = ((double)(j+1))*deltaSlcAng_;
		cosAng_ = cos(angle_);
		sinAng_ = sin(angle_);

		x_ = m_in_r*cosAng_;
		z_ = m_in_r*sinAng_;
	}

	for(int i=1 ; i<m_rings ; i++ )
	{
		for(int j=0 ; j< m_sides ; j++ ) // circle
		{
			Vertex* vr1_ = msh_->vertexList()[j];

			angle_  = ((double)(i))*deltaRngAng_;
			cosAng_ = cos(angle_);
			sinAng_ = sin(angle_);

			x_ = vr1_->x()*cosAng_;
			y_ = vr1_->x()*sinAng_;

			msh_->vertexList().push_back(new Vertex(x_,y_,vr1_->z()));
		}
	}

	for(int i=1 ; i< m_rings ; i++) // height
	{
		for(int j=0 ; j< m_sides-1 ; j++ ) // circle
		{
			Vertex* v1_ = msh_->vertexList()[ (i-1)*m_sides+j+1];
			Vertex* v2_ = msh_->vertexList()[ (i-1)*m_sides+j];
			Vertex* v3_ = msh_->vertexList()[ i*m_sides+j+1];
			Vertex* v4_ = msh_->vertexList()[ i*m_sides+j];

			Triangle* tr1_ = new Triangle(v3_,v2_,v1_);
			Triangle* tr2_ = new Triangle(v3_,v4_,v2_);

			msh_->faceList().push_back(tr1_);
			msh_->faceList().push_back(tr2_);
		}
		Vertex* v1_ = msh_->vertexList()[ (i-1)*m_sides];
		Vertex* v2_ = msh_->vertexList()[ (i-1)*m_sides+m_sides-1];
		Vertex* v3_ = msh_->vertexList()[ i*m_sides];
		Vertex* v4_ = msh_->vertexList()[ i*m_sides+m_sides-1];

		Triangle* tr1_ = new Triangle(v3_,v2_,v1_);
		Triangle* tr2_ = new Triangle(v3_,v4_,v2_);

		msh_->faceList().push_back(tr1_);
		msh_->faceList().push_back(tr2_);
	}
	//
	for(int j=0 ; j< m_sides-1 ; j++ ) // circle
	{
		Vertex* v1_ = msh_->vertexList()[ (m_rings-1)*m_sides+j+1];
		Vertex* v2_ = msh_->vertexList()[ (m_rings-1)*m_sides+j];
		Vertex* v3_ = msh_->vertexList()[ 0*m_sides+j+1];
		Vertex* v4_ = msh_->vertexList()[ 0*m_sides+j];

		Triangle* tr1_ = new Triangle(v3_,v2_,v1_);
		Triangle* tr2_ = new Triangle(v3_,v4_,v2_);

		msh_->faceList().push_back(tr1_);
		msh_->faceList().push_back(tr2_);
	}
	Vertex* v1_ = msh_->vertexList()[ (m_rings-1)*m_sides];
	Vertex* v2_ = msh_->vertexList()[ (m_rings-1)*m_sides+m_sides-1];
	Vertex* v3_ = msh_->vertexList()[ 0*m_sides];
	Vertex* v4_ = msh_->vertexList()[ 0*m_sides+m_sides-1];

	Triangle* tr1_ = new Triangle(v3_,v2_,v1_);
	Triangle* tr2_ = new Triangle(v3_,v4_,v2_);

	msh_->faceList().push_back(tr1_);
	msh_->faceList().push_back(tr2_);

	msh_->calculatebounds();
}

void Torus::draw( drawType dt_ )
{
    if ( dt_ & SHADED )
    {
        glutSolidTorus( m_in_r, m_out_r, m_sides, m_rings );
    }

    if ( dt_ & WIRED )
    {
        glutWireTorus( m_in_r, m_out_r, m_sides, m_rings );
    }

}


