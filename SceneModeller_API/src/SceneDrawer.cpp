#include "SceneDrawer.h"

#include "core/sphere.h"
#include "core/cube.h"
#include "core/cone.h"
#include "core/trianglemesh.h"
#include "core/cylinder.h"
#include "core/twosidedcylinder.h"
#include "core/torus.h"

#include "core/triangleshape.h"
#include "core/rectangle.h"
#include "core/circle.h"
#include "core/disk.h"
#include "core/partialdisk.h"

SceneDrawer::SceneDrawer(void)
{
}

SceneDrawer::~SceneDrawer(void)
{
}

void SceneDrawer::drawScene(Scene* sc_, Camera* cm_, CanvasGrid* grd_,
                            drawType dt_,
                            bool drwLight_, bool drwCmr_ )
{
    if (cm_ != NULL)
	{
		gluLookAt( cm_->position().x(), cm_->position().y(), cm_->position().z(),
                   cm_->lookAtPoint().x(),cm_->lookAtPoint().y(),cm_->lookAtPoint().z(),
                   cm_->upVector().x(),cm_->upVector().y(),cm_->upVector().z() );
	}

	if (grd_ != NULL)
	{
		grd_->draw();
	}

    /*glTranslatef(0, 0, 30);

    glRotatef(-90, 1, 0, 0);*/

	for(int i=0 ; i<sc_->objects().size();i++)
	{
		sc_->objects()[i]->draw( dt_ );
	}

	if(drwLight_)
	{
		glDisable(GL_LIGHTING);
		glLineWidth(3);
		for(int i=0 ; i<sc_->lights().size();i++)
			sc_->lights()[i]->draw();
		glLineWidth(1);
		glEnable(GL_LIGHTING);
	}

	if(drwCmr_)
	{
		for(int i=0 ; i<sc_->cameras().size();i++)
			sc_->cameras()[i]->draw();
	}
}
