//Author: Ufuk Tiryaki @ 2009
//Desc:

#ifndef FILM_H
#define FILM_H

namespace output
{
	struct TRadiance
	{
		TRadiance(double r_=0,double g_=0,double b_=0) : r(r_),g(g_),b(b_) {};

		double r;
		double g;
		double b;
	};

	class Film
	{
		public:	
			Film() {};
			
		private:
	};
};


inline output::TRadiance operator+(const output::TRadiance& lhs,const output::TRadiance& rhs)
{
	return output::TRadiance(lhs.r+rhs.r,lhs.g+rhs.g,lhs.b+rhs.b);
}

inline output::TRadiance operator/(const output::TRadiance& lhs,double d)
{
	return output::TRadiance(lhs.r/d,lhs.g/d,lhs.b/d);
}

inline output::TRadiance operator*(const output::TRadiance& lhs,double d)
{
	return output::TRadiance(lhs.r*d,lhs.g*d,lhs.b*d);
}


#endif