


#ifndef RECTANGLE_H
#define RECTANGLE_H


#include "shape.h"
#include "trianglemesh.h"

class SM_API_EXPORT RectangleShape : public Shape
{
	public:	
		RectangleShape(): Shape() {
		
			m_x = 4 ; 
			m_y = 2 ;

			m_type = RECTANGLE;

		};						
		BBox object_bound() const ;
		void copyToMesh(TriangleMesh* msh_);

		virtual bool can_intersect() const { return false; } ;
		virtual const std::vector<Triangle*>& refine() const { std::vector<Triangle*> ms; return ms;  };

		virtual bool intersect(const Ray& r,float *hit,DifferentialGeometry* d) const {
			return  false;
		};
		virtual bool intersectp(const Ray& r) const {
			return false;
		};
public:
	double m_x;
	double m_y;
};

#endif