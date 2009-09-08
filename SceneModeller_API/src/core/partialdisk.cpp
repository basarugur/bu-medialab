#include "partialdisk.h"

BBox PartialDisk::object_bound() const
{
	return  BBox(Point3(-m_out_r,-m_out_r,0),Point3(m_out_r,m_out_r,0));
}

Shape* PartialDisk::getNewCopy()
{
    PartialDisk* pd_ = new PartialDisk();
    pd_->m_in_r = m_in_r;
    pd_->m_out_r = m_out_r;
    pd_->m_loops = m_loops;
    pd_->m_slices = m_slices;
    pd_->start_ang = start_ang;
    pd_->sweep_ang = sweep_ang;

    return pd_;
}

void PartialDisk::copyToMesh(TriangleMesh* msh_)
{
	double deltaSlicesAng_ = 0.0174532925*(double)-sweep_ang/(double)m_slices;
	double strtAngle_ = 0.0174532925*(-start_ang-90) ;
	double deltaR_ = (m_out_r-m_in_r)/(double)m_loops;

	double angle_,cosAng_,sinAng_;
	double x_ , y_;
	x_ = m_in_r;
	y_ = 0;

	angle_  = strtAngle_;
	cosAng_ = cos(angle_);
	sinAng_ = sin(angle_);

	for(int j=0 ; j<= m_loops ; j++ ) // circle
	{
		x_ = (m_in_r+(double)j*deltaR_)*cosAng_;
		y_ = (m_in_r+(double)j*deltaR_)*sinAng_;

		Vertex* vrt_ = new Vertex(-x_,-y_,0);
		msh_->vertexList().push_back(vrt_);
	}

	for(int i=1 ; i<=m_slices ; i++)
	{
		for(int j=0 ; j<= m_loops ; j++)
		{
			Vertex* vr1_ = msh_->vertexList()[j];

			angle_  = (double)(i)*deltaSlicesAng_;
			cosAng_ = cos(angle_);
			sinAng_ = sin(angle_);

			x_ = vr1_->x()*cosAng_ - vr1_->y()*sinAng_;
			y_ = vr1_->x()*sinAng_ + vr1_->y()*cosAng_;

			msh_->vertexList().push_back(new Vertex(x_,y_,0));
		}
	}

	for(int i=1 ; i<= m_slices ; i++) // height
	{
		for(int j=0 ; j< m_loops ; j++ ) // circle
		{
			Vertex* v1_ = msh_->vertexList()[ (i-1)*(m_loops+1)+j+1];
			Vertex* v2_ = msh_->vertexList()[ (i-1)*(m_loops+1)+j];
			Vertex* v3_ = msh_->vertexList()[ i*(m_loops+1)+j+1];
			Vertex* v4_ = msh_->vertexList()[ i*(m_loops+1)+j];

			Triangle* tr1_ = new Triangle(v1_,v2_,v3_);
			Triangle* tr2_ = new Triangle(v2_,v4_,v3_);

			msh_->faceList().push_back(tr1_);
			msh_->faceList().push_back(tr2_);
		}
	}

	msh_->calculatebounds();
}

void PartialDisk::draw( drawType dt_ )
{
    if ( dt_ & SHADED )
    {
        gluQuadricDrawStyle( p_qdr, GLU_FILL );

        gluPartialDisk(p_qdr, m_in_r, m_out_r, m_slices, m_loops, start_ang, sweep_ang);
    }

    if ( dt_ & WIRED )
    {
        gluQuadricDrawStyle( p_qdr, GLU_LINE );

        gluPartialDisk(p_qdr, m_in_r, m_out_r, m_slices, m_loops, start_ang, sweep_ang);
    }
}
