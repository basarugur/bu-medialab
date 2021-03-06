#include "twosidedcylinder.h"

BBox TwoSidedCylinder::object_bound() const
{
	double maxR =std::max(m_base_r,m_top_r);
	return BBox(Point3(-maxR,-maxR,0),Point3(maxR,maxR,m_h));
}

Shape* TwoSidedCylinder::getNewCopy()
{
    TwoSidedCylinder* tsc_ = new TwoSidedCylinder();
    tsc_->m_base_r = m_base_r;
    tsc_->m_top_r = m_top_r;
    tsc_->m_h = m_h;
    tsc_->m_slices = m_slices;
    tsc_->m_stacks = m_stacks;

    return tsc_;
}

void TwoSidedCylinder::copyToMesh(TriangleMesh* msh_)
{
	double deltaAng_ = 0.0174532925*(double)360.0/(double)m_slices;
	double deltaHgh_ = m_h / (double)m_stacks;

	double angle_,cosAng_,sinAng_;
	double x_ , y_ ;
	x_ = 0;
	y_ = m_base_r;

	double delraR_ = (m_top_r-m_base_r)/(double)m_stacks;

	for(int j=0 ; j< m_slices ; j++ ) // circle
	{
		Vertex* vrt_ = new Vertex(x_,y_,0);
		msh_->vertexList().push_back(vrt_);

		angle_  = ((double)(j+1))*deltaAng_;
		cosAng_ = cos(angle_);
		sinAng_ = sin(angle_);

		y_ = m_base_r*cosAng_;
		x_ = m_base_r*sinAng_;
	}

	for(int i=1 ; i<= m_stacks ; i++) // height
	{
		y_ = m_base_r+delraR_*i;
		x_ = 0;
		for(int j=0 ; j< m_slices ; j++ ) // circle
		{
			Vertex* bs_ = msh_->vertexList()[(i-1)*m_slices+j];
			Vertex* v1_ = new Vertex(x_,y_,bs_->z()+deltaHgh_);

			msh_->vertexList().push_back(v1_);

			angle_  = ((double)(j+1))*deltaAng_;
			cosAng_ = cos(angle_);
			sinAng_ = sin(angle_);

			y_ = (m_base_r+delraR_*i)*cosAng_;
			x_ = (m_base_r+delraR_*i)*sinAng_;

		}
	}

	for(int i=1 ; i<= m_stacks ; i++) // height
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

	Vertex* bse_ = new Vertex(0,0,0);
	Vertex* top_ = new Vertex(0,0,m_h);
	for (int i=1; i<m_slices ; i++)
	{
		msh_->faceList().push_back(
			new Triangle(
			msh_->vertexList()[i],
			bse_,
			msh_->vertexList()[i-1]));

		msh_->faceList().push_back(
			new Triangle(
			msh_->vertexList()[msh_->vertexList().size()-i-1],
			top_,
			msh_->vertexList()[msh_->vertexList().size()-i]));
	}
	msh_->faceList().push_back(
		new Triangle(msh_->vertexList()[0],
		bse_,
		msh_->vertexList()[m_slices-1]));

	msh_->faceList().push_back(
		new Triangle(msh_->vertexList()[msh_->vertexList().size()-1],
		top_,
		msh_->vertexList()[msh_->vertexList().size()-m_slices]));

	msh_->vertexList().push_back(bse_);
	msh_->vertexList().push_back(top_);

	msh_->calculatebounds();
}

void TwoSidedCylinder::draw( drawType dt_ )
{
    if ( dt_ & SHADED )
    {
        gluQuadricDrawStyle( p_qdr, GLU_FILL );

        gluCylinder(p_qdr, m_base_r, m_top_r, m_h, m_slices, m_stacks);
        gluDisk(p_qdr, 0, m_base_r, m_slices, 1);
        glTranslatef(0, 0, m_h);
        gluDisk(p_qdr, 0, m_top_r, m_slices, 1);
        glTranslatef(0, 0,-m_h);
    }

    if ( dt_ & WIRED )
    {
        gluQuadricDrawStyle( p_qdr, GLU_LINE );

        gluCylinder(p_qdr, m_base_r, m_top_r, m_h, m_slices, m_stacks);
        gluDisk(p_qdr, 0, m_base_r, m_slices, 1);
        glTranslatef(0, 0, m_h);
        gluDisk(p_qdr, 0, m_top_r, m_slices, 1);
        glTranslatef(0, 0,-m_h);
    }

}
