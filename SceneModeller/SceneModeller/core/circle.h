


#ifndef CIRCLE_H
#define CIRCLE_H


#include "shape.h"
#include "trianglemesh.h"

class Circle : public Shape
{
	public:	
		Circle(): Shape() {
		
			m_r = 2 ; 
			m_slices = 10;
			m_loops = 10;

			m_type = CIRCLE;

		};						
		BBox object_bound() const ;
		void copyToMesh(TriangleMesh* msh_);

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
	int m_slices;
	int m_loops;
};

#endif