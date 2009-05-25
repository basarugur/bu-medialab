
#ifndef DIFF_GEOM_H
#define DIFF_GEOM_H

#include "vector3.h"
#include "point3.h"
#include "normal3.h"
#include "shape.h"
#include <float.h>
#include <algorithm>

class Triangle;

class DifferentialGeometry 
{
public:
	DifferentialGeometry() { 
		m_u = 0.0;
		m_v = 0.0;
		m_shape = NULL;
	}

	DifferentialGeometry(const Point3& p, const Vector3& dpdu,
		const Vector3& dpdv,const Shape* s, float u=0.0, float v=0.0,float w=0.0)
		: m_p(p),m_dpdu(dpdu),m_dpdv(dpdv)
	{
		Vector3 vv = (dpdu ^ dpdv).normalize();
		m_n = Normal3(vv.x(),vv.y(),vv.z());
		m_u = u;
		m_v = v;
		m_w = w;
		m_shape = s;
	}

	void set_material(Material* m) { m_material = m; };
	Material* material() const { return m_material; };
	void setnormal(const Normal3& normal) const { m_n = normal; };
	void setp(const Point3& point) const { m_p = point; };
	void setuv(const Vector3& u,const Vector3&  v) { m_dpdu = u; m_dpdv = v; };	
	void setuv(float u,float v,float w) { m_u = u; m_v = v; m_w = w; };
	const Normal3& n() const { return m_n; };
	const Point3& p() const { return m_p; };
	float u() const { return m_u; };
	float v() const { return m_v; };
	float w() const { return m_w; };

private:
	mutable Point3 m_p;
	mutable Normal3 m_n;
	Material* m_material;
	Vector3 m_dpdu,m_dpdv;			
	const Shape* m_shape;
	float m_u,m_v,m_w;
};

#endif