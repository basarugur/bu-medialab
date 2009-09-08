


#ifndef SPHERE_H
#define SPHERE_H


#include "shape.h"
#include "trianglemesh.h"

class SM_API_EXPORT Sphere : public Shape
{
	public:
		Sphere(): Shape() {

			m_r = 3 ;
			m_type = SPHERE;
			m_slices = 10;
			m_stacks = 10;

		};
		BBox object_bound() const;

		double radius(){ return m_r; }

        virtual Shape* getNewCopy();

		virtual void copyToMesh(TriangleMesh* msh_);

		virtual void draw( drawType dt_ );

		virtual bool can_intersect() const { return false; } ;
		virtual const std::vector<Triangle*>& refine() const {  std::vector<Triangle*> ms; return ms; } ;

		virtual bool intersect(const Ray& r,float *hit,DifferentialGeometry* d) const {
			return  false;
		};
		virtual bool intersectp(const Ray& r) const {
			return false;
		};

public:
	double m_r;
	int m_slices;
	int m_stacks;
};

#endif
