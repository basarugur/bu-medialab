#include "triangle.h"
#include "diffgeometry.h"

//Fast minimum storage ray / triangle intersection. ( Tomas Moller )
bool Triangle::intersect(const Ray& r,float *hit,DifferentialGeometry* dg) const
{
	Vector3 dir = r.direction();
	Vector3 org(r.origin().x(),r.origin().y(),r.origin().z());
	Vector3 e1 = (m_v[1] - m_v[0]);
	Vector3 e2 = (m_v[2] - m_v[0]);
	Vector3 pvec = dir ^ e2;
	double det = e1 * pvec;

	//(det > -ZERO && det < ZERO)
	if (det == 0) {
		dg = NULL;
		*hit = 1e30;				
		return false;
	}

	double inv_det = 1.0 / det;
	Vector3 tvec = org - m_v[0];
	double u = (tvec * pvec) * inv_det;

	if ((u<0.0) || (u>1.0)) {
		dg = NULL;
		*hit = 1e30;				
		return false;
	}

	Vector3 qvec = tvec ^ e1;
	double v = (dir * qvec) * inv_det;

	if ((v<0.0) || ((v+u)>1.0)) {
		dg = NULL;
		*hit = 1e30;				
		return false;
	}

	double t = (e2 * qvec)*inv_det;
	//face forwarding
	Normal3 fn;

	if (n()*r.direction()>0) fn = Normal3(-n().x(),-n().y(),-n().z()); 
	else fn = Normal3(n().x(),n().y(),n().z());
	Point3 p = r.origin() + (r.direction()*t);

	float u_ = p.x() - m_box.min().x();
	float v_ = p.y() - m_box.min().y();
	float w_ = p.z() - m_box.min().z();

	dg->setp(p);
	dg->setnormal(fn);
	dg->set_material(m_material);				
	dg->setuv(u_,v_,w_);
	*hit = t;
	return true;
};
