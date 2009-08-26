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

void SceneDrawer::drawWiredScene(Scene* sc_, Camera* cm_, CanvasGrid* grd_,
					bool drwLight_ ,bool drwCmr_ )
{
    if (cm_ != NULL)
	{
		gluLookAt(cm_->position().x(), cm_->position().y(), cm_->position().z(),
			cm_->atPoint().x(),cm_->atPoint().y(),cm_->atPoint().z(),
			cm_->upVector().x(),cm_->upVector().y(),cm_->upVector().z()
			);
	}
	if (grd_ != NULL)
	{
		grd_->draw();
	}
	for(int i=0 ; i<sc_->objects().size();i++)
	{
		drawWiredObject(sc_->objects()[i]);
	}
	if(drwLight_)
	{
		glDisable(GL_LIGHTING);
		glLineWidth(3);
		for(int i=0 ; i<sc_->lights().size();i++)
			drawLight(sc_->lights()[i]);
		glLineWidth(1);
		glEnable(GL_LIGHTING);
	}
	if(drwCmr_)
	{
		for(int i=0 ; i<sc_->cameras().size();i++)
			drawCamera(sc_->cameras()[i]);
	}
}
void SceneDrawer::drawShadedScene(Scene* sc_, Camera* cm_, CanvasGrid* grd_, bool drwLight_, bool drwCmr_ )
{
    if (cm_ != NULL)
	{
	    gluLookAt(cm_->position().x(),cm_->position().y(),cm_->position().z(),
			cm_->atPoint().x(),cm_->atPoint().y(),cm_->atPoint().z(),
			cm_->upVector().x(),cm_->upVector().y(),cm_->upVector().z()
			);
	}
	if (grd_ != NULL)
	{
		grd_->draw();
	}

	glPushMatrix();

    /*glTranslatef(0, 0, 30);

    glRotatef(-90, 1, 0, 0);*/

    for(int i=0 ; i<sc_->objects().size();i++)
	{
	    drawShadedObject(sc_->objects()[i]);
	}

	glPopMatrix();

	if(drwLight_)
	{
		glDisable(GL_LIGHTING);
		glLineWidth(3);
		for(int i=0 ; i<sc_->lights().size();i++)
			drawLight(sc_->lights()[i]);
		glLineWidth(1);
		glEnable(GL_LIGHTING);
	}
	if(drwCmr_)
	{
		for(int i=0 ; i<sc_->cameras().size();i++)
			drawCamera(sc_->cameras()[i]);
	}
}
void SceneDrawer::drawShadedWiredScene(Scene* sc_, Camera* cm_, CanvasGrid* grd_,
                                        bool drwLight_ ,bool drwCmr_ )
{
	if (cm_ != NULL)
	{
		gluLookAt(cm_->position().x(),cm_->position().y(),cm_->position().z(),
			cm_->atPoint().x(),cm_->atPoint().y(),cm_->atPoint().z(),
			cm_->upVector().x(),cm_->upVector().y(),cm_->upVector().z()
			);
	}
	if (grd_ != NULL)
	{
		grd_->draw();
	}
	for(int i=0 ; i<sc_->objects().size();i++)
	{
		drawShadedWiredObject(sc_->objects()[i]);
	}
	if(drwLight_)
	{
		glDisable(GL_LIGHTING);
		glLineWidth(3);
		for(int i=0 ; i<sc_->lights().size();i++)
			drawLight(sc_->lights()[i]);
		glLineWidth(1);
		glEnable(GL_LIGHTING);
	}
	if(drwCmr_)
	{
		for(int i=0 ; i<sc_->cameras().size();i++)
			drawCamera(sc_->cameras()[i]);
	}
}
void SceneDrawer::drawLight(Light *lg_)
{
	PointLight* pnt_;
	AreaLight* are_;
	GLUquadric* qdr_ =  gluNewQuadric();

	if(lg_->isSelected())
		glColor3f(1.0,0.5,0.5);
	else
		glColor3f(1.0,1.0,1.0);

	switch(lg_->type())
	{
	case POINT_LIGHT:
		gluQuadricDrawStyle(qdr_,GLU_FILL);
		pnt_ = static_cast<PointLight*>(lg_);
		glTranslatef(pnt_->p().x(),pnt_->p().y(),pnt_->p().z());
		gluSphere(qdr_,0.5,30,30);

		glBegin(GL_LINES);
		glVertex3f(0.7,0,0);glVertex3f(1,0,0);
		glVertex3f(-0.7,0,0);glVertex3f(-1,0,0);

		glVertex3f(0,0.7,0);glVertex3f(0,1,0);
		glVertex3f(0,-0.7,0);glVertex3f(0,-1,0);

		glVertex3f(0,0,0.7);glVertex3f(0,0,1);
		glVertex3f(0,0,-0.7);glVertex3f(0,0,-1);
		glEnd();

		glTranslatef(-pnt_->p().x(),-pnt_->p().y(),-pnt_->p().z());
		break;
	case AREA_LIGHT:
		are_ = static_cast<AreaLight*>(lg_);
		glTranslatef(are_->p().x(),are_->p().y(),are_->p().z());

		glBegin(GL_QUADS);
		glVertex3f(are_->w()/2,are_->h()/2,0);
		glVertex3f(are_->w()/2,-are_->h()/2,0);
		glVertex3f(-are_->w()/2,-are_->h()/2,0);
		glVertex3f(-are_->w()/2,are_->h()/2,0);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(0,0,0.2);glVertex3f(0,0,0.5);
		glVertex3f(0,0,-0.2);glVertex3f(0,0,-0.5);

		glVertex3f(are_->w()/4,are_->h()/4,0.2);glVertex3f(are_->w()/4,are_->h()/4,0.5);
		glVertex3f(are_->w()/4,are_->h()/4,-0.2);glVertex3f(are_->w()/4,are_->h()/4,-0.5);

		glVertex3f(are_->w()/4,-are_->h()/4,0.2);glVertex3f(are_->w()/4,-are_->h()/4,0.5);
		glVertex3f(are_->w()/4,-are_->h()/4,-0.2);glVertex3f(are_->w()/4,-are_->h()/4,-0.5);

		glVertex3f(-are_->w()/4,-are_->h()/4,0.2);glVertex3f(-are_->w()/4,-are_->h()/4,0.5);
		glVertex3f(-are_->w()/4,-are_->h()/4,-0.2);glVertex3f(-are_->w()/4,-are_->h()/4,-0.5);

		glVertex3f(-are_->w()/4,are_->h()/4,0.2);glVertex3f(-are_->w()/4,are_->h()/4,0.5);
		glVertex3f(-are_->w()/4,are_->h()/4,-0.2);glVertex3f(-are_->w()/4,are_->h()/4,-0.5);
		glEnd();

		glTranslatef(-are_->p().x(),-are_->p().y(),-are_->p().z());
		break;
	}
}
void SceneDrawer::drawCamera(Camera* cm_)
{
	glPushMatrix();

	// calculate camera totation
	Matrix rotationMat;
	Vector3 vz_ = (cm_->atPoint()-cm_->position()).normalize();
	Vector3 vx_ = (vz_^cm_->upVector()).normalize();
	Vector3 vy_ = cm_->upVector();
	rotationMat.setcell(0,0, vx_.x() );
	rotationMat.setcell(0,1, vx_.y() );
	rotationMat.setcell(0,2, vx_.z() );

	rotationMat.setcell(1,0, vy_.x());
	rotationMat.setcell(1,1, vy_.y());
	rotationMat.setcell(1,2, vy_.z());

	rotationMat.setcell(2,0, -(vz_.x()));
	rotationMat.setcell(2,1, -(vz_.y()));
	rotationMat.setcell(2,2, -(vz_.z()));
	Rotation4 rot_;
	rot_.setFromMatrix(rotationMat);

	glTranslatef(cm_->position().x(),cm_->position().y(),cm_->position().z());
	double x_ = rot_.ax() ; double y_ = rot_.ay(); double z_ = rot_.az(); double ang_ = rot_.theta();
	glRotatef(-ang_,x_,y_,z_);

	double lngth_ = (cm_->atPoint()-cm_->position()).length();

	GLUquadric* qdr_ =  gluNewQuadric();
	gluQuadricDrawStyle(qdr_,GLU_FILL);

	glColor3f(0.1,0.1,0.1);
	if(cm_->isSelected())glColor3f(1,0.3,0.3);

	glRotatef(180,1.0,0.0,0.0);
	glTranslatef(0.0,0.0,-1.5);
	gluCylinder(qdr_,0.5,0.5,1.5,10,10);
	glTranslatef(0.0,0.0,1.5);
	glutSolidCone(0.5,0.75,10,10);
	glRotatef(180,-1.0,0.0,0.0);

	glLineWidth(3);

	glBegin(GL_LINES);
	glVertex3f(0,0,0);glVertex3f(0,-2,-1);
	glVertex3f(0,0,0);glVertex3f(0.5,-2,0.5);
	glVertex3f(0,0,0);glVertex3f(-0.5,-2,0.5);
	glEnd();

	glColor3f(0,0,1);
	if(cm_->isSelected())glColor3f(1,0.3,0.3);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);glVertex3f(0,0,-lngth_);
	glEnd();

	glLineWidth(1);

	glTranslatef(0,0,-lngth_);
	gluSphere(qdr_,0.3,10,10);
	glTranslatef(0,0,lngth_);

	glPopMatrix();
}
void SceneDrawer::drawWiredObject(GfxObject* obj_)
{
	Transformation globalTrns_ =  *obj_->getIndividualTransform() + *obj_->getPublicTransform();
	GfxObject* tmp_ = obj_->getParent();

	while(tmp_ != NULL)
	{
		globalTrns_ = globalTrns_*(*tmp_->getPublicTransform());
		tmp_ = tmp_->getParent();
	}
	glPushMatrix();
	glTranslatef(globalTrns_.translation().x(),
		globalTrns_.translation().y(),
		globalTrns_.translation().z());
	glScalef(globalTrns_.scale().x(),
		globalTrns_.scale().y(),
		globalTrns_.scale().z());
	glRotatef(globalTrns_.rotation().theta(),
		globalTrns_.rotation().ax(),
		globalTrns_.rotation().ay(),
		globalTrns_.rotation().az());

	TriangleMesh* msh_;
	Cube* cp_;
	Sphere* sph_;
	Cone* cne_;
	Cylinder* cyld_;
	TwoSidedCylinder* twcyl_;
	Torus* trs_ ;
	TriangleShape* trngshp_;
	RectangleShape* rect_;
	Circle* circle_;
	Disk* disk_;
	PartialDisk* pdisk_;

	if(obj_->isSelected())
		glColor3f(1,0,0);
	else
		glColor3f(obj_->getMaterial()->diffcolor().r,
		obj_->getMaterial()->diffcolor().g,
		obj_->getMaterial()->diffcolor().b);

	GLUquadric* qdr_ =  gluNewQuadric();
	gluQuadricDrawStyle(qdr_,GLU_LINE);

	switch(obj_->getShape()->type())
	{
	case TRIANGLE_MESH:
		msh_ = static_cast<TriangleMesh*>(obj_->getShape());
		glBegin(GL_LINES);
		for(int i=0 ; i<msh_->faceList().size();i++)
		{
			glVertex3f(msh_->faceList()[i]->a()->x(),msh_->faceList()[i]->a()->y(),msh_->faceList()[i]->a()->z());
			glVertex3f(msh_->faceList()[i]->b()->x(),msh_->faceList()[i]->b()->y(),msh_->faceList()[i]->b()->z());

			glVertex3f(msh_->faceList()[i]->b()->x(),msh_->faceList()[i]->b()->y(),msh_->faceList()[i]->b()->z());
			glVertex3f(msh_->faceList()[i]->c()->x(),msh_->faceList()[i]->c()->y(),msh_->faceList()[i]->c()->z());

			glVertex3f(msh_->faceList()[i]->c()->x(),msh_->faceList()[i]->c()->y(),msh_->faceList()[i]->c()->z());
			glVertex3f(msh_->faceList()[i]->a()->x(),msh_->faceList()[i]->a()->y(),msh_->faceList()[i]->a()->z());
		}
		glEnd();
		glLineWidth(1);
		break;
	case CUBE:
		cp_ = static_cast<Cube*>(obj_->getShape());
		glutWireCube(cp_->m_d);
		break;
	case SPHERE:
		sph_ = static_cast<Sphere*>(obj_->getShape());
		glutWireSphere(sph_->m_r,sph_->m_slices,sph_->m_stacks);
		break;
	case CONE:
		cne_ = static_cast<Cone*>(obj_->getShape());
		gluCylinder(qdr_,cne_->m_r,0.0,cne_->m_h,cne_->m_slices,cne_->m_stacks);
		gluDisk(qdr_,0,cne_->m_r,cne_->m_slices,1);
		break;
	case CYLINDER:
		cyld_ = static_cast<Cylinder*>(obj_->getShape());
		gluCylinder(qdr_,cyld_->m_r,cyld_->m_r,cyld_->m_h,cyld_->m_slices,cyld_->m_stacks);
		gluDisk(qdr_,0,cyld_->m_r,cyld_->m_slices,1);
		glTranslatef(0,0,cyld_->m_h);
		gluDisk(qdr_,0,cyld_->m_r,cyld_->m_slices,1);
		glTranslatef(0,0,-cyld_->m_h);
		break;
	case TWO_SIDED_CYLINDER:
		twcyl_ = static_cast<TwoSidedCylinder*>(obj_->getShape());
		gluCylinder(qdr_,twcyl_->m_base_r,twcyl_->m_top_r,twcyl_->m_h,twcyl_->m_slices,twcyl_->m_stacks);
		gluDisk(qdr_,0,twcyl_->m_base_r,twcyl_->m_slices,1);
		glTranslatef(0,0,twcyl_->m_h);
		gluDisk(qdr_,0,twcyl_->m_top_r,twcyl_->m_slices,1);
		glTranslatef(0,0,-twcyl_->m_h);
		break;
	case TORUS:
		trs_ = static_cast<Torus*>(obj_->getShape());
		glutWireTorus(trs_->m_in_r,trs_->m_out_r,trs_->m_sides,trs_->m_rings);
		break;
	case TRIANGLE_SHAPE:
		trngshp_ = static_cast<TriangleShape*>(obj_->getShape());
		glBegin(GL_LINE_LOOP);
		glVertex3f(trngshp_->m_p1.x(),trngshp_->m_p1.y(),trngshp_->m_p1.z());
		glVertex3f(trngshp_->m_p2.x(),trngshp_->m_p2.y(),trngshp_->m_p2.z());
		glVertex3f(trngshp_->m_p3.x(),trngshp_->m_p3.y(),trngshp_->m_p3.z());
		glEnd();
		break;
	case RECTANGLE:
		rect_ = static_cast<RectangleShape*>(obj_->getShape());
		glBegin(GL_LINE_LOOP);
		glVertex3f(rect_->m_x/2,rect_->m_y/2,0);
		glVertex3f(rect_->m_x/2,-rect_->m_y/2,0);
		glVertex3f(-rect_->m_x/2,-rect_->m_y/2,0);
		glVertex3f(-rect_->m_x/2,rect_->m_y/2,0);
		glEnd();
		break;
	case CIRCLE:
		circle_ = static_cast<Circle*>(obj_->getShape());
		gluDisk(qdr_,0,circle_->m_r,circle_->m_slices,circle_->m_loops);
		break;
	case DISK:
		disk_ = static_cast<Disk*>(obj_->getShape());
		gluDisk(qdr_,disk_->m_in_r,disk_->m_out_r,disk_->m_slices,disk_->m_loops);
		break;
	case PARTIAL_DISK:
		pdisk_ = static_cast<PartialDisk*>(obj_->getShape());
		gluPartialDisk(qdr_,pdisk_->m_in_r,pdisk_->m_out_r,pdisk_->m_slices,pdisk_->m_loops,
			pdisk_->start_ang,pdisk_->sweep_ang);
		break;
	default:
		break;
	}
	glPopMatrix();

}
void SceneDrawer::drawShadedObject(GfxObject* obj_)
{
    Transformation globalTrns_ =  *obj_->getIndividualTransform() + *obj_->getPublicTransform();
	GfxObject* tmp_ = obj_->getParent();

	while(tmp_ != NULL)
	{
		globalTrns_ = globalTrns_*(*tmp_->getPublicTransform());
		tmp_ = tmp_->getParent();
	}
	glPushMatrix();

	glTranslatef(globalTrns_.translation().x(),
		globalTrns_.translation().y(),
		globalTrns_.translation().z());
	glScalef(globalTrns_.scale().x(),
		globalTrns_.scale().y(),
		globalTrns_.scale().z());
	glRotatef(globalTrns_.rotation().theta(),
		globalTrns_.rotation().ax(),
		globalTrns_.rotation().ay(),
		globalTrns_.rotation().az());

	TriangleMesh* msh_;
	Cube* cp_;
	Sphere* sph_;
	Cone* cne_;
	Cylinder* cyld_;
	TwoSidedCylinder* twcyl_;
	Torus* trs_ ;
	TriangleShape* trngshp_;
	RectangleShape* rect_;
	Circle* circle_;
	Disk* disk_;
	PartialDisk* pdisk_;

	if(obj_->isSelected())
		glColor3f(1,0,0);
	else
		glColor3f(obj_->getMaterial()->diffcolor().r,
		obj_->getMaterial()->diffcolor().g,
		obj_->getMaterial()->diffcolor().b);

	GLUquadric* qdr_ =  gluNewQuadric();
	gluQuadricDrawStyle(qdr_,GLU_FILL);

	switch(obj_->getShape()->type())
	{
	case TRIANGLE_MESH:
        msh_ = static_cast<TriangleMesh*>(obj_->getShape());

		glBegin(GL_TRIANGLES);
		for(int i=0 ; i<msh_->faceList().size(); i++)
		{
			glNormal3f(msh_->faceList()[i]->n().x(), msh_->faceList()[i]->n().y(), msh_->faceList()[i]->n().z());
			glVertex3f(msh_->faceList()[i]->a()->x(), msh_->faceList()[i]->a()->y(), msh_->faceList()[i]->a()->z());
			glVertex3f(msh_->faceList()[i]->b()->x(), msh_->faceList()[i]->b()->y(), msh_->faceList()[i]->b()->z());
			glVertex3f(msh_->faceList()[i]->c()->x(), msh_->faceList()[i]->c()->y(), msh_->faceList()[i]->c()->z());
		}
		glEnd();
		break;
	case CUBE:
		cp_ = static_cast<Cube*>(obj_->getShape());
		glutSolidCube(cp_->m_d);
		break;
	case SPHERE:
		sph_ = static_cast<Sphere*>(obj_->getShape());
		glutSolidSphere(sph_->m_r,sph_->m_slices,sph_->m_stacks);
		break;
	case CONE:
		cne_ = static_cast<Cone*>(obj_->getShape());
		gluCylinder(qdr_,cne_->m_r,0.0,cne_->m_h,cne_->m_slices,cne_->m_stacks);
		gluDisk(qdr_,0,cne_->m_r,cne_->m_slices,1);
		break;
	case CYLINDER:
		cyld_ = static_cast<Cylinder*>(obj_->getShape());
		gluCylinder(qdr_,cyld_->m_r,cyld_->m_r,cyld_->m_h,cyld_->m_slices,cyld_->m_stacks);
		gluDisk(qdr_,0,cyld_->m_r,cyld_->m_slices,1);
		glTranslatef(0,0,cyld_->m_h);
		gluDisk(qdr_,0,cyld_->m_r,cyld_->m_slices,1);
		glTranslatef(0,0,-cyld_->m_h);
		break;
	case TWO_SIDED_CYLINDER:
		twcyl_ = static_cast<TwoSidedCylinder*>(obj_->getShape());
		gluCylinder(qdr_,twcyl_->m_base_r,twcyl_->m_top_r,twcyl_->m_h,twcyl_->m_slices,twcyl_->m_stacks);
		gluDisk(qdr_,0,twcyl_->m_base_r,twcyl_->m_slices,1);
		glTranslatef(0,0,twcyl_->m_h);
		gluDisk(qdr_,0,twcyl_->m_top_r,twcyl_->m_slices,1);
		glTranslatef(0,0,-twcyl_->m_h);
		break;
	case TORUS:
		trs_ = static_cast<Torus*>(obj_->getShape());
		glutSolidTorus(trs_->m_in_r,trs_->m_out_r,trs_->m_sides,trs_->m_rings);
		break;
	case TRIANGLE_SHAPE:
		trngshp_ = static_cast<TriangleShape*>(obj_->getShape());
		glBegin(GL_TRIANGLES);
		glVertex3f(trngshp_->m_p1.x(),trngshp_->m_p1.y(),trngshp_->m_p1.z());
		glVertex3f(trngshp_->m_p2.x(),trngshp_->m_p2.y(),trngshp_->m_p2.z());
		glVertex3f(trngshp_->m_p3.x(),trngshp_->m_p3.y(),trngshp_->m_p3.z());
		glEnd();
		break;
	case RECTANGLE:
		rect_ = static_cast<RectangleShape*>(obj_->getShape());
		glBegin(GL_QUADS);
		glVertex3f(rect_->m_x/2,rect_->m_y/2,0);
		glVertex3f(rect_->m_x/2,-rect_->m_y/2,0);
		glVertex3f(-rect_->m_x/2,-rect_->m_y/2,0);
		glVertex3f(-rect_->m_x/2,rect_->m_y/2,0);
		glEnd();
		break;
	case CIRCLE:
		circle_ = static_cast<Circle*>(obj_->getShape());
		gluDisk(qdr_,0,circle_->m_r,circle_->m_slices,circle_->m_loops);
		break;
	case DISK:
		disk_ = static_cast<Disk*>(obj_->getShape());
		gluDisk(qdr_,disk_->m_in_r,disk_->m_out_r,disk_->m_slices,disk_->m_loops);
		break;
	case PARTIAL_DISK:
		pdisk_ = static_cast<PartialDisk*>(obj_->getShape());
		gluPartialDisk(qdr_,pdisk_->m_in_r,pdisk_->m_out_r,pdisk_->m_slices,pdisk_->m_loops,
			pdisk_->start_ang,pdisk_->sweep_ang);
		break;
	default:
		break;
	}


	glPopMatrix();

}
void SceneDrawer::drawShadedWiredObject(GfxObject* obj_)
{
	Transformation globalTrns_ =  *obj_->getIndividualTransform() + *obj_->getPublicTransform();
	GfxObject* tmp_ = obj_->getParent();

	while(tmp_ != NULL)
	{
		globalTrns_ = globalTrns_*(*tmp_->getPublicTransform());
		tmp_ = tmp_->getParent();
	}
	glPushMatrix();
	glTranslatef(globalTrns_.translation().x(),
		globalTrns_.translation().y(),
		globalTrns_.translation().z());
	glScalef(globalTrns_.scale().x(),
		globalTrns_.scale().y(),
		globalTrns_.scale().z());
	glRotatef(globalTrns_.rotation().theta(),
		globalTrns_.rotation().ax(),
		globalTrns_.rotation().ay(),
		globalTrns_.rotation().az());

	TriangleMesh* msh_;
	Cube* cp_;
	Sphere* sph_;
	Cone* cne_;
	Cylinder* cyld_;
	TwoSidedCylinder* twcyl_;
	Torus* trs_ ;
	TriangleShape* trngshp_;
	RectangleShape* rect_;
	Circle* circle_;
	Disk* disk_;
	PartialDisk* pdisk_;

	if(obj_->isSelected())
		glColor3f(1,0,0);
	else
		glColor3f(obj_->getMaterial()->diffcolor().r,
		obj_->getMaterial()->diffcolor().g,
		obj_->getMaterial()->diffcolor().b);

	GLUquadric* qdr_ =  gluNewQuadric();
	gluQuadricDrawStyle(qdr_,GLU_FILL);

	// shaded
	switch(obj_->getShape()->type())
	{
	case TRIANGLE_MESH:
		msh_ = static_cast<TriangleMesh*>(obj_->getShape());
		glBegin(GL_TRIANGLES);
		for(int i=0 ; i<msh_->faceList().size();i++)
		{
			glNormal3f(msh_->faceList()[i]->n().x(),msh_->faceList()[i]->n().y(),msh_->faceList()[i]->n().z());
			glVertex3f(msh_->faceList()[i]->a()->x(),msh_->faceList()[i]->a()->y(),msh_->faceList()[i]->a()->z());
			glVertex3f(msh_->faceList()[i]->b()->x(),msh_->faceList()[i]->b()->y(),msh_->faceList()[i]->b()->z());
			glVertex3f(msh_->faceList()[i]->c()->x(),msh_->faceList()[i]->c()->y(),msh_->faceList()[i]->c()->z());
		}
		glEnd();
		break;
	case CUBE:
		cp_ = static_cast<Cube*>(obj_->getShape());
		glutSolidCube(cp_->m_d);
		break;
	case SPHERE:
		sph_ = static_cast<Sphere*>(obj_->getShape());
		glutSolidSphere(sph_->m_r,sph_->m_slices,sph_->m_stacks);
		break;
	case CONE:
		cne_ = static_cast<Cone*>(obj_->getShape());
		gluCylinder(qdr_,cne_->m_r,0.0,cne_->m_h,cne_->m_slices,cne_->m_stacks);
		gluDisk(qdr_,0,cne_->m_r,cne_->m_slices,1);
		break;
	case CYLINDER:
		cyld_ = static_cast<Cylinder*>(obj_->getShape());
		gluCylinder(qdr_,cyld_->m_r,cyld_->m_r,cyld_->m_h,cyld_->m_slices,cyld_->m_stacks);
		gluDisk(qdr_,0,cyld_->m_r,cyld_->m_slices,1);
		glTranslatef(0,0,cyld_->m_h);
		gluDisk(qdr_,0,cyld_->m_r,cyld_->m_slices,1);
		glTranslatef(0,0,-cyld_->m_h);
		break;
	case TWO_SIDED_CYLINDER:
		twcyl_ = static_cast<TwoSidedCylinder*>(obj_->getShape());
		gluCylinder(qdr_,twcyl_->m_base_r,twcyl_->m_top_r,twcyl_->m_h,twcyl_->m_slices,twcyl_->m_stacks);
		gluDisk(qdr_,0,twcyl_->m_base_r,twcyl_->m_slices,1);
		glTranslatef(0,0,twcyl_->m_h);
		gluDisk(qdr_,0,twcyl_->m_top_r,twcyl_->m_slices,1);
		glTranslatef(0,0,-twcyl_->m_h);
		break;
	case TORUS:
		trs_ = static_cast<Torus*>(obj_->getShape());
		glutSolidTorus(trs_->m_in_r,trs_->m_out_r,trs_->m_sides,trs_->m_rings);
		break;
	case TRIANGLE_SHAPE:
		trngshp_ = static_cast<TriangleShape*>(obj_->getShape());
		glBegin(GL_TRIANGLES);
		glVertex3f(trngshp_->m_p1.x(),trngshp_->m_p1.y(),trngshp_->m_p1.z());
		glVertex3f(trngshp_->m_p2.x(),trngshp_->m_p2.y(),trngshp_->m_p2.z());
		glVertex3f(trngshp_->m_p3.x(),trngshp_->m_p3.y(),trngshp_->m_p3.z());
		glEnd();
		break;
	case RECTANGLE:
		rect_ = static_cast<RectangleShape*>(obj_->getShape());
		glBegin(GL_QUADS);
		glVertex3f(rect_->m_x/2,rect_->m_y/2,0);
		glVertex3f(rect_->m_x/2,-rect_->m_y/2,0);
		glVertex3f(-rect_->m_x/2,-rect_->m_y/2,0);
		glVertex3f(-rect_->m_x/2,rect_->m_y/2,0);
		glEnd();
		break;
	case CIRCLE:
		circle_ = static_cast<Circle*>(obj_->getShape());
		gluDisk(qdr_,0,circle_->m_r,circle_->m_slices,circle_->m_loops);
		break;
	case DISK:
		disk_ = static_cast<Disk*>(obj_->getShape());
		gluDisk(qdr_,disk_->m_in_r,disk_->m_out_r,disk_->m_slices,disk_->m_loops);
		break;
	case PARTIAL_DISK:
		pdisk_ = static_cast<PartialDisk*>(obj_->getShape());
		gluPartialDisk(qdr_,pdisk_->m_in_r,pdisk_->m_out_r,pdisk_->m_slices,pdisk_->m_loops,
			pdisk_->start_ang,pdisk_->sweep_ang);
		break;
	default:
		break;
	}

	// wired
	if(obj_->isSelected())
		glColor3f(1,1,0);
	else
		glColor3f(obj_->getMaterial()->diffcolor().r-0.5,
		obj_->getMaterial()->diffcolor().g+0.5,
		obj_->getMaterial()->diffcolor().b-0.5);


	gluQuadricDrawStyle(qdr_,GLU_LINE);
	glLineWidth(2);

	switch(obj_->getShape()->type())
	{
	case TRIANGLE_MESH:
		msh_ = static_cast<TriangleMesh*>(obj_->getShape());
		glBegin(GL_LINES);
		for(int i=0 ; i<msh_->faceList().size();i++)
		{
			glVertex3f(msh_->faceList()[i]->a()->x(),msh_->faceList()[i]->a()->y(),msh_->faceList()[i]->a()->z());
			glVertex3f(msh_->faceList()[i]->b()->x(),msh_->faceList()[i]->b()->y(),msh_->faceList()[i]->b()->z());

			glVertex3f(msh_->faceList()[i]->b()->x(),msh_->faceList()[i]->b()->y(),msh_->faceList()[i]->b()->z());
			glVertex3f(msh_->faceList()[i]->c()->x(),msh_->faceList()[i]->c()->y(),msh_->faceList()[i]->c()->z());

			glVertex3f(msh_->faceList()[i]->c()->x(),msh_->faceList()[i]->c()->y(),msh_->faceList()[i]->c()->z());
			glVertex3f(msh_->faceList()[i]->a()->x(),msh_->faceList()[i]->a()->y(),msh_->faceList()[i]->a()->z());

			//gl TMP normals
			//glVertex3f(msh_->faceList()[i]->mid().x(),msh_->faceList()[i]->mid().y(),msh_->faceList()[i]->mid().z());
			//glVertex3f(msh_->faceList()[i]->mid().x()+msh_->faceList()[i]->n().x()
			//	       ,msh_->faceList()[i]->mid().y()+msh_->faceList()[i]->n().y()
			//		   ,msh_->faceList()[i]->mid().z()+msh_->faceList()[i]->n().z());

		}
		glEnd();
		break;
	case CUBE:
		cp_ = static_cast<Cube*>(obj_->getShape());
		glutWireCube(cp_->m_d);
		break;
	case SPHERE:
		sph_ = static_cast<Sphere*>(obj_->getShape());
		glutWireSphere(sph_->m_r,sph_->m_slices,sph_->m_stacks);
		break;
	case CONE:
		cne_ = static_cast<Cone*>(obj_->getShape());
		gluCylinder(qdr_,cne_->m_r,0.0,cne_->m_h,cne_->m_slices,cne_->m_stacks);
		gluDisk(qdr_,0,cne_->m_r,cne_->m_slices,1);
		break;
	case CYLINDER:
		cyld_ = static_cast<Cylinder*>(obj_->getShape());
		gluCylinder(qdr_,cyld_->m_r,cyld_->m_r,cyld_->m_h,cyld_->m_slices,cyld_->m_stacks);
		gluDisk(qdr_,0,cyld_->m_r,cyld_->m_slices,1);
		glTranslatef(0,0,cyld_->m_h);
		gluDisk(qdr_,0,cyld_->m_r,cyld_->m_slices,1);
		glTranslatef(0,0,-cyld_->m_h);
		break;
	case TWO_SIDED_CYLINDER:
		twcyl_ = static_cast<TwoSidedCylinder*>(obj_->getShape());
		gluCylinder(qdr_,twcyl_->m_base_r,twcyl_->m_top_r,twcyl_->m_h,twcyl_->m_slices,twcyl_->m_stacks);
		gluDisk(qdr_,0,twcyl_->m_base_r,twcyl_->m_slices,1);
		glTranslatef(0,0,twcyl_->m_h);
		gluDisk(qdr_,0,twcyl_->m_top_r,twcyl_->m_slices,1);
		glTranslatef(0,0,-twcyl_->m_h);
		break;
	case TORUS:
		trs_ = static_cast<Torus*>(obj_->getShape());
		glutWireTorus(trs_->m_in_r,trs_->m_out_r,trs_->m_sides,trs_->m_rings);
		break;
	case TRIANGLE_SHAPE:
		trngshp_ = static_cast<TriangleShape*>(obj_->getShape());
		glBegin(GL_LINE_LOOP);
		glVertex3f(trngshp_->m_p1.x(),trngshp_->m_p1.y(),trngshp_->m_p1.z());
		glVertex3f(trngshp_->m_p2.x(),trngshp_->m_p2.y(),trngshp_->m_p2.z());
		glVertex3f(trngshp_->m_p3.x(),trngshp_->m_p3.y(),trngshp_->m_p3.z());
		glEnd();
		break;
	case RECTANGLE:
		rect_ = static_cast<RectangleShape*>(obj_->getShape());
		glBegin(GL_LINE_LOOP);
		glVertex3f(rect_->m_x/2,rect_->m_y/2,0);
		glVertex3f(rect_->m_x/2,-rect_->m_y/2,0);
		glVertex3f(-rect_->m_x/2,-rect_->m_y/2,0);
		glVertex3f(-rect_->m_x/2,rect_->m_y/2,0);
		glEnd();
		break;
	case CIRCLE:
		circle_ = static_cast<Circle*>(obj_->getShape());
		gluDisk(qdr_,0,circle_->m_r,circle_->m_slices,circle_->m_loops);
		break;
	case DISK:
		disk_ = static_cast<Disk*>(obj_->getShape());
		gluDisk(qdr_,disk_->m_in_r,disk_->m_out_r,disk_->m_slices,disk_->m_loops);
		break;
	case PARTIAL_DISK:
		pdisk_ = static_cast<PartialDisk*>(obj_->getShape());
		gluPartialDisk(qdr_,pdisk_->m_in_r,pdisk_->m_out_r,pdisk_->m_slices,pdisk_->m_loops,
			pdisk_->start_ang,pdisk_->sweep_ang);
		break;
	default:
		break;
	}

	glLineWidth(1);
	glPopMatrix();

}
