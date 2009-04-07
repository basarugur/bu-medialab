/*	Geometry.h: A Geometry class containing a 3D geometric object
	plus 3D geometric primitives with some useful methods defined on them
	Author: Basar Ugur */

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <math.h>

using namespace std;

#define PI				3.14159265359f
#define PI_2			6.28318530718f
#define N_AREA			8				// number of body areas to be modified
#define N_VFITTER		9

class Point
{
public: // Methods
	Point(float fx, float fy, float fz) { x = fx; y = fy; z = fz; };
	Point(float *fArray) { x = fArray[0]; y = fArray[1]; z = fArray[2]; };
	Point(float f) { x = y = z = f; };
	Point() { x = 0; y = 0; z = 0; };
	Point operator+(Point p) const { return Point(x+p.x, y+p.y, z+p.z); };
	Point operator-(Point p) const { return Point(x-p.x, y-p.y, z-p.z); };
	float operator*(Point p) const { return x*p.x + y*p.y + z*p.z; }; // dot product
	Point operator%(Point p) const { return Point(-y*p.z + z*p.y, -z*p.x + x*p.z, -x*p.y + y*p.x); }; // cross product
	Point operator*(float f) const { return Point(f*x, f*y, f*z); };
	Point operator/(float f) const { return Point(x/f, y/f, z/f); };
	Point operator-() const { return Point(-x, -y, -z); };
	void operator+=(const Point& p) { x += p.x; y += p.y; z += p.z;	};
	void operator-=(const Point& p) { x -= p.x; y -= p.y; z -= p.z;	};
	bool operator==(const Point& p) const { return (p.x==x && p.y==y && p.z==z); };
	float maxCoord() { return (x>y?(x>z?x:z):(y>z?y:z)); };
	float minCoord() { return (x<y?(x<z?x:z):(y<z?y:z)); };
	static Point normalize(const Point p)
	{
		float d = sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
		return Point(p.x / d, p.y / d, p.z / d);
	};
	static float norm(const Point p)
	{
		return sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
	}
	static float dist(const Point p1, const Point p2)
	{
		return norm(p1 - p2);
	}
	~Point() { return; };

public: // Variables
	float x,y,z;
};

class Line
{
public: // Methods
	Line(Point org, Point dir, bool normalizeDirection=true)
	{ origin = org;
	direction = normalizeDirection ? Point::normalize(dir) : dir; };
	Line() { };
public: // Variables:
	Point origin, direction;
};

class Face
{
public: // Methods
	Face(int *corners) { indices[0] = corners[0]; indices[1] = corners[1]; indices[2] = corners[2]; };
	~Face() { return; };
	static Point normal(Point a,Point b,Point c)
	{
		Point f1 = a - b;
		Point f2 = c - b;
		return f1 % f2;
	};

public: // Variables
	int indices[3];
};

class AreaMember
{
public: // Methods
	AreaMember(int i, float m) { index = i; membership = m; };

public:	// Variables
	int index;	// for a point, it's the area index; for an area, it's the point index
	float membership;
};

class Area
{
public: // Methods
	Area()	{ weight = 0.0; top = -1; bottom = -1; left = -1; right = -1; front = -1; back = -1; };
public: // Variables
	vector<AreaMember> members;		// body area membership values
	float weight;					// current weight of the area
	Point centroid;
	int top, bottom, left, right, front, back;
	Line axis;
};

class Vertex
{
public: // Methods
	Vertex() { };
public: // Variables
	vector<int> faceIndices; // indices of faces that the vertex is a corner of
	vector<AreaMember> areaIndices; // indices of areas that the vertex is a member of
};

class Matrix4x4
{
public: // Methods
	Matrix4x4()
	{
		for (int i=0; i<4; i++)
            for (int j=0; j<4; j++)
                data[i][j] = 0.0f;
	};
	Matrix4x4(float matrix[16]) // be careful to give 16 element arrays
	{
		for (int i=0; i<4; i++)
            for (int j=0; j<4; j++)
                data[i][j] = matrix[i*4 + j];
	};
	Matrix4x4(float matrix[4][4]) // be careful to give 16 element arrays
	{
		for (int i=0; i<4; i++)
            for (int j=0; j<4; j++)
                data[i][j] = matrix[i][j];
	};
	Point operator*(Point p) const
	{
		Point r(data[0][0] * p.x + data[0][1] * p.y + data[0][2] * p.z + data[0][3],
				data[1][0] * p.x + data[1][1] * p.y + data[1][2] * p.z + data[1][3],
				data[2][0] * p.x + data[2][1] * p.y + data[2][2] * p.z + data[2][3]);
		float invLast = 1.0f / (data[3][0] * p.x + data[3][0] * p.y + data[3][2]* p.z + data[3][3]); // inverse of last cell of point coordinate
		return r * invLast;
	};

public: // Variables
	float data[4][4];
};

class Geometry
{
public: // Methods
	Geometry();
	virtual ~Geometry();

	void invertNormals();
	void initColors(Point fillColor);						// initialize color array

	bool onArea(Face *f, int areaIndex);	/* checks if a "face" or "point" is on a particular area */
	bool onArea(Point *p, int areaIndex);	/* checks if a "face" or "point" is on a particular area */
	bool onArea(int pointIndex, int areaIndex);	/* checks if a "face" or "point" is on a particular area */

	/* a simple drawing routine for contained primitives */
	void draw();

	/* scale all points according to these factors */
	void scale(float sx, float sy, float sz);

//Variables
	vector<Point> points, normals, colors;		// core geometric elements
	vector<Face> faces;							// faces | meshes
	vector<Vertex> vertices;					// vertex array holding container face info

	int dressSize;
	float Coord2CM;								// coordinate units -> CM transformer

	friend class vrml_io;

private: // Variables
	Area areas[N_AREA+1];						// usable areas
	Point pMin, pMax;							// points holding extreme coordinates [bounding box]
	float weight;
};

class SceneObject
{
public:
    SceneObject(const char* fileName = "", const char* objectName = "");
    ~SceneObject();
    void draw();

    vector<Geometry> children;
};
