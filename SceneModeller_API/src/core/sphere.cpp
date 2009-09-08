#include "sphere.h"

BBox Sphere::object_bound() const
{
	return BBox(Point3(-m_r,-m_r,-m_r),Point3(m_r,m_r,m_r));
}

Shape* Sphere::getNewCopy()
{
    Sphere* sph_ = new Sphere();
    sph_->m_r = m_r;

    return sph_;
}

void Sphere::copyToMesh(TriangleMesh* msh_)
{
	double deltaSlicesAng_ = 0.0174532925*(double)360.0/(double)m_slices;
	double deltaStacksAng_ = 0.0174532925*(double)180.0/(double)m_stacks;

	double x_,y_,z_;
	z_ = m_r;

	double angle_,cosAng_,sinAng_;

	for(int i=0 ; i<m_stacks-1 ; i++)
	{
		angle_  = ((double)(i+1))*deltaStacksAng_;
		cosAng_ = cos(angle_);
		sinAng_ = sin(angle_);
		z_  = m_r*cosAng_;
		x_  = m_r*sinAng_;

		msh_->vertexList().push_back(new Vertex(0,x_,z_));
	}

	for(int i=1 ; i<m_slices ; i++)
	{
		for(int j=0 ; j<m_stacks-1 ; j++)
		{
			Vertex* vr_ = msh_->vertexList()[j];

			angle_  = ((double)i)*deltaSlicesAng_;
			cosAng_ = cos(angle_);
			sinAng_ = sin(angle_);
			y_ = vr_->y()*cosAng_;
			x_ = vr_->y()*sinAng_;

			msh_->vertexList().push_back(new Vertex(x_,y_,vr_->z()));
		}
	}

	for(int i=1 ; i< m_slices ; i++) // height
	{
		for(int j=0 ; j< m_stacks-2 ; j++ ) // circle
		{
			Vertex* v1_ = msh_->vertexList()[ (i-1)*(m_stacks-1)+j+1];
			Vertex* v2_ = msh_->vertexList()[ (i-1)*(m_stacks-1)+j];
			Vertex* v3_ = msh_->vertexList()[ i*(m_stacks-1)+j+1];
			Vertex* v4_ = msh_->vertexList()[ i*(m_stacks-1)+j];

			Triangle* tr1_ = new Triangle(v1_,v2_,v3_);
			Triangle* tr2_ = new Triangle(v2_,v4_,v3_);

			msh_->faceList().push_back(tr1_);
			msh_->faceList().push_back(tr2_);
		}
	}
	for(int j=0 ; j< m_stacks-2 ; j++ ) // circle
	{
		Vertex* v1_ = msh_->vertexList()[ j+1];
		Vertex* v2_ = msh_->vertexList()[ j];
		Vertex* v3_ = msh_->vertexList()[ (m_slices-1)*(m_stacks-1)+j+1];
		Vertex* v4_ = msh_->vertexList()[ (m_slices-1)*(m_stacks-1)+j];

		Triangle* tr1_ = new Triangle(v3_,v2_,v1_);
		Triangle* tr2_ = new Triangle(v3_,v4_,v2_);

		msh_->faceList().push_back(tr1_);
		msh_->faceList().push_back(tr2_);
	}


	Vertex* rot1_ =  new Vertex(0,0,m_r);
	for(int i=0 ; i< m_slices-1 ; i++) // height
	{
		Vertex* v1_ = msh_->vertexList()[i*(m_stacks-1)];
		Vertex* v2_ = msh_->vertexList()[(i+1)*(m_stacks-1)];

		msh_->faceList().push_back(new Triangle(rot1_,v2_,v1_));
	}
	msh_->vertexList().push_back(rot1_);
	msh_->faceList().push_back(new Triangle(rot1_,
		msh_->vertexList()[0],
		msh_->vertexList()[(m_slices-1)*(m_stacks-1)]));

	Vertex* rot2_ =  new Vertex(0,0,-m_r);
	for(int i=0 ; i< m_slices-1 ; i++) // height
	{
		Vertex* v1_ = msh_->vertexList()[i*(m_stacks-1)+(m_stacks-2)];
		Vertex* v2_ = msh_->vertexList()[(i+1)*(m_stacks-1)+(m_stacks-2)];

		msh_->faceList().push_back(new Triangle(rot2_,v1_,v2_));
	}
	msh_->vertexList().push_back(rot2_);
	msh_->faceList().push_back(new Triangle(rot2_,
		msh_->vertexList()[(m_slices-1)*(m_stacks-1)+(m_stacks-2)],
		msh_->vertexList()[(m_stacks-2)]
		));

	msh_->calculatebounds();
}

void Sphere::draw( drawType dt_ )
{

    if ( dt_ & SHADED )
        glutSolidSphere( m_r, m_slices, m_stacks );

    if ( dt_ & WIRED )
        glutWireSphere( m_r, m_slices, m_stacks );

}
