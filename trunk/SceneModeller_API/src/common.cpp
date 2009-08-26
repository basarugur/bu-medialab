#include "common.h"

#include "./core/vector3.h"

// non member function

Vector3 RotateVectorAroundVector(Vector3 trg_,Vector3 bse_,double angle)
{
	double x = trg_.x() ;
	double y = trg_.y() ;
	double z = trg_.z() ;
	double u = bse_.x() ;
	double v = bse_.y() ;
	double w = bse_.z() ;
	double ux=u*x ;
	double uy=u*y ;
	double uz=u*z ;
	double vx=v*x ;
	double vy=v*y ;
	double vz=v*z ;
	double wx=w*x ;
	double wy=w*y ;
	double wz=w*z ;
	double sa = sin(angle);
	double ca = cos(angle);

	x = u*(ux+vy+wz)+(x*(v*v+w*w)-u*(vy+wz))*ca+(-wy+vz)*sa;
	y = v*(ux+vy+wz)+(y*(u*u+w*w)-v*(ux+wz))*ca+(wx-uz)*sa;
	z = w*(ux+vy+wz)+(z*(u*u+v*v)-w*(ux+vy))*ca+(-vx+uy)*sa;

	return Vector3(x,y,z);
}
