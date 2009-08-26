#pragma once

#include "core/scene.h"


class SM_API_EXPORT RenderController
{
public:
	RenderController(void);
	~RenderController(void);

	void render(Scene* sc_,Camera* cm_,bool skyLight = false, double skyCoeff=1 , bool antiAlisng = false ,
		                               int width=600 , int height = 600);

	void saveRawFiles(Scene* m_scene);

	void saveXML(Scene* sc_,Camera* cm_,bool skyLight ,double skyCoeff, bool antiAlisng,
				 int width , int height);
};
