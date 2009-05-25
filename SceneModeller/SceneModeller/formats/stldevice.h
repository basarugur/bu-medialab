
#ifndef STL_DEVICE_H
#define STL_DEVICE_H

#include "SMIODevice.h"

#include "../core/trianglemesh.h"

class StlDevice : public SMIODevice
{
public:
	StlDevice();
	~StlDevice();

	void loadScene(std::string fl_ , Scene* sce_);
	void loadObject(std::string fl_ , GfxObject* obj_);
	void saveToFile(std::string fl_ , Scene* sce_);

	void saveMesh(std::string fl_ , TriangleMesh* obj_);
	void loadMesh(std::string fl_ , TriangleMesh* obj_);
};

#endif