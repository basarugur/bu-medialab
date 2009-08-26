
#include "../../src/core/scene.h"
#include "../../src/core/cylinder.h"
#include "../../src/core/cube.h"
#include "../../src/core/rectangle.h"
#include "../../src/RenderController.h"




int main()
{

	Scene* new_scene = new Scene();

	GfxObject* new_obj1 = new GfxObject(new RectangleShape(),new Material(),new Transformation());
	new_obj1->getMaterial()->enableTexture(true);
	new_obj1->getMaterial()->getTexture().m_scale_x = 30 ; 
	new_obj1->getMaterial()->getTexture().m_scale_y = 30 ;

	if (new_obj1->getShape()->type() == RECTANGLE)
	{
		RectangleShape* rct_ = static_cast<RectangleShape*>(new_obj1->getShape());
		rct_->m_x = 100 ; 
		rct_->m_y = 100 ;
	}

	GfxObject* new_obj2 = new GfxObject(new Cube(),new Material(),new Transformation());
	new_obj2->getIndividualTranform()->scale(4,6,0.5);
	new_obj2->getIndividualTranform()->translate(0,0,6.5);
	new_obj2->getMaterial()->setDiffColor(TRadiance(0,0.5,0));


	GfxObject* new_obj3 = new GfxObject(new Cylinder(),new Material(),new Transformation());
	GfxObject* new_obj4 = new GfxObject(new Cylinder(),new Material(),new Transformation());
	GfxObject* new_obj5 = new GfxObject(new Cylinder(),new Material(),new Transformation());
	GfxObject* new_obj6 = new GfxObject(new Cylinder(),new Material(),new Transformation());
	
	new_obj3->getMaterial()->setDiffColor(TRadiance(1,0,0));
	new_obj4->getMaterial()->setDiffColor(TRadiance(1,0,0));
	new_obj5->getMaterial()->setDiffColor(TRadiance(1,0,0));
	new_obj6->getMaterial()->setDiffColor(TRadiance(1,0,0));

	new_obj3->getIndividualTranform()->translate(5,8,0);
	new_obj4->getIndividualTranform()->translate(5,-8,0);
	new_obj5->getIndividualTranform()->translate(-5,-8,0);
	new_obj6->getIndividualTranform()->translate(-5,8,0);


	Cylinder* tmp_ = static_cast<Cylinder*>(new_obj3->getShape());
	tmp_->m_h = 6 ;
	tmp_->m_r = 1;
	tmp_ = static_cast<Cylinder*>(new_obj4->getShape());
	tmp_->m_h = 6 ;
	tmp_->m_r = 1;
	tmp_ = static_cast<Cylinder*>(new_obj5->getShape());
	tmp_->m_h = 6 ;
	tmp_->m_r = 1;
	tmp_ = static_cast<Cylinder*>(new_obj6->getShape());
	tmp_->m_h = 6 ; 
	tmp_->m_r = 1;

	new_obj2->addChild(new_obj3);
	new_obj2->addChild(new_obj4);
	new_obj2->addChild(new_obj5);
	new_obj2->addChild(new_obj6);


	new_obj2->getPublicTranform()->translate(0,0,5); // translate whole tree

    
	PointLight* lgh1_ = new PointLight();
	lgh1_->setPos(Point3(10,30,20));	
	lgh1_->set_coeff(0.6);

	PointLight* lgh2_ = new PointLight();
	lgh2_->setPos(Point3(-10,-30,20));
	lgh2_->set_coeff(0.6);

	Camera* cmr_ = new Camera();
	cmr_->setPosition(Point3(30,30,10));
	cmr_->setAtPoint(Point3(0,0,0));
	cmr_->setUpVector(Vector3(-0.5,-0.5,6).normalize());

	
	*new_scene+=new_obj1;
	*new_scene+=new_obj2;
	*new_scene+=new_obj3;
	*new_scene+=new_obj4;
	*new_scene+=new_obj5;
	*new_scene+=new_obj6;
	*new_scene+=lgh1_;
	*new_scene+=lgh2_;

	RenderController* rc_ = new RenderController();

	rc_->render(new_scene,cmr_);

}