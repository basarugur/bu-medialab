#pragma once

#include "core/scene.h"
#include "CanvasGrid.h"

#include "GL/glut.h"

class SM_API_EXPORT SceneDrawer
{
public:
	SceneDrawer(void);
	~SceneDrawer(void);

	void drawWiredScene(Scene* sc_,Camera* cm_ = NULL,CanvasGrid* grd_ = NULL,
						bool drwLight_ = false,bool drwCmr_ = false);
	void drawShadedScene(Scene* sc_,Camera* cm_ = NULL,CanvasGrid* grd_ = NULL,
						bool drwLight_ = false,bool drwCmr_ = false);
	void drawShadedWiredScene(Scene* sc_,Camera* cm_ = NULL,CanvasGrid* grd_ = NULL,
						bool drwLight_ = false,bool drwCmr_ = false);

	void drawShadedObject(GfxObject* obj_);
	void drawWiredObject(GfxObject* obj_);
	void drawShadedWiredObject(GfxObject* obj_);
	void drawLight(Light* lg_);
	void drawCamera(Camera* cm_);
};
