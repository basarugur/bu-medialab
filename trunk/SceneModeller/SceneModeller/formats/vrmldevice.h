
#ifndef VRML_DEVICE_H
#define VRML_DEVICE_H

#include "SMIODevice.h"



#include "../core/trianglemesh.h"

#include <map>
#include <sstream>

#include "vrml/Node.h"
#include "vrml/SceneGraph.h"

class VrmlDevice : public SMIODevice
{
public:
	VrmlDevice();
	~VrmlDevice();

	void loadScene(std::string fl_ , Scene* sce_);
	void loadObject(std::string fl_ , GfxObject* obj_);
	void saveToFile(std::string fl_ , Scene* sce_);

	// load shape to shape node
	void createShapeNode(Shape* shp_,Material* mt_,ShapeNode* shpNode_);
	void saveToTransformNode( GfxObject* obj_ , TransformNode *nde_ );
	void saveMeshToIndexedSet(TriangleMesh* msh_ , IndexedFaceSetNode* fst_);

	void addTransformNode(Scene* scn_,GfxObject* parnt_,TransformNode* tns_);
	// load shape node to shape
	void addShapeNode(Shape*& shp,Material* mt_,ShapeNode* shpNode_);

	void TriangulateFace(std::vector<Triangle*>& trList,std::vector<Vertex*>& vrtList,std::vector<int> indList);
};

#endif