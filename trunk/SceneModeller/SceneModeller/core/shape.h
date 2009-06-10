


#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "material.h"
#include "vector3.h"
#include "normal3.h"
#include "point3.h"
#include "triangle.h"
#include "bbox.h"
#include "ray.h"

enum ShapeType
{
	TRIANGLE_MESH = 0,
	CUBE = 1,
	SPHERE = 2,
	CONE = 3,
	CYLINDER = 4,
	TWO_SIDED_CYLINDER = 5,
	TORUS = 6,
	TRIANGLE_SHAPE = 7,
	RECTANGLE = 8,
	CIRCLE = 9,
	DISK = 10,
	PARTIAL_DISK = 11
};

class Shape
{
	public:	
		Shape() {};	
		virtual BBox object_bound() const = 0;
		virtual bool can_intersect() const = 0;
		virtual const std::vector<Triangle*>& refine() const = 0;

		virtual bool intersect(const Ray& r,float *hit,DifferentialGeometry* d) const {
			return  false;
		};
		virtual bool intersectp(const Ray& r) const {
			return false;
		};

		ShapeType type() { return m_type; };

protected:
	ShapeType m_type;
};

#endif