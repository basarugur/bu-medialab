


#ifndef TWO_SIDED_CYLINDER_H
#define TWO_SIDED_CYLINDER_H


#include "shape.h"
#include "trianglemesh.h"

class TwoSidedCylinder : public Shape
{
	public:	
		TwoSidedCylinder(): Shape() {
		
			m_base_r = 4 ; 
			m_top_r = 2;
			m_h = 5 ;
			m_slices = 10;
			m_stacks = 10;

			m_type = TWO_SIDED_CYLINDER;

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
	double m_base_r;
	double m_top_r;
	double m_h;
	int m_slices;
	int m_stacks;
};

#endif