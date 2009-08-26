


#ifndef FILM_H
#define FILM_H

#include "../sm_api_dll.h"

struct TRadiance
{
	TRadiance(double r_=0,double g_=0,double b_=0)
	{
		r = r_;
		g = g_;
		b = b_;
	};

	void normalize() {
		if (r>1.0) r = 1.0;
		if (g>1.0) g = 1.0;
		if (b>1.0) b = 1.0;
	}

	double r;
	double g;
	double b;
};

class SM_API_EXPORT Film
{
	public:	
		Film() {};
		
	private:
};



inline TRadiance operator+(const TRadiance& lhs,const TRadiance& rhs)
{
	return TRadiance(lhs.r+rhs.r,lhs.g+rhs.g,lhs.b+rhs.b);
}

inline TRadiance operator/(const TRadiance& lhs,double d)
{
	return TRadiance(lhs.r/d,lhs.g/d,lhs.b/d);
}

inline TRadiance operator*(const TRadiance& lhs,double d)
{
	return TRadiance(lhs.r*d,lhs.g*d,lhs.b*d);
}


#endif