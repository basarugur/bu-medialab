
#include "../../src/core/scene.h"
#include "../../src/core/cylinder.h"
#include "../../src/core/cube.h"
#include "../../src/core/rectangle.h"
#include "../../src/RenderController.h"
#include "../../src/core/trianglemesh.h"

int main()
{

	Scene* new_scene = new Scene();

	GfxObject* new_obj1 = new GfxObject(new RectangleShape(),new Material(),new Transformation());
	new_obj1->getMaterial()->enableTexture(true);
	new_obj1->getMaterial()->getTexture().m_scale_x = 30 ;
	new_obj1->getMaterial()->getTexture().m_scale_y = 30 ;
	new_obj1->getMaterial()->getTexture().m_path = "texture/floor2.bmp";

	if (new_obj1->getShape()->type() == RECTANGLE)
	{
		RectangleShape* rct_ = static_cast<RectangleShape*>(new_obj1->getShape());
		rct_->m_x = 100 ;
		rct_->m_y = 100 ;
	}

	GfxObject* new_obj2 = new GfxObject(new Cube(),new Material(),new Transformation());
	new_obj2->getMaterial()->setDiffColor(TRadiance(0,0.5,0));
	new_obj2->getIndividualTransform()->translate(0,0,8);

	if (new_obj2->getShape()->type() == CUBE)
	{
		Cube* cbu_ = static_cast<Cube*>(new_obj2->getShape());
		cbu_->m_d = 8 ;
	}

	*new_scene += new_obj1 ;
	*new_scene += new_obj2 ;

	new_obj2->select(true);

	GfxObject* obj_ = new_scene->getSelectedObject(); // this returns new_object2 ;


	new_scene->clearobjectSelections();

	obj_ = new_scene->getSelectedObject(); // this returns NULL


	new_obj2->convertToMesh(); // now it is Triangle Mesh


	TriangleMesh* msh_ = static_cast<TriangleMesh*>(new_obj2->getShape());

	msh_->faceList()[0]->select(true);

	Triangle* tr_ = msh_->getSelectedFaceList()[0];

	msh_->clearFaceSelections();

	tr_->a()->setX(tr_->a()->x() + 5*tr_->n().x());
	tr_->a()->setY(tr_->a()->y() + 5*tr_->n().y());
	tr_->a()->setZ(tr_->a()->z() + 5*tr_->n().z());

	tr_->b()->setX(tr_->b()->x() + 5*tr_->n().x());
	tr_->b()->setY(tr_->b()->y() + 5*tr_->n().y());
	tr_->b()->setZ(tr_->b()->z() + 5*tr_->n().z());

	tr_->c()->setX(tr_->c()->x() + 5*tr_->n().x());
	tr_->c()->setY(tr_->c()->y() + 5*tr_->n().y());
	tr_->c()->setZ(tr_->c()->z() + 5*tr_->n().z());

	tr_->restoreNormalAndMidPoint();

	msh_->vertexList()[5]->select(true);
	Vertex* vrt_ = msh_->getSelectedVertexList()[0];
	msh_->clearVertexSelections();

	vrt_->setX(vrt_->x() + 16 );



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


	*new_scene+=lgh1_;
	*new_scene+=lgh2_;

	RenderController* rc_ = new RenderController();

	rc_->render(new_scene, cmr_);

	return 0;

}
