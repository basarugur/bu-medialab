


#ifndef CONE_H
#define CONE_H


#include "shape.h"
#include "trianglemesh.h"

class SM_API_EXPORT Cone : public Shape
{
	public:	
		Cone(): Shape() {
		
			m_r = 2 ; 
			m_h = 5 ;
			m_slices = 10;
			m_stacks = 10;

			m_type = CONE;

		};						
		BBox object_bound() const ;
		void copyToMesh(TriangleMesh* msh_);

		double buttomRadius(){ return m_r; }
		double height(){ return m_h; }

		virtual bool can_intersect() const { return false; } ;
		virtual const std::vector<Triangle*>& refine() const {  std::vector<Triangle*> ms; return ms;  };

		virtual bool intersect(const Ray& r,float *hit,DifferentialGeometry* d) const {
			return  false;
		};
		virtual bool intersectp(const Ray& r) const {
			return false;
		};

public:
	double m_r;
	double m_h;
	int m_slices;
	int m_stacks;
};

#endif