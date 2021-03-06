


#ifndef TORUS_H
#define TORUS_H


#include "shape.h"
#include "trianglemesh.h"

class SM_API_EXPORT Torus : public Shape
{
	public:
		Torus(): Shape() {

			m_in_r = 2 ;
			m_out_r = 4 ;
			m_sides = 10;
			m_rings = 10;

			m_type = TORUS;

		};
		BBox object_bound() const ;

		Shape* getNewCopy();

		void copyToMesh(TriangleMesh* msh_);

		void draw( drawType dt_ );

		virtual bool can_intersect() const { return false; } ;
		virtual const std::vector<Triangle*>& refine() const {  std::vector<Triangle*> ms; return ms;  };

		virtual bool intersect(const Ray& r,float *hit,DifferentialGeometry* d) const {
			return  false;
		};
		virtual bool intersectp(const Ray& r) const {
			return false;
		};


public:
	double m_in_r;
	double m_out_r;
	int m_sides;
	int m_rings;
};

#endif
