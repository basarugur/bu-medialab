
#ifndef VRML_DEVICE_H
#define VRML_DEVICE_H

#include "SMIODevice.h"



#include "../core/trianglemesh.h"

#include <map>
#include <sstream>

#include "vrml/Node.h"
#include "vrml/SceneGraph.h"

class SM_API_EXPORT VrmlDevice : public SMIODevice
{
public:
	VrmlDevice();
	~VrmlDevice();

	void loadScene(std::string fl_ , Scene* sce_);
	void loadObject(std::string fl_ , GfxObject* obj_);
	void saveToFile(std::string fl_ , Scene* sce_);

	// Load scene to into VRML nodes
	void createShapeNode(Shape* shp_,Material* mt_,ShapeNode* shpNode_);
	void saveToTransformNode( GfxObject* obj_ , TransformNode *nde_ );
	void saveMeshToIndexedSet(TriangleMesh* msh_ , IndexedFaceSetNode* fst_);

    // Load VRML nodes into scene
    void addNewNode(Scene* scn_, Node* node_, GfxObject* parentObj_ = NULL,
                    Transformation localTrans_ = Transformation(), Transformation globalTrans_ = Transformation());

	void addTransformNode(Scene* scn_, Node* node_, GfxObject* parentObj_ = NULL,
                          Transformation localTrans_ = Transformation(), Transformation globalTrans_ = Transformation());

	void addShapeNode(Scene* sce_, Node* node_, GfxObject* parentObj_ = NULL,
                      Transformation localTrans_ = Transformation(), Transformation globalTrans_ = Transformation());

	void TriangulateFace(std::vector<Triangle*>& trList, std::vector<Vertex*>& vrtList,std::vector<int> indList);

    /** Name / String from last DEF node, to be used when writing file etc. */
	std::string lastDEF;
};

#endif
