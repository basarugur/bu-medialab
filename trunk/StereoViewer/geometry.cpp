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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Geometry::Geometry()
{
    weight = 0.0;
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
    Point n;
    if (!faces.empty())
    {    // Currently supports one color per geometry:
        glColor3f(colors.at(0).x, colors.at(0).y, colors.at(0).z);

        glBegin(GL_TRIANGLES);
        for (vector<Face>::iterator i = faces.begin(); i != faces.end(); i++)
        {
            n = Face::normal(points.at(i->indices[0]), points.at(i->indices[1]), points.at(i->indices[2]) );
            for (int c=0; c<3; c++)
            {
                //glNormal3f(normals.at(i->indices[c]).x, normals.at(i->indices[c]).y, normals.at(i->indices[c]).z);
                glNormal3f(n.x, n.y, n.z);
                glVertex3f(points.at(i->indices[c]).x, points.at(i->indices[c]).y, points.at(i->indices[c]).z);
            }
        }
        glEnd();
    }
}

void Geometry::scale(float sx, float sy, float sz)
{
    Point scaler(sx, sy, sz);
    float range = pMax.maxCoord() - pMin.minCoord();
    scaler = scaler / range;

    for (vector<Point>::iterator iter = points.begin(); iter != points.end(); iter++)
        *iter = Point(iter->x * scaler.x, iter->y * scaler.y, iter->z * scaler.z);
}

SceneObject::SceneObject(const char* fileName, const char* objectName)
{
	vrml_io reader;
	reader.read(this, fileName, objectName);
	if (!children.empty())
        cout << "[i] Number of faces in first child: " << children[0].faces.size() << endl;
}

SceneObject::~SceneObject()
{
    children.clear();
}

void SceneObject::draw()
{
    if (!children.empty())
        for (vector<Geometry>::iterator c = children.begin(); c != children.end(); c++)
            c->draw();
}
