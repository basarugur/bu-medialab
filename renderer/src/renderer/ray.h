//Author: Ufuk Tiryaki @ 2009
//Desc:

#ifndef RAY_H
#define RAY_H

#include "vector3.h"
#include "point3.h"
#include "normal3.h"
#include <float.h>
#include <algorithm>

namespace scene
{
	class Ray
	{
		public:	
			Ray() : m_mint(RAY_EPSILON),m_maxt(RAY_INFINITY)
			{};
			Ray(const space::Point3& o,const space::Vector3& v,double min=RAY_EPSILON,double max=RAY_INFINITY)
				: m_origin(o),m_mint(min),m_maxt(max)
			{
				m_dir = v.normalize();
				m_inv_dir = space::Vector3(1.f/m_dir.x(),1.f/m_dir.y(),1.f/m_dir.z());

				m_sign[0] = (m_inv_dir.x() < 0);
				m_sign[1] = (m_inv_dir.y() < 0);
				m_sign[2] = (m_inv_dir.z() < 0);

				m_mint = 0;
				m_maxt = 1e30;

				m_index_of_refraction = 1.0;
			};
			
			int sign(int i) const { return m_sign[i]; };
			double mint() const { return m_mint; };
			double maxt() const { return m_maxt; };
			void set_mint(double p) const { m_mint = p; };
			void set_maxt(double p) const { m_maxt = p; };

			const space::Point3& origin() const { return m_origin; };
			const space::Vector3& direction() const { return m_dir; };
			const space::Vector3& inv_direction() const { return m_inv_dir; };
			void set_origin(const space::Point3& o) const { m_origin = o; };
			void set_direction(const space::Vector3& v) const { m_dir = v; };
			const space::Point3& hitpoint() const { return m_hitpoint; };
			void set_hit(const space::Point3& p) const { m_hitpoint = p; };
			double refraction_index() const { return m_index_of_refraction; };
			void set_refraction_index(double r) { m_index_of_refraction = r; };

			Ray reflect(const space::Normal3& n,const space::Point3& p) const {								
				
				space::Vector3 rv = m_dir - 2*n*(m_dir*n);
				return Ray(p,rv);				
			}

			Ray refract(const space::Normal3& n,const space::Point3& p,double n1,double n2,bool& reflected) const {
				
				double nn  = (n1/n2);
				double cost  = ((m_dir*n)/(m_dir.length()*n.length()));
				double sint2 = nn*nn*(1.0 - cost*cost);
				
				if(sint2 <= 1.0) {			
					reflected = false;
					space::Vector3 rv = (m_dir*nn) - (nn*cost + sqrt(1-sint2))*n;
					return Ray(p,rv);
				} else {
					reflected = true;
					return reflect(n,p);
				}

			}

		private:
			mutable space::Point3  m_origin;
			mutable space::Vector3 m_dir;
			mutable space::Vector3 m_inv_dir;
			mutable space::Point3  m_hitpoint;
			mutable double m_mint;
			mutable double m_maxt;
			mutable double m_index_of_refraction;	
			int m_sign[3];
	};

	class BBox 
	{
		public:
			BBox() {
				m_pmin = space::Point3(INFINITY,INFINITY,INFINITY);
				m_pmax = space::Point3(-INFINITY,-INFINITY,-INFINITY);
			};
			BBox(const space::Point3& p) : m_pmin(p),m_pmax(p) {};
			BBox(const space::Point3& p1,const space::Point3& p2) {
				
				m_pmin = space::Point3(std::min(p1.x(),p2.x()),
									   std::min(p1.y(),p2.y()),
									   std::min(p1.z(),p2.z()));

				m_pmax = space::Point3(std::max(p1.x(),p2.x()),
									   std::max(p1.y(),p2.y()),
									   std::max(p1.z(),p2.z()));
			};		

			bool inside(const space::Point3 &pt) const {
				return (pt.x() >= m_pmin.x() && pt.x() <= m_pmax.x() &&
						pt.y() >= m_pmin.y() && pt.y() <= m_pmax.y() &&
						pt.z() >= m_pmin.z() && pt.z() <= m_pmax.z());
			};

			space::Point3 min() const { return m_pmin; };
			space::Point3 max() const { return m_pmax; };

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
			space::Point3 m_pmin;
			space::Point3 m_pmax;
	};
};

#endif