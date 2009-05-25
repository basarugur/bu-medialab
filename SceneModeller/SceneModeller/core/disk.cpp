#include "disk.h"

BBox Disk::object_bound() const 
{
	return BBox(Point3(-m_out_r,-m_out_r,0),Point3(m_out_r,m_out_r,0));
}

void Disk::copyToMesh(TriangleMesh* msh_)
{
	double deltaSlicesAng_ = 0.0174532925*(double)360.0/(double)m_slices;
	double deltaR_ = (m_out_r-m_in_r)/(double)m_loops;

	double angle_,cosAng_,sinAng_;
	double x_ , y_; 
	x_ = m_in_r;
	y_ = 0;
	for(int j=0 ; j<= m_loops ; j++ ) // circle
	{
		Vertex* vrt_ = new Vertex(x_+deltaR_*j,0,0);
		msh_->vertexList().push_back(vrt_);
	}

	for(int i=1 ; i<m_slices ; i++)
	{
		for(int j=0 ; j<= m_loops ; j++)
		{
			Vertex* vr1_ = msh_->vertexList()[j]; 

			angle_  = (double)(i)*deltaSlicesAng_;
			cosAng_ = cos(angle_);
			sinAng_ = sin(angle_);

			x_ = vr1_->x()*cosAng_;
			y_ = vr1_->x()*sinAng_;

			msh_->vertexList().push_back(new Vertex(x_,y_,0));
		}
	}

	for(int i=1 ; i< m_slices ; i++) // height
	{
		for(int j=0 ; j<= m_loops-1 ; j++ ) // circle
		{
			Vertex* v1_ = msh_->vertexList()[ (i-1)*(m_loops+1)+j+1];
			Vertex* v2_ = msh_->vertexList()[ (i-1)*(m_loops+1)+j];
			Vertex* v3_ = msh_->vertexList()[ i*(m_loops+1)+j+1];
			Vertex* v4_ = msh_->vertexList()[ i*(m_loops+1)+j];

			Triangle* tr1_ = new Triangle(v1_,v2_,v3_);
			Triangle* tr2_ = new Triangle(v3_,v4_,v2_);

			msh_->faceList().push_back(tr1_);
			msh_->faceList().push_back(tr2_);
		}
	}
	for(int j=0 ; j<= m_loops-1 ; j++ ) // circle
	{
		Vertex* v1_ = msh_->vertexList()[ (m_slices-1)*(m_loops+1)+j+1];
		Vertex* v2_ = msh_->vertexList()[ (m_slices-1)*(m_loops+1)+j];
		Vertex* v3_ = msh_->vertexList()[ j+1];
		Vertex* v4_ = msh_->vertexList()[ j];

		Triangle* tr1_ = new Triangle(v1_,v2_,v3_);
		Triangle* tr2_ = new Triangle(v3_,v4_,v2_);

		msh_->faceList().push_back(tr1_);
		msh_->faceList().push_back(tr2_);
	}

	msh_->calculatebounds();
}


