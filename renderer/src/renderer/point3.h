//Author: Ufuk Tiryaki @ 2009
//Desc:

#ifndef POINT_H
#define POINT_H

#include "vector3.h"

namespace space
{
	class Point3
	{
		public:	
			 Point3(double _x=0,double _y=0,double _z=0)			 
			 {
				m_v[0] = _x;
				m_v[1] = _y;
				m_v[2] = _z;
			 };
			 
			 double x() const { return m_v[0]; };
			 double y() const { return m_v[1]; };
			 double z() const { return m_v[2]; };
			 double v(int i) const { return m_v[i]; };
			 
			 bool operator==(const Point3& rhs) const {
				 return ((x() == rhs.x()) && (y() == rhs.y()) &&  (z() == rhs.z()));
			 }

			 bool operator!=(const Point3& rhs) const {
				 return (!(*this == rhs));
			 }

			 Point3 operator+(const Point3& rhs) const {
				return Point3(m_v[0]+rhs.x(),m_v[1]+rhs.y(),m_v[2]+rhs.z());
			 }
			 
			 Point3 operator+(const Vector3& rhs) const {
				return Point3(m_v[0]+rhs.x(),m_v[1]+rhs.y(),m_v[2]+rhs.z());
			 }
			 
			 Point3& operator+=(const Vector3& rhs) {
			   m_v[0] += rhs.x(); m_v[1] += rhs.y(); m_v[2] += rhs.z();
			   return *this;
			 }

			 Point3& operator=(const Point3& rhs) {
			   m_v[0] = rhs.x(); m_v[1] = rhs.y(); m_v[2] = rhs.z();
			   return *this;
			 }
			 
			 Point3 operator*(double f) const {
			   return Point3(f*x(),f*y(),f*z());
			 }

			 double operator*(const Vector3& rhs) const {
			   return (rhs.x()*x()+rhs.x()*y()+rhs.x()*z());
			 }
			 
			 Point3& operator*=(double f) {
				m_v[0] *= f; m_v[1] *= f; m_v[2] *= f;
				return *this;
			 }
	
			 Vector3 operator-(const Point3& p) const {
				return Vector3(m_v[0] - p.x(),m_v[1] - p.y(), m_v[2] - p.z());
			 }
			  
			 Point3 operator-(const Vector3& v) const {
				return Point3(m_v[0] - v.x(),m_v[1] - v.y(), m_v[2] - v.z());
			 }
			 
			 Point3& operator-=(const Vector3& v) {
				m_v[0] -= v.x(); m_v[1] -= v.y(); m_v[2] -= v.z();
				return *this;
			 }
			 
			 Point3 operator/(double f) const {
				double inv = 1.f / f;
				return Point3(x()*inv,y()*inv,z()*inv);
			 } 
			 
			 double length() const { return sqrt(m_v[0]*m_v[0] + m_v[1]*m_v[1] + m_v[2]*m_v[2]); }
	 	 				
		private:
			double m_v[3];
	};	
};

inline double distance(const space::Point3& p1,const space::Point3& p2) {
	return (p1-p2).length();
}

#endif