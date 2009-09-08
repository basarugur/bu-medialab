


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

#include "GL/glu.h"
#include "GL/glut.h"

class TriangleMesh;

enum drawType
{
    SHADED = 0x0001,
    WIRED = 0x0002
};

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

class SM_API_EXPORT Shape
{
public:
    Shape()
    {
        p_qdr = gluNewQuadric();
    };

    ~Shape()
    {
        gluDeleteQuadric( p_qdr );
    }

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

    virtual Shape* getNewCopy() = 0;

    virtual void copyToMesh(TriangleMesh* msh_) = 0;

    virtual void draw(drawType dt_) = 0;

protected:
	ShapeType m_type;

	GLUquadricObj* p_qdr;
};

#endif
