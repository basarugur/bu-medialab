


#ifndef BBOX_H
#define BBOX_H

#include "point3.h"

#include "ray.h"

class BBox 
{
public:
	BBox() {
		m_pmin = Point3(INFINITY,INFINITY,INFINITY);
		m_pmax = Point3(-INFINITY,-INFINITY,-INFINITY);
	};
	BBox(const Point3& p) : m_pmin(p),m_pmax(p) {};
	BBox(const Point3& p1,const Point3& p2) {

		m_pmin = Point3(std::min(p1.x(),p2.x()),
			std::min(p1.y(),p2.y()),
			std::min(p1.z(),p2.z()));

		m_pmax = Point3(std::max(p1.x(),p2.x()),
			std::max(p1.y(),p2.y()),
			std::max(p1.z(),p2.z()));
	};		

	bool inside(const Point3 &pt) const {
		return (pt.x() >= m_pmin.x() && pt.x() <= m_pmax.x() &&
			pt.y() >= m_pmin.y() && pt.y() <= m_pmax.y() &&
			pt.z() >= m_pmin.z() && pt.z() <= m_pmax.z());
	};

	Point3 min() const { return m_pmin; };
	Point3 max() const { return m_pmax; };

	bool intersectp(const Ray& ray,float *hitt0,float *hitt1) const {
		float t0 = ray.mint(), t1 = ray.maxt();

		for (int i = 0; i < 3; ++i) {
			float invRayDir = 1.f / ray.direction().v(i);
			float tNear = (m_pmin.v(i) - ray.origin().v(i))*invRayDir;
			float tFar  = (m_pmax.v(i) - ray.origin().v(i))*invRayDir;

			if (tNear > tFar) std::swap(tNear,tFar);
			t0 = tNear > t0 ? tNear : t0;
			t1 = tFar  < t1 ? tFar  : t1;
			if (t0 > t1) return false;
		}

		if (hitt0) *hitt0 = t0;
		if (hitt1) *hitt1 = t1;
		return true;
	};

private:
	Point3 m_pmin;
	Point3 m_pmax;
};


#endif