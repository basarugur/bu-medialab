


#ifndef TRIANGLE_SHAPE_H
#define TRIANGLE_SHAPE_H


#include "shape.h"
#include "trianglemesh.h"

class SM_API_EXPORT TriangleShape : public Shape
{
	public:	
		TriangleShape(): Shape() {
		

			m_p1 = Vertex(0,2,0);
			m_p2 = Vertex(1.5,-1,0);
			m_p3 = Vertex(-1.5,-1,0);

			m_type = TRIANGLE_SHAPE;

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
	Vertex m_p1;
	Vertex m_p2;
	Vertex m_p3;
};

#endif