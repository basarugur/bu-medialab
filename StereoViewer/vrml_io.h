/*	vrml_io.h:
	VRML 97 Reader & Writer -highly- BETA
	Authors: Basar Ugur & Isik Baris Fidaner */

class Geometry;

class vrml_io
{
public:
	vrml_io() {};
	~vrml_io() {};

	void read(Geometry* g, const char* fileName, const char* objectName);
	void write(Geometry* g, const char* fileName, const char* objectName);
};
