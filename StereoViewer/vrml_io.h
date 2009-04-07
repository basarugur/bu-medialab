/*	vrml_io.h:
	VRML 97 Reader & Writer -highly- BETA
	Authors: Basar Ugur & Resid Cizmeci */

#include <cybergarage/x3d/CyberX3D.h>

using namespace CyberX3D;

class Geometry;
class SceneObject;

class vrml_io
{
public:
	vrml_io() {};
	~vrml_io() {};

    Node* getMaterialNode(Node * root);
    void fillIndexedFaceSets(Geometry* g, ShapeNode* shapeNode);
	bool read(SceneObject* o, const char* fileName, const char* objectName);
	void write(Geometry* g, const char* fileName, const char* objectName);
};
