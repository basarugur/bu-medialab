
#ifndef RAY_H
#define RAY_H

#include "vector3.h"
#include "point3.h"
#include "normal3.h"
#include <float.h>
#include <algorithm>

class Ray
{
	public:	
		Ray() : m_mint(RAY_EPSILON),m_maxt(RAY_INFINITY)
		{};
		Ray(const Point3& o,const Vector3& v,double min=RAY_EPSILON,double max=RAY_INFINITY)
			: m_origin(o),m_mint(min),m_maxt(max)
		{
			m_dir = v.normalize();
			m_inv_dir = Vector3(1.f/m_dir.x(),1.f/m_dir.y(),1.f/m_dir.z());

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

		const Point3& origin() const { return m_origin; };
		const Vector3& direction() const { return m_dir; };
		const Vector3& inv_direction() const { return m_inv_dir; };
		void set_origin(const Point3& o) const { m_origin = o; };
		void set_direction(const Vector3& v) const { m_dir = v; };
		const Point3& hitpoint() const { return m_hitpoint; };
		void set_hit(const Point3& p) const { m_hitpoint = p; };
		double refraction_index() const { return m_index_of_refraction; };
		void set_refraction_index(double r) { m_index_of_refraction = r; };

		Ray reflect(const Normal3& n,const Point3& p) const {								
			
			Vector3 rv = m_dir - 2*n*(m_dir*n);
			return Ray(p,rv);				
		}

		Ray refract(const Normal3& n,const Point3& p,double n1,double n2,bool& reflected) const {
			
			double nn  = (n1/n2);
			double cost  = ((m_dir*n)/(m_dir.length()*n.length()));
			double sint2 = nn*nn*(1.0 - cost*cost);
			
			if(sint2 <= 1.0) {			
				reflected = false;
				Vector3 rv = (m_dir*nn) - (nn*cost + sqrt(1-sint2))*n;
				return Ray(p,rv);
			} else {
				reflected = true;
				return reflect(n,p);
			}

		}

	private:
		mutable Point3  m_origin;
		mutable Vector3 m_dir;
		mutable Vector3 m_inv_dir;
		mutable Point3  m_hitpoint;
		mutable double m_mint;
		mutable double m_maxt;
		mutable double m_index_of_refraction;	
		int m_sign[3];
};

#endif