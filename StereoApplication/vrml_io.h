/*	vrml_io.h:
	VRML 97 Reader & Writer BETA -very much-
	Authors: Basar Ugur & Isik Baris Fidaner */

#ifndef I_VRMLIO_H
#define I_VRMLIO_H

#include "geometry.h"

class vrml_io
{
public:
	vrml_io() {};
	~vrml_io() {};

	void read(Geometry* g, const char* fileName, const char* objectName);
	void write(Geometry* g, const char* fileName, const char* objectName);
};

#endif
