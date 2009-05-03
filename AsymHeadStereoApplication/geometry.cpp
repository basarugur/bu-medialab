/*	geometry.cpp: implementation
	Author: Basar Ugur */

#include "geometry.h"
#include "vrml_io.h"
#include "GL/glut.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DONE		0
#define NOT_FOUND  -1

#define SCALE_NORM	4.5
#define MAXCORNER	10
#define STR_MAX		128

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Geometry::Geometry(const char* fileName, const char* objectName)
{
	weight = 0.0;
	vrml_io reader;
	reader.read(this, fileName, objectName);
}

Geometry::~Geometry()
{
	points.clear();
	faces.clear();
}

void Geometry::invertNormals()
{
	for (int i=0; i<normals.size(); i++)
	{
		normals[i].x = -(normals.at(i).x);
		normals[i].y = -(normals.at(i).y);
		normals[i].z = -(normals.at(i).z);
	}
}

void Geometry::initColors(Point fill)
{
	for (vector<Point>::iterator cIter = points.begin(); cIter != points.end(); cIter++)
		colors.push_back(fill);
}

bool Geometry::onArea( Face *f, int ai )
{
	Area *area = &areas[ai];
	for (vector<AreaMember>::iterator iter=area->members.begin(); iter != area->members.end(); iter++)
		if (iter->index == f->indices[0] || iter->index == f->indices[1] || iter->index == f->indices[2])
			return true;
	return false;
}

bool Geometry::onArea( Point *p, int ai )
{
	Area *area = &areas[ai];
	for (vector<AreaMember>::iterator iter=area->members.begin(); iter != area->members.end(); iter++)
		if (points.at(iter->index) == *p)
			return true;
	return false;
}

bool Geometry::onArea( int pi, int ai )
{
	for (vector<AreaMember>::iterator iter=vertices[pi].areaIndices.begin();
		 iter!=vertices[pi].areaIndices.end();
		 iter++)
		if (iter->index == ai)
			return true;
	
	return false;	
}

void Geometry::draw()
{
	for (vector<Face>::iterator i = faces.begin(); i != faces.end(); i++)
		for (int c=0; c<3; c++)
		{
		        glNormal3f(normals.at(i->indices[c]).x, normals.at(i->indices[c]).y, normals.at(i->indices[c]).z);
                        glVertex3f(points.at(i->indices[c]).x, points.at(i->indices[c]).y, points.at(i->indices[c]).z);
		}
}