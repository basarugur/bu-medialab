
#ifndef SMIO_DEVICE_H
#define SMIO_DEVICE_H

#include "../core/scene.h"


class SMIODevice
{
public:
	SMIODevice() 
	{

	};
	~SMIODevice()
	{

	};

	virtual void loadScene(std::string fl_ , Scene* sce_) = 0;
	virtual void loadObject(std::string fl_ , GfxObject* obj_)  = 0;
	virtual void saveToFile(std::string fl_ , Scene* sce_)  = 0;

};

#endif