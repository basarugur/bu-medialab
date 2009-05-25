


#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <float.h>

#define PI                     3.14159265358979323846
#define ZERO				   1e-5
#define RAY_EPSILON            1e-5
#define RAY_INFINITY           1e30
#ifndef INFINITY
#define INFINITY               FLT_MAX
#endif


class Vector3
{
	public:	
		 Vector3(double _x=0,double _y=0,double _z=0)			 
		 {
			m_v[0] = _x;
			m_v[1] = _y;
			m_v[2] = _z;
		 };
		 
		 double x() const { return m_v[0]; };
		 double y() const { return m_v[1]; };
		 double z() const { return m_v[2]; };
		 double v(int i) const { return m_v[i]; };

		 Vector3 operator-(const Vector3& rhs) const {
		    return Vector3(m_v[0]-rhs.x(),m_v[1]-rhs.y(),m_v[2]-rhs.z());
		 }

		 Vector3 operator+(const Vector3& rhs) const {
			return Vector3(m_v[0]+rhs.x(),m_v[1]+rhs.y(),m_v[2]+rhs.z());
		 }

		 Vector3& operator=(const Vector3& rhs) {
		   m_v[0] = rhs.x(); m_v[1] = rhs.y(); m_v[2] = rhs.z();
		   return *this;
		 }
		 
		 Vector3& operator+=(const Vector3& rhs) {
		   m_v[0] += rhs.x(); m_v[1] += rhs.y(); m_v[2] += rhs.z();
		   return *this;
		 }
		 
		 double operator*(const Vector3& rhs) const {
			return m_v[0]*rhs.x() + m_v[1]*rhs.y() + m_v[2]*rhs.z();
		 }

		  Vector3 scale(Vector3 rhs_) const {
		   return Vector3(rhs_.x()*x(),rhs_.y()*y(),rhs_.z()*z());
		 }
		 
		 Vector3 operator*(double f) const {
		   return Vector3(f*x(),f*y(),f*z());
		 }
		 
		 Vector3& operator*=(double f) {
			m_v[0] *= f; m_v[1] *= f; m_v[2] *= f;
			return *this;
		 }
		 
		 Vector3 operator^(const Vector3& rhs) const {
			return Vector3((y() * rhs.z()) - (z() * rhs.y()),
						   (z() * rhs.x()) - (x() * rhs.z()),
						   (x() * rhs.y()) - (y() * rhs.x()));
		 }
		 
		 Vector3 operator/(double f) const {
			double inv = 1.f / f;
			return Vector3(x()*inv,y()*inv,z()*inv);
		 }
		 
		 Vector3& operator/=(double f) {
			double inv = 1.f / f;
			m_v[0] /= inv; m_v[1] /= inv; m_v[2] /= inv;
			return *this;
		 }
		 
		 Vector3 operator-() const {
			return Vector3(-x(),-y(),-z());
		 }

		 bool operator==(const Vector3& rhs) const
		 {
			if (x() == rhs.x() && y() == rhs.y() && z() == rhs.z() )				
				return true;			

			return false;
		 }
		 
		 double length() const { return sqrt(x()*x() + y()*y() + z()*z()); }
		 Vector3 normalize() const { return (*this) / length(); }

 	 	 Vector3 max_coor() {
			 double f = std::max(m_v[0],std::max(m_v[0],m_v[1]));
			return Vector3(f,f,f);
		 }
		 						
	protected:
		double m_v[3];
};


inline Vector3 operator*(double lhs,const Vector3& rhs) { return rhs*lhs; };
inline double random() { return ((double)rand()/RAND_MAX); };
inline double degtorad(int angle) { return (angle* PI / 180.0); };
inline void random_stratified(Vector3* list,int size) {

	double inc  = 1 / (double)size;
	double hinc = inc/2.0;
	double ix = hinc;
	double iy = hinc;
	int c = 0;

	for(int i=0;i<size;i++) {
		for(int j=0;j<size;j++) {
			double xx =  ix + ((hinc)-(random()*(inc)));
			double yy =  iy + ((hinc)-(random()*(inc)));

			Vector3 t(xx,yy,0);
			list[c] = t;

			ix = ix + inc;
			c++;
		}			
		ix = hinc;
		iy = iy + inc;
	}

};

#endif