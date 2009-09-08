#include "../../src/core/scene.h"
#include "../../src/core/sphere.h"
#include "../../src/core/rectangle.h"

#include "../../src/RenderController.h"

int main()
{
	Scene* new_scene = new Scene();

	GfxObject* new_obj = new GfxObject(new Sphere(),new Material(),new Transformation());

	GfxObject* new_obj1 = new GfxObject(new RectangleShape(),new Material(),new Transformation());

	if (new_obj1->getShape()->type() == RECTANGLE)
	{
		RectangleShape* rct_ = static_cast<RectangleShape*>(new_obj1->getShape());
		rct_->m_x = 100 ;
		rct_->m_y = 100 ;
	}

	if (new_obj->getShape()->type() == SPHERE)
	{
		Sphere* sph_ = static_cast<Sphere*>(new_obj->getShape());
		sph_->m_r = 5 ;
		sph_->m_slices = 30;
		sph_->m_stacks = 30;
	}

	new_obj->getIndividualTransform()->translate(0,0,8);
	new_obj->getMaterial()->setDiffColor(TRadiance(0.0,0.2,0.9));

	new_obj1->getMaterial()->setDiffColor(TRadiance(0.6,0.6,0.6));

	PointLight* lgh1_ = new PointLight();
	lgh1_->setPos(Point3(0,10,50));
	lgh1_->set_coeff(0.6);

	PointLight* lgh2_ = new PointLight();
	lgh2_->setPos(Point3(0,-10,50));
	lgh2_->set_coeff(0.6);

	Camera* cmr_ = new Camera();
	cmr_->setPosition(Point3(10,10,20));
	cmr_->setAtPoint(Point3(0,0,0));
	cmr_->setUpVector(Vector3(-0.5,-0.5,0.5).normalize());

	*new_scene+=new_obj;
	*new_scene+=new_obj1;
	*new_scene+=lgh1_;
	*new_scene+=lgh2_;

	RenderController* rc_ = new RenderController();

	rc_->render(new_scene,cmr_);

	return 0;
}
