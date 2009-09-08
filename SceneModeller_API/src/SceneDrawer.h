#pragma once

#include "core/scene.h"
#include "CanvasGrid.h"

class SM_API_EXPORT SceneDrawer
{
public:
	SceneDrawer(void);
	~SceneDrawer(void);

	void drawScene( Scene* sc_, Camera* cm_ = NULL, CanvasGrid* grd_ = NULL,
                    drawType dt_ = SHADED,
                    bool drwLight_ = false,bool drwCmr_ = false);
};
