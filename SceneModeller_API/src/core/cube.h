


#ifndef CUBE_H
#define CUBE_H


#include "shape.h"
#include "trianglemesh.h"

class SM_API_EXPORT Cube : public Shape
{
	public:
		Cube(): Shape() {

			m_d = 3 ;
			m_type = CUBE;

		};
		BBox object_bound() const ;

		void copyToMesh(TriangleMesh* msh_);

		Shape* getNewCopy();

		void draw( drawType dt_ );

		double Dim(){ return m_d; }

		virtual bool can_intersect() const { return false; } ;
		virtual const std::vector<Triangle*>& refine() const {  std::vector<Triangle*> ms; return ms;  };

		virtual bool intersect(const Ray& r,float *hit,DifferentialGeometry* d) const {
			return  false;
		};
		virtual bool intersectp(const Ray& r) const {
			return false;
		};

public:
	double m_d;
};

#endif
