#include "cone.h"

BBox Cone::object_bound() const 
{
	return BBox(Point3(-m_r,-m_r,0),Point3(m_r,m_r,m_h));
}
void Cone::copyToMesh(TriangleMesh* msh_)
{
	double deltaAng_ = 0.0174532925*(double)360.0/(double)m_slices;
	double deltaHgh_ = m_h / (double)m_stacks;

	double angle_,cosAng_,sinAng_;
	double x_ , y_ ; 
	x_ = 0;
	y_ = m_r;

	double topR_ = m_r/m_stacks;

	double stacks_ = m_stacks-1;

	double delraR_ = (topR_-m_r)/(double)stacks_;

	for(int j=0 ; j< m_slices ; j++ ) // circle
	{
		Vertex* vrt_ = new Vertex(x_,y_,0);
		msh_->vertexList().push_back(vrt_);

		angle_  = ((double)(j+1))*deltaAng_;
		cosAng_ = cos(angle_);
		sinAng_ = sin(angle_);

		y_ = m_r*cosAng_;
		x_ = m_r*sinAng_;
	}

	for(int i=1 ; i<= stacks_ ; i++) // height
	{
		x_ = 0;
		y_ = m_r+delraR_*i;
		for(int j=0 ; j< m_slices ; j++ ) // circle
		{
			Vertex* bs_ = msh_->vertexList()[(i-1)*m_slices+j];
			Vertex* v1_ = new Vertex(x_,y_,bs_->z()+deltaHgh_);

			msh_->vertexList().push_back(v1_);

			angle_  = ((double)(j+1))*deltaAng_;
			cosAng_ = cos(angle_);
			sinAng_ = sin(angle_);

			y_ = (m_r+delraR_*i)*cosAng_;
			x_ = (m_r+delraR_*i)*sinAng_;

		}
	}

	for(int i=1 ; i<= stacks_ ; i++) // height
	{
		for(int j=0 ; j< m_slices-1 ; j++ ) // circle
		{
			Vertex* v1_ = msh_->vertexList()[ (i-1)*m_slices+j+1];
			Vertex* v2_ = msh_->vertexList()[ (i-1)*m_slices+j];
			Vertex* v3_ = msh_->vertexList()[ i*m_slices+j+1];
			Vertex* v4_ = msh_->vertexList()[ i*m_slices+j];

			Triangle* tr1_ = new Triangle(v1_,v2_,v3_);
			Triangle* tr2_ = new Triangle(v2_,v4_,v3_);

			msh_->faceList().push_back(tr1_);
			msh_->faceList().push_back(tr2_);
		}
		Vertex* v1_ = msh_->vertexList()[ (i-1)*m_slices];
		Vertex* v2_ = msh_->vertexList()[ (i-1)*m_slices+m_slices-1];
		Vertex* v3_ = msh_->vertexList()[ i*m_slices];
		Vertex* v4_ = msh_->vertexList()[ i*m_slices+m_slices-1];

		Triangle* tr1_ = new Triangle(v1_,v2_,v3_);
		Triangle* tr2_ = new Triangle(v2_,v4_,v3_);

		msh_->faceList().push_back(tr1_);
		msh_->faceList().push_back(tr2_);
	}

	Vertex* topVer_ = new Vertex(0,0,m_h);

	for(int j=0 ; j< m_slices-1 ; j++ ) // circle
	{
		Vertex* v1_ = msh_->vertexList()[msh_->vertexList().size()-(j+1)];
		Vertex* v2_ = msh_->vertexList()[msh_->vertexList().size()-(j+2)];
		Triangle* tr1_ = new Triangle(topVer_,v1_,v2_);
		msh_->faceList().push_back(tr1_);
	}
	Vertex* v1_ = msh_->vertexList()[msh_->vertexList().size()-1];
	Vertex* v2_ = msh_->vertexList()[msh_->vertexList().size()-(m_slices) ];
	Triangle* tr1_ = new Triangle(topVer_,v2_,v1_);
	msh_->faceList().push_back(tr1_);

	msh_->vertexList().push_back(topVer_);


	Vertex* bse_ = new Vertex(0,0,0);
	for (int i=1; i<m_slices ; i++)
	{
		msh_->faceList().push_back(
			new Triangle(
			msh_->vertexList()[i],
			bse_,
			msh_->vertexList()[i-1]));
	}
	msh_->faceList().push_back(
		new Triangle(msh_->vertexList()[0],
		bse_,
		msh_->vertexList()[m_slices-1]));
	msh_->vertexList().push_back(bse_);


	msh_->calculatebounds();
}