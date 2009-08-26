


#ifndef DISK_H
#define DISK_H


#include "shape.h"
#include "trianglemesh.h"

class SM_API_EXPORT Disk : public Shape
{
	public:	
		Disk(): Shape() {
		
			m_in_r = 2 ; 
			m_out_r = 4 ;
			m_slices = 10;
			m_loops = 10;

			m_type = DISK;

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
	double m_in_r;
	double m_out_r;
	int m_slices;
	int m_loops;
};

#endif