#include "smcanvaswidget.h"


#include "../core/sphere.h"
#include "../core/cube.h"
#include "../core/cone.h"
#include "../core/trianglemesh.h"
#include "../core/cylinder.h"
#include "../core/twosidedcylinder.h"
#include "../core/torus.h"

#include "../core/triangleshape.h"
#include "../core/rectangle.h"
#include "../core/circle.h"
#include "../core/disk.h"
#include "../core/partialdisk.h"

#include "../glut.h"

#include <algorithm>


SMCanvasWidget::SMCanvasWidget(CanvasType typ_,Scene* sc_,QWidget *parent)
	: QGLWidget(parent) , m_scene(sc_)
{

	m_canvas_type = typ_ ; 

	setVisible(true);	

	setUpTypeSettings();

	//setFocusPolicy(Qt::NoFocus);

	m_drawing_type = WIRED ; 

	m_draw_tree_path = true;

	m_draw_cameras = true;
	m_draw_lights = true;
}

SMCanvasWidget::~SMCanvasWidget()
{

}

void SMCanvasWidget::setUpTypeSettings()
{
	m_camera = new EditingCamera();
	switch(m_canvas_type)
	{
	case PERSPECTIVE_VIEW:
		// grid
		m_grid = new CanvasGrid(XY_GRID);

		// camera
		m_camera->setPosition(Point3(20,-20,40));
		m_camera->setAtPoint(Point3(0,0,0));
		m_camera->setUpVector(Vector3(-1,1,1).normalize());
		m_camera->setName("Perspective");
		break;
	case TOP_VIEW:
		// grid
		m_grid = new CanvasGrid(XY_GRID);

		// camera
		m_camera->setPosition(Point3(0,0,30));
		m_camera->setAtPoint(Point3(0,0,0));
		m_camera->setUpVector(Vector3(0,1,0));
		m_camera->setName("Top");
		break;
	case RIGHT_VIEW:
		// grid
		m_grid = new CanvasGrid(YZ_GRID);

		// camera
		m_camera->setPosition(Point3(30,0,0));
		m_camera->setAtPoint(Point3(0,0,0));
		m_camera->setUpVector(Vector3(0,0,1));
		m_camera->setName("Right");
		break;
	case FRONT_VIEW:
		// grid
		m_grid = new CanvasGrid(XZ_GRID);

		// camera
		m_camera->setPosition(Point3(0,-30,0));
		m_camera->setAtPoint(Point3(0,0,0));
		m_camera->setUpVector(Vector3(0,0,1));
		m_camera->setName("Front");
		break;
	default:
		break;
	}
}

void SMCanvasWidget::initializeGL()
{
	GLfloat LightAmbient[]= { 0.1f, 0.1f, 0.1f, 1.0f }; 
	GLfloat LightDiffuse[]= { 0.25f, 0.25f,0.25f, 1.0f };
	GLfloat LightPosition[]= { 10.0f, 5.0f, 10.0f, 1.0f };	

	GLfloat LightAmbient1[]= { 0.1f, 0.1f, 0.1f, 1.0f }; 
	GLfloat LightDiffuse1[]= { 0.25f, 0.25f,0.25f, 1.0f };
	GLfloat LightPosition1[]= { 15.0f, 15.0f, -20.0f, 1.0f };	

	GLfloat LightAmbient2[]= { 0.1f, 0.1f, 0.1f, 1.0f }; 
	GLfloat LightDiffuse2[]= { 0.25f, 0.25f,0.25f, 1.0f };
	GLfloat LightPosition2[]= { -15.0f, 10.0f, -15.0f, 1.0f };



	glShadeModel(GL_FLAT);						// Enable Smooth Shading
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);			// Black Background
	glClearDepth(1.0f);							// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);						// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);							// The Type Of Depth Testing To Do


	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);	
	glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient1);	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse1);	
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition1);

	glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient2);	
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse2);	
	glLightfv(GL_LIGHT2, GL_POSITION,LightPosition2);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);	
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	glEnable(GL_COLOR_MATERIAL);

	glClearColor(   m_scene->backgroundColor().r ,
					m_scene->backgroundColor().g ,
					m_scene->backgroundColor().b ,1 );

	glEnable(GL_DOUBLEBUFFER);

}
void SMCanvasWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDrawBuffer(GL_FRONT_AND_BACK);

	glClearColor(  m_scene->backgroundColor().r ,
			       m_scene->backgroundColor().g ,
	               m_scene->backgroundColor().b ,1);

	//// Draw Axis
	glDisable(GL_LIGHTING);

	double ratio = (double)width() / (double)height();
	glTranslatef(-0.49*ratio,-0.47,-1.2);
	Vector3 dir_ = (m_camera->atPoint()-m_camera->position()).normalize();
	gluLookAt(0,0,0,
         dir_.x(),dir_.y(),dir_.z(),
         m_camera->upVector().x(),m_camera->upVector().y(),m_camera->upVector().z()
	  );
	
	glPutLetter(0.12,0,0,'x');
	glPutLetter(0,0.12,0,'y');
	glPutLetter(0,0,0.12,'z');

	glLineWidth(2);

	glBegin(GL_LINES);

	glColor3f(1.0,0,0);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.1,0.0,0.0);

	glColor3f(0,1.0,0);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0,0.1,0.0);

	glColor3f(0,0,1.0);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0,0,0.1);

	glEnd();

	glEnable(GL_LIGHTING);
	glLoadIdentity();
	//end or Draw axis


	gluLookAt(m_camera->position().x(),m_camera->position().y(),m_camera->position().z(),
	          m_camera->atPoint().x(),m_camera->atPoint().y(),m_camera->atPoint().z(),
	          m_camera->upVector().x(),m_camera->upVector().y(),m_camera->upVector().z()
		      ); 

	 //draw grids
	m_grid->draw();

	for(int i=0 ; i<m_scene->objects().size();i++)
	{
		switch(m_drawing_type)
		{
		case SHADED:
			drawShadedObject(m_scene->objects()[i]);
			break;
		case WIRED:
			drawWiredObject(m_scene->objects()[i]);
			break;
		case SHADED_WIRED:
			drawShadedWiredObject(m_scene->objects()[i]);
			break;
		}
	}
	if (SMGlobalSettings::getEditingMode()==VERTEX_EDITING_MODE)
	{
		for (int i=0 ; i<m_scene->objects().size();i++)
		{
			drawPoints(m_scene->objects()[i]);
		}
	}
	if(m_draw_tree_path)
	{
		glDisable(GL_LIGHTING);
		glLineWidth(3);
        glColor3f(1.0,1.0,0.0);

		for(int i=0 ; i<m_scene->objects().size();i++)
				drawObjectPath(m_scene->objects()[i]);

		glLineWidth(1);
		glEnable(GL_LIGHTING);
	}
	if(m_draw_lights)
	{
		glDisable(GL_LIGHTING);
		glLineWidth(3);
		for(int i=0 ; i<m_scene->lights().size();i++)
			drawLight(m_scene->lights()[i]);
		glLineWidth(1);
		glEnable(GL_LIGHTING);
	}
	if(m_draw_cameras)
	{
		for(int i=0 ; i<m_scene->cameras().size();i++)
			drawCamera(m_scene->cameras()[i]);
	}

	swapBuffers();
	glFlush();


}
void SMCanvasWidget::drawLight(Light *lg_)
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
void SMCanvasWidget::drawCamera(Camera* cm_)
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
void SMCanvasWidget::drawObjectPath(GfxObject* obj_)
{
	if(obj_->getParent()!= NULL)
	{
		Transformation globalTrns_ = *obj_->getParent()->getIndividualTranform()
			                         +*obj_->getParent()->getPublicTranform();
		Transformation indTrns_ = *obj_->getIndividualTranform() + *obj_->getPublicTranform();
		indTrns_ = indTrns_*(*obj_->getParent()->getPublicTranform());

		GfxObject* tmp_ = obj_->getParent()->getParent();

		while(tmp_ != NULL)
		{
			globalTrns_ = globalTrns_*(*tmp_->getPublicTranform());
			indTrns_ = indTrns_*(*tmp_->getPublicTranform());
			tmp_ = tmp_->getParent();
		}

		glBegin(GL_LINES);
		glVertex3f(indTrns_.translation().x(),indTrns_.translation().y(),indTrns_.translation().z());
		glVertex3f(globalTrns_.translation().x(),globalTrns_.translation().y(),globalTrns_.translation().z());
		glEnd();

  //		Vector3 transObj_ = indTrns_.translation().scale(globalTrns_.scale());
	 //   transObj_ = globalTrns_.rotation().applyToVector(transObj_);
		//transObj_ = transObj_ + globalTrns_.translation(); 

		//Vector3 trans2_ = globalTrns_.translation()+obj_->getParent()->getIndividualTranform()->translation();

		//glBegin(GL_LINES);
		//glVertex3f(trans1_.x(),trans1_.y(),trans1_.z());
		//glVertex3f(trans2_.x(),trans2_.y(),trans2_.z());
		//glEnd();
	}
}
void SMCanvasWidget::paintForVertexSelection()
{
	int indexCounter_ = 1;
	for (int k=0 ; k<m_scene->objects().size() ; k++)
	{
		GfxObject* obj_ = m_scene->objects()[k];
		if (obj_->getShape()->type() == TRIANGLE_MESH)
		{
			Transformation globalTrns_ =  *obj_->getIndividualTranform()+
				*obj_->getPublicTranform();
			GfxObject* tmp_ = obj_->getParent();

			while(tmp_ != NULL)
			{
				globalTrns_ = globalTrns_*(*tmp_->getPublicTranform());
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

			TriangleMesh* msh_ = static_cast<TriangleMesh*>(obj_->getShape()); 

			GLUquadric* qdr_ =  gluNewQuadric();
			gluQuadricDrawStyle(qdr_,GLU_FILL);

			for (int i=0 ; i<msh_->vertexList().size() ; i++)
			{
				glTranslatef(msh_->vertexList()[i]->x(),
					msh_->vertexList()[i]->y(),
					msh_->vertexList()[i]->z());

				glLoadName(indexCounter_);
				indexCounter_++;

				glutSolidCube(0.1);

				glTranslatef(-msh_->vertexList()[i]->x(),
					-msh_->vertexList()[i]->y(),
					-msh_->vertexList()[i]->z());
			}
			glPopMatrix();
		}
	}
}
void SMCanvasWidget::paintForFaceSelection()
{
	int indexCounter_ = 1;
	for (int k=0 ; k<m_scene->objects().size() ; k++)
	{
		GfxObject* obj_ = m_scene->objects()[k];
		if (obj_->getShape()->type() == TRIANGLE_MESH)
		{
			Transformation globalTrns_ =  *obj_->getIndividualTranform()+
				*obj_->getPublicTranform();
			GfxObject* tmp_ = obj_->getParent();

			while(tmp_ != NULL)
			{
				globalTrns_ = globalTrns_*(*tmp_->getPublicTranform());
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

			TriangleMesh* msh_ = static_cast<TriangleMesh*>(obj_->getShape()); 

			GLUquadric* qdr_ =  gluNewQuadric();
			gluQuadricDrawStyle(qdr_,GLU_FILL);

			for (int i=0 ; i<msh_->faceList().size() ; i++)
			{
				glLoadName(indexCounter_);
				indexCounter_++;

				glBegin(GL_TRIANGLES);
				glNormal3f(msh_->faceList()[i]->n().x(),msh_->faceList()[i]->n().y(),msh_->faceList()[i]->n().z());
				glVertex3f(msh_->faceList()[i]->a()->x(),msh_->faceList()[i]->a()->y(),msh_->faceList()[i]->a()->z());
				glVertex3f(msh_->faceList()[i]->b()->x(),msh_->faceList()[i]->b()->y(),msh_->faceList()[i]->b()->z());
				glVertex3f(msh_->faceList()[i]->c()->x(),msh_->faceList()[i]->c()->y(),msh_->faceList()[i]->c()->z());
				glEnd();
			}
			glPopMatrix();
		}
	}
}
void SMCanvasWidget::drawPoints(GfxObject* obj_)
{
	if (obj_->getShape()->type() == TRIANGLE_MESH)
	{
		Transformation globalTrns_ =  *obj_->getIndividualTranform()+
			*obj_->getPublicTranform();
		GfxObject* tmp_ = obj_->getParent();

		while(tmp_ != NULL)
		{
			globalTrns_ = globalTrns_*(*tmp_->getPublicTranform());
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

		TriangleMesh* msh_ = static_cast<TriangleMesh*>(obj_->getShape()); 

		GLUquadric* qdr_ =  gluNewQuadric();
		gluQuadricDrawStyle(qdr_,GLU_FILL);

		for (int i=0 ; i<msh_->vertexList().size() ; i++)
		{

			if (msh_->vertexList()[i]->isSelected())
			{
				glColor3f(1,0,0);
			}
			else
			{
				glColor3f(obj_->getMaterial()->diffcolor().r+0.5,
					   	obj_->getMaterial()->diffcolor().g-0.5,
						obj_->getMaterial()->diffcolor().b+0.5);
			}

			glTranslatef(msh_->vertexList()[i]->x(),
				         msh_->vertexList()[i]->y(),
						 msh_->vertexList()[i]->z());

			glutSolidCube(0.1);

			glTranslatef(-msh_->vertexList()[i]->x(),
						 -msh_->vertexList()[i]->y(),
						 -msh_->vertexList()[i]->z());
		}
		glPopMatrix();
	}
}
void SMCanvasWidget::drawWiredObject(GfxObject* obj_)
{
	Transformation globalTrns_ =  *obj_->getIndividualTranform()+
							  *obj_->getPublicTranform();
	GfxObject* tmp_ = obj_->getParent();

	while(tmp_ != NULL)
	{
		globalTrns_ = globalTrns_*(*tmp_->getPublicTranform());
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
			if(SMGlobalSettings::getEditingMode() == FACE_EDITING_MODE)
			{
				if(msh_->faceList()[i]->isSelected()){
					glColor3f(1,0,0);
					glLineWidth(2);
				}
				else{
					glColor3f(obj_->getMaterial()->diffcolor().r,
							  obj_->getMaterial()->diffcolor().g,
							  obj_->getMaterial()->diffcolor().b);
					glLineWidth(1);
				}
			}
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
void SMCanvasWidget::drawShadedObject(GfxObject* obj_)
{
	Transformation globalTrns_ =  *obj_->getIndividualTranform()+
							  *obj_->getPublicTranform();
	GfxObject* tmp_ = obj_->getParent();

	while(tmp_ != NULL)
	{
		globalTrns_ = globalTrns_*(*tmp_->getPublicTranform());
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
		for(int i=0 ; i<msh_->faceList().size();i++)
		{
			if(SMGlobalSettings::getEditingMode() == FACE_EDITING_MODE)
			{
				if(msh_->faceList()[i]->isSelected()){
					glColor3f(1,0,0);
				}
				else{
					glColor3f(obj_->getMaterial()->diffcolor().r,
							  obj_->getMaterial()->diffcolor().g,
							  obj_->getMaterial()->diffcolor().b);
				}
			}
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


	glPopMatrix();

}
void SMCanvasWidget::drawShadedWiredObject(GfxObject* obj_)
{
	Transformation globalTrns_ =  *obj_->getIndividualTranform()+
							  *obj_->getPublicTranform();
	GfxObject* tmp_ = obj_->getParent();

	while(tmp_ != NULL)
	{
		globalTrns_ = globalTrns_*(*tmp_->getPublicTranform());
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
			if(SMGlobalSettings::getEditingMode() == FACE_EDITING_MODE)
			{
				if(msh_->faceList()[i]->isSelected()){
					glColor3f(1,0,0);
				}
				else{
					glColor3f(obj_->getMaterial()->diffcolor().r,
							  obj_->getMaterial()->diffcolor().g,
							  obj_->getMaterial()->diffcolor().b);
				}
			}
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
void SMCanvasWidget::resizeGL(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	if(h == 0) h = 1;
	double ratio = (double)w / (double)h;

	glViewport(0, 0, w, h);

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // no transformations
	
	glFrustum(-0.5*ratio,0.5*ratio,-0.5,0.5,1.0,1000);
	

	//glMatrixMode(GL_MODELVIEW);
	//gluLookAt(m_camera->position().x(),m_camera->position().y(),m_camera->position().z(),
	//      m_camera->atPoint().x(),m_camera->atPoint().y(),m_camera->atPoint().z(),
	//      m_camera->upVector().x(),m_camera->upVector().y(),m_camera->upVector().z()
	//	  ); 
}
void SMCanvasWidget::glPutLetter(double x,double y,double z,char w)
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	double mvmatrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);

	double projmatrix[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

	//double x = 0.20, y = 0, z = 0;
	double winx, winy, winz;
	gluProject(x, y, z, mvmatrix, projmatrix, viewport, &winx, &winy, &winz);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewport[2], 0, viewport[3], -1, 1);


	glBegin(GL_LINES);

	if (w == 'x')
	{
		glColor3f(1.0,0,0);
		glVertex3f(winx - 5, winy, 0);
		glVertex3f(winx + 5, winy + 7, 0);

		glVertex3f(winx + 5, winy, 0);
		glVertex3f(winx - 5 , winy + 7, 0);
	}

	if (w == 'y')
	{
		glColor3f(0,1.0,0);
		glVertex3f(winx, winy, 0);
		glVertex3f(winx, winy + 5, 0);

		glVertex3f(winx, winy + 5, 0);
		glVertex3f(winx + 4 , winy + 10, 0);

		glVertex3f(winx, winy + 5, 0);
		glVertex3f(winx - 4 , winy + 10, 0);
	}

	if (w == 'z')
	{
		glColor3f(0,0,1.0);
		glVertex3f(winx - 3, winy, 0);
		glVertex3f(winx + 3, winy, 0);

		glVertex3f(winx - 3, winy + 10, 0);
		glVertex3f(winx + 3, winy + 10, 0);

		glVertex3f(winx - 3, winy, 0);
		glVertex3f(winx + 3 , winy + 10, 0);
	}

	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
//void SMCanvasWidget::drawGfxObjectTree(GfxObject* obj_,Transformation tr_)
//{
//
//	Transformation trns_ = tr_ ; 
//
//	switch(m_drawing_type)
//	{
//	case SHADED:
//		drawSingleObjectShaded(obj_,trns_);
//		break;
//	case WIRED:
//		drawSingleObjectWired(obj_,trns_);
//		break;
//	case SHADED_WIRED:
//		drawSingleObjectShadedWired(obj_,trns_);
//		break;
//	}
//
//	trns_ = *obj_->getPublicTranform()+tr_ ; 
//
//	for(int i=0 ; i<obj_->getChildList().size();i++)
//		drawGfxObjectTree(obj_->getChildList()[i],trns_);
//}
//void SMCanvasWidget::drawSingleObjectWired(GfxObject* obj_,Transformation tr_)
//{
//	glPushMatrix();
//	Transformation trns_ = tr_ ; 
//
//	glTranslatef(trns_.translation().x(),
//		         trns_.translation().y(),
//				 trns_.translation().z());
//
//	glScalef(trns_.scale().x(),
//		     trns_.scale().y(),
//			 trns_.scale().z());
//	glRotatef(trns_.rotation().theta(),
//			  trns_.rotation().ax(),
//		      trns_.rotation().ay(),
//			  trns_.rotation().az());
//
//	trns_ = *obj_->getIndividualTranform()+ *obj_->getPublicTranform() ;
//
//	glTranslatef(trns_.translation().x(),
//		         trns_.translation().y(),
//				 trns_.translation().z());
//	glScalef(trns_.scale().x(),
//		     trns_.scale().y(),
//			 trns_.scale().z());
//	glRotatef(trns_.rotation().theta(),
//			  trns_.rotation().ax(),
//		      trns_.rotation().ay(),
//			  trns_.rotation().az());
//
//	TriangleMesh* msh_;
//	Cube* cp_;
//	Sphere* sph_;
//	Cone* cne_;
//	Cylinder* cyld_;
//	TwoSidedCylinder* twcyl_;
//	Torus* trs_ ; 
//	TriangleShape* trngshp_;
//	RectangleShape* rect_;
//	Circle* circle_;
//	Disk* disk_;
//	PartialDisk* pdisk_;
//
//	if(obj_->isSelected())
//		glColor3f(1,0,0);
//	else
//		glColor3f(obj_->getMaterial()->diffcolor().r,
//				  obj_->getMaterial()->diffcolor().g,
//				  obj_->getMaterial()->diffcolor().b);
//
//	GLUquadric* qdr_ =  gluNewQuadric();
//	gluQuadricDrawStyle(qdr_,GLU_LINE);
//
//	switch(obj_->getShape()->type())
//	{
//	case TRIANGLE_MESH:
//		msh_ = static_cast<TriangleMesh*>(obj_->getShape());
//		glBegin(GL_LINES);
//		for(int i=0 ; i<msh_->refine().size();i++)
//		{
//			if(SMGlobalSettings::getEditingMode() == FACE_EDITING_MODE)
//			{
//				if(obj_->isSelected()){
//					glColor3f(1,0,0);
//					glLineWidth(2);
//				}
//				else{
//					glColor3f(obj_->getMaterial()->diffcolor().r,
//							  obj_->getMaterial()->diffcolor().g,
//							  obj_->getMaterial()->diffcolor().b);
//					glLineWidth(1);
//				}
//			}
//			glVertex3f(msh_->refine()[i]->a().x(),msh_->refine()[i]->a().y(),msh_->refine()[i]->a().z());
//			glVertex3f(msh_->refine()[i]->b().x(),msh_->refine()[i]->b().y(),msh_->refine()[i]->b().z());
//
//			glVertex3f(msh_->refine()[i]->b().x(),msh_->refine()[i]->b().y(),msh_->refine()[i]->b().z());
//			glVertex3f(msh_->refine()[i]->c().x(),msh_->refine()[i]->c().y(),msh_->refine()[i]->c().z());
//
//			glVertex3f(msh_->refine()[i]->c().x(),msh_->refine()[i]->c().y(),msh_->refine()[i]->c().z());
//			glVertex3f(msh_->refine()[i]->a().x(),msh_->refine()[i]->a().y(),msh_->refine()[i]->a().z());
//		}
//		glEnd();
//		glLineWidth(1);
//		break;
//	case CUBE:
//		cp_ = static_cast<Cube*>(obj_->getShape());
//		glutWireCube(cp_->m_d);
//		break;
//	case SPHERE:
//		sph_ = static_cast<Sphere*>(obj_->getShape());
//		glutWireSphere(sph_->m_r,sph_->m_slices,sph_->m_stacks);
//		break;
//	case CONE:
//		cne_ = static_cast<Cone*>(obj_->getShape());
//		gluCylinder(qdr_,cne_->m_r,0.0,cne_->m_h,cne_->m_slices,cne_->m_stacks);
//		break;
//	case CYLINDER:
//		cyld_ = static_cast<Cylinder*>(obj_->getShape());
//		gluCylinder(qdr_,cyld_->m_r,cyld_->m_r,cyld_->m_h,cyld_->m_slices,cyld_->m_stacks);
//		break;
//	case TWO_SIDED_CYLINDER:
//		twcyl_ = static_cast<TwoSidedCylinder*>(obj_->getShape());
//		gluCylinder(qdr_,twcyl_->m_base_r,twcyl_->m_top_r,twcyl_->m_h,twcyl_->m_slices,twcyl_->m_stacks);
//		break;
//	case TORUS:
//		trs_ = static_cast<Torus*>(obj_->getShape());
//		glutWireTorus(trs_->m_in_r,trs_->m_out_r,trs_->m_sides,trs_->m_rings);
//		break;
//	case TRIANGLE_SHAPE:
//		trngshp_ = static_cast<TriangleShape*>(obj_->getShape());
//		glBegin(GL_LINE_LOOP);
//		glVertex3f(trngshp_->m_p1.x(),trngshp_->m_p1.y(),trngshp_->m_p1.z());
//		glVertex3f(trngshp_->m_p2.x(),trngshp_->m_p2.y(),trngshp_->m_p2.z());
//		glVertex3f(trngshp_->m_p3.x(),trngshp_->m_p3.y(),trngshp_->m_p3.z());
//		glEnd();
//		break;
//	case RECTANGLE:
//		rect_ = static_cast<RectangleShape*>(obj_->getShape());
//		glBegin(GL_LINE_LOOP);
//		glVertex3f(rect_->m_x/2,rect_->m_y/2,0);
//		glVertex3f(rect_->m_x/2,-rect_->m_y/2,0);
//		glVertex3f(-rect_->m_x/2,-rect_->m_y/2,0);
//		glVertex3f(-rect_->m_x/2,rect_->m_y/2,0);
//		glEnd();
//		break;
//	case CIRCLE:
//		circle_ = static_cast<Circle*>(obj_->getShape());
//		gluDisk(qdr_,0,circle_->m_r,circle_->m_slices,circle_->m_loops);
//		break;
//	case DISK:
//		disk_ = static_cast<Disk*>(obj_->getShape());
//		gluDisk(qdr_,disk_->m_in_r,disk_->m_out_r,disk_->m_slices,disk_->m_loops);
//		break;
//	case PARTIAL_DISK:
//		pdisk_ = static_cast<PartialDisk*>(obj_->getShape());
//		gluPartialDisk(qdr_,pdisk_->m_in_r,pdisk_->m_out_r,pdisk_->m_slices,pdisk_->m_loops,
//			pdisk_->start_ang,pdisk_->sweep_ang);
//		break;
//	default:
//		break;
//	}
//	glPopMatrix();
//}
//void SMCanvasWidget::drawSingleObjectShadedWired(GfxObject* obj_,Transformation tr_)
//{
//	glPushMatrix();
//	Transformation trns_ = tr_ ; 
//
//	glTranslatef(trns_.translation().x(),
//		         trns_.translation().y(),
//				 trns_.translation().z());
//
//	glScalef(trns_.scale().x(),
//		     trns_.scale().y(),
//			 trns_.scale().z());
//	glRotatef(trns_.rotation().theta(),
//			  trns_.rotation().ax(),
//		      trns_.rotation().ay(),
//			  trns_.rotation().az());
//	
//
//	trns_ = *obj_->getIndividualTranform()+ *obj_->getPublicTranform() ;
//
//	glTranslatef(trns_.translation().x(),
//		         trns_.translation().y(),
//				 trns_.translation().z());
//	glScalef(trns_.scale().x(),
//		     trns_.scale().y(),
//			 trns_.scale().z());
//	glRotatef(trns_.rotation().theta(),
//			  trns_.rotation().ax(),
//		      trns_.rotation().ay(),
//			  trns_.rotation().az());
//	
//
//	TriangleMesh* msh_;
//	Cube* cp_;
//	Sphere* sph_;
//	Cone* cne_;
//	Cylinder* cyld_;
//	TwoSidedCylinder* twcyl_;
//	Torus* trs_ ; 
//	TriangleShape* trngshp_;
//	RectangleShape* rect_;
//	Circle* circle_;
//	Disk* disk_;
//	PartialDisk* pdisk_;
//
//	if(obj_->isSelected())
//		glColor3f(1,0,0);
//	else
//		glColor3f(obj_->getMaterial()->diffcolor().r,
//				  obj_->getMaterial()->diffcolor().g,
//				  obj_->getMaterial()->diffcolor().b);
//
//	GLUquadric* qdr_ =  gluNewQuadric();
//	gluQuadricDrawStyle(qdr_,GLU_FILL);
//
//	// shaded
//	switch(obj_->getShape()->type())
//	{
//	case TRIANGLE_MESH:
//		msh_ = static_cast<TriangleMesh*>(obj_->getShape());
//		glBegin(GL_TRIANGLES);
//		for(int i=0 ; i<msh_->refine().size();i++)
//		{
//			if(SMGlobalSettings::getEditingMode() == FACE_EDITING_MODE)
//			{
//				if(obj_->isSelected()){
//					glColor3f(1,0,0);
//				}
//				else{
//					glColor3f(obj_->getMaterial()->diffcolor().r,
//							  obj_->getMaterial()->diffcolor().g,
//							  obj_->getMaterial()->diffcolor().b);
//				}
//			}
//			glNormal3f(msh_->refine()[i]->n().x(),msh_->refine()[i]->n().y(),msh_->refine()[i]->n().z());
//			glVertex3f(msh_->refine()[i]->a().x(),msh_->refine()[i]->a().y(),msh_->refine()[i]->a().z());
//			glVertex3f(msh_->refine()[i]->b().x(),msh_->refine()[i]->b().y(),msh_->refine()[i]->b().z());
//			glVertex3f(msh_->refine()[i]->c().x(),msh_->refine()[i]->c().y(),msh_->refine()[i]->c().z());
//		}
//		glEnd();
//		break;
//	case CUBE:
//		cp_ = static_cast<Cube*>(obj_->getShape());
//		glutSolidCube(cp_->m_d);
//		break;
//	case SPHERE:
//		sph_ = static_cast<Sphere*>(obj_->getShape());
//		glutSolidSphere(sph_->m_r,sph_->m_slices,sph_->m_stacks);
//		break;
//	case CONE:
//		cne_ = static_cast<Cone*>(obj_->getShape());
//		gluCylinder(qdr_,cne_->m_r,0.0,cne_->m_h,cne_->m_slices,cne_->m_stacks);
//		break;
//	case CYLINDER:
//		cyld_ = static_cast<Cylinder*>(obj_->getShape());
//		gluCylinder(qdr_,cyld_->m_r,cyld_->m_r,cyld_->m_h,cyld_->m_slices,cyld_->m_stacks);
//		break;
//	case TWO_SIDED_CYLINDER:
//		twcyl_ = static_cast<TwoSidedCylinder*>(obj_->getShape());
//		gluCylinder(qdr_,twcyl_->m_base_r,twcyl_->m_top_r,twcyl_->m_h,twcyl_->m_slices,twcyl_->m_stacks);
//		break;
//	case TORUS:
//		trs_ = static_cast<Torus*>(obj_->getShape());
//		glutSolidTorus(trs_->m_in_r,trs_->m_out_r,trs_->m_sides,trs_->m_rings);
//		break;
//	case TRIANGLE_SHAPE:
//		trngshp_ = static_cast<TriangleShape*>(obj_->getShape());
//		glBegin(GL_TRIANGLES);
//		glVertex3f(trngshp_->m_p1.x(),trngshp_->m_p1.y(),trngshp_->m_p1.z());
//		glVertex3f(trngshp_->m_p2.x(),trngshp_->m_p2.y(),trngshp_->m_p2.z());
//		glVertex3f(trngshp_->m_p3.x(),trngshp_->m_p3.y(),trngshp_->m_p3.z());
//		glEnd();
//		break;
//	case RECTANGLE:
//		rect_ = static_cast<RectangleShape*>(obj_->getShape());
//		glBegin(GL_QUADS);
//		glVertex3f(rect_->m_x/2,rect_->m_y/2,0);
//		glVertex3f(rect_->m_x/2,-rect_->m_y/2,0);
//		glVertex3f(-rect_->m_x/2,-rect_->m_y/2,0);
//		glVertex3f(-rect_->m_x/2,rect_->m_y/2,0);
//		glEnd();
//		break;
//	case CIRCLE:
//		circle_ = static_cast<Circle*>(obj_->getShape());
//		gluDisk(qdr_,0,circle_->m_r,circle_->m_slices,circle_->m_loops);
//		break;
//	case DISK:
//		disk_ = static_cast<Disk*>(obj_->getShape());
//		gluDisk(qdr_,disk_->m_in_r,disk_->m_out_r,disk_->m_slices,disk_->m_loops);
//		break;
//	case PARTIAL_DISK:
//		pdisk_ = static_cast<PartialDisk*>(obj_->getShape());
//		gluPartialDisk(qdr_,pdisk_->m_in_r,pdisk_->m_out_r,pdisk_->m_slices,pdisk_->m_loops,
//			pdisk_->start_ang,pdisk_->sweep_ang);
//		break;
//	default:
//		break;
//	}
//
//	// wired
//	if(obj_->isSelected())
//		glColor3f(1,1,0);
//	else
//		glColor3f(obj_->getMaterial()->diffcolor().r-0.5,
//				  obj_->getMaterial()->diffcolor().g+0.5,
//			      obj_->getMaterial()->diffcolor().b-0.5);
//	
//
//	gluQuadricDrawStyle(qdr_,GLU_LINE);
//	glLineWidth(2);
//
//	switch(obj_->getShape()->type())
//	{
//	case TRIANGLE_MESH:
//		msh_ = static_cast<TriangleMesh*>(obj_->getShape());
//		glBegin(GL_LINES);
//		for(int i=0 ; i<msh_->refine().size();i++)
//		{
//			glVertex3f(msh_->refine()[i]->a().x(),msh_->refine()[i]->a().y(),msh_->refine()[i]->a().z());
//			glVertex3f(msh_->refine()[i]->b().x(),msh_->refine()[i]->b().y(),msh_->refine()[i]->b().z());
//
//			glVertex3f(msh_->refine()[i]->b().x(),msh_->refine()[i]->b().y(),msh_->refine()[i]->b().z());
//			glVertex3f(msh_->refine()[i]->c().x(),msh_->refine()[i]->c().y(),msh_->refine()[i]->c().z());
//
//			glVertex3f(msh_->refine()[i]->c().x(),msh_->refine()[i]->c().y(),msh_->refine()[i]->c().z());
//			glVertex3f(msh_->refine()[i]->a().x(),msh_->refine()[i]->a().y(),msh_->refine()[i]->a().z());
//		}
//		glEnd();
//		break;
//	case CUBE:
//		cp_ = static_cast<Cube*>(obj_->getShape());
//		glutWireCube(cp_->m_d);
//		break;
//	case SPHERE:
//		sph_ = static_cast<Sphere*>(obj_->getShape());
//		glutWireSphere(sph_->m_r,sph_->m_slices,sph_->m_stacks);
//		break;
//	case CONE:
//		cne_ = static_cast<Cone*>(obj_->getShape());
//		gluCylinder(qdr_,cne_->m_r,0.0,cne_->m_h,cne_->m_slices,cne_->m_stacks);
//		break;
//	case CYLINDER:
//		cyld_ = static_cast<Cylinder*>(obj_->getShape());
//		gluCylinder(qdr_,cyld_->m_r,cyld_->m_r,cyld_->m_h,cyld_->m_slices,cyld_->m_stacks);
//		break;
//	case TWO_SIDED_CYLINDER:
//		twcyl_ = static_cast<TwoSidedCylinder*>(obj_->getShape());
//		gluCylinder(qdr_,twcyl_->m_base_r,twcyl_->m_top_r,twcyl_->m_h,twcyl_->m_slices,twcyl_->m_stacks);
//		break;
//	case TORUS:
//		trs_ = static_cast<Torus*>(obj_->getShape());
//		glutWireTorus(trs_->m_in_r,trs_->m_out_r,trs_->m_sides,trs_->m_rings);
//		break;
//	case TRIANGLE_SHAPE:
//		trngshp_ = static_cast<TriangleShape*>(obj_->getShape());
//		glBegin(GL_LINE_LOOP);
//		glVertex3f(trngshp_->m_p1.x(),trngshp_->m_p1.y(),trngshp_->m_p1.z());
//		glVertex3f(trngshp_->m_p2.x(),trngshp_->m_p2.y(),trngshp_->m_p2.z());
//		glVertex3f(trngshp_->m_p3.x(),trngshp_->m_p3.y(),trngshp_->m_p3.z());
//		glEnd();
//		break;
//	case RECTANGLE:
//		rect_ = static_cast<RectangleShape*>(obj_->getShape());
//		glBegin(GL_LINE_LOOP);
//		glVertex3f(rect_->m_x/2,rect_->m_y/2,0);
//		glVertex3f(rect_->m_x/2,-rect_->m_y/2,0);
//		glVertex3f(-rect_->m_x/2,-rect_->m_y/2,0);
//		glVertex3f(-rect_->m_x/2,rect_->m_y/2,0);
//		glEnd();
//		break;
//	case CIRCLE:
//		circle_ = static_cast<Circle*>(obj_->getShape());
//		gluDisk(qdr_,0,circle_->m_r,circle_->m_slices,circle_->m_loops);
//		break;
//	case DISK:
//		disk_ = static_cast<Disk*>(obj_->getShape());
//		gluDisk(qdr_,disk_->m_in_r,disk_->m_out_r,disk_->m_slices,disk_->m_loops);
//		break;
//	case PARTIAL_DISK:
//		pdisk_ = static_cast<PartialDisk*>(obj_->getShape());
//		gluPartialDisk(qdr_,pdisk_->m_in_r,pdisk_->m_out_r,pdisk_->m_slices,pdisk_->m_loops,
//			pdisk_->start_ang,pdisk_->sweep_ang);
//		break;
//	default:
//		break;
//	}
//
//	glLineWidth(1);
//	glPopMatrix();
//}
//void SMCanvasWidget::drawSingleObjectShaded(GfxObject* obj_,Transformation tr_)
//{
//	glPushMatrix();
//	Transformation trns_ = tr_ ; 
//
//	glTranslatef(trns_.translation().x(),
//		         trns_.translation().y(),
//				 trns_.translation().z());
//
//	glScalef(trns_.scale().x(),
//		     trns_.scale().y(),
//			 trns_.scale().z());
//	glRotatef(trns_.rotation().theta(),
//			  trns_.rotation().ax(),
//		      trns_.rotation().ay(),
//			  trns_.rotation().az());
//
//
//	trns_ = *obj_->getIndividualTranform()+ *obj_->getPublicTranform() ;
//
//	glTranslatef(trns_.translation().x(),
//		         trns_.translation().y(),
//				 trns_.translation().z());
//	glScalef(trns_.scale().x(),
//		     trns_.scale().y(),
//			 trns_.scale().z());
//	glRotatef(trns_.rotation().theta(),
//			  trns_.rotation().ax(),
//		      trns_.rotation().ay(),
//			  trns_.rotation().az());
//	
//
//	TriangleMesh* msh_;
//	Cube* cp_;
//	Sphere* sph_;
//	Cone* cne_;
//	Cylinder* cyld_;
//	TwoSidedCylinder* twcyl_;
//	Torus* trs_ ; 
//	TriangleShape* trngshp_;
//	RectangleShape* rect_;
//	Circle* circle_;
//	Disk* disk_;
//	PartialDisk* pdisk_;
//
//	if(obj_->isSelected())
//		glColor3f(1,0,0);
//	else
//		glColor3f(obj_->getMaterial()->diffcolor().r,
//				  obj_->getMaterial()->diffcolor().g,
//				  obj_->getMaterial()->diffcolor().b);
//
//	GLUquadric* qdr_ =  gluNewQuadric();
//	gluQuadricDrawStyle(qdr_,GLU_FILL);
//
//	switch(obj_->getShape()->type())
//	{
//	case TRIANGLE_MESH:
//		msh_ = static_cast<TriangleMesh*>(obj_->getShape());
//		glBegin(GL_TRIANGLES);
//		for(int i=0 ; i<msh_->refine().size();i++)
//		{
//			if(SMGlobalSettings::getEditingMode() == FACE_EDITING_MODE)
//			{
//				if(obj_->isSelected()){
//					glColor3f(1,0,0);
//				}
//				else{
//					glColor3f(obj_->getMaterial()->diffcolor().r,
//							  obj_->getMaterial()->diffcolor().g,
//							  obj_->getMaterial()->diffcolor().b);
//				}
//			}
//			glNormal3f(msh_->refine()[i]->n().x(),msh_->refine()[i]->n().y(),msh_->refine()[i]->n().z());
//			glVertex3f(msh_->refine()[i]->a().x(),msh_->refine()[i]->a().y(),msh_->refine()[i]->a().z());
//			glVertex3f(msh_->refine()[i]->b().x(),msh_->refine()[i]->b().y(),msh_->refine()[i]->b().z());
//			glVertex3f(msh_->refine()[i]->c().x(),msh_->refine()[i]->c().y(),msh_->refine()[i]->c().z());
//		}
//		glEnd();
//		break;
//	case CUBE:
//		cp_ = static_cast<Cube*>(obj_->getShape());
//		glutSolidCube(cp_->m_d);
//		break;
//	case SPHERE:
//		sph_ = static_cast<Sphere*>(obj_->getShape());
//		glutSolidSphere(sph_->m_r,sph_->m_slices,sph_->m_stacks);
//		break;
//	case CONE:
//		cne_ = static_cast<Cone*>(obj_->getShape());
//		gluCylinder(qdr_,cne_->m_r,0.0,cne_->m_h,cne_->m_slices,cne_->m_stacks);
//		break;
//	case CYLINDER:
//		cyld_ = static_cast<Cylinder*>(obj_->getShape());
//		gluCylinder(qdr_,cyld_->m_r,cyld_->m_r,cyld_->m_h,cyld_->m_slices,cyld_->m_stacks);
//		break;
//	case TWO_SIDED_CYLINDER:
//		twcyl_ = static_cast<TwoSidedCylinder*>(obj_->getShape());
//		gluCylinder(qdr_,twcyl_->m_base_r,twcyl_->m_top_r,twcyl_->m_h,twcyl_->m_slices,twcyl_->m_stacks);
//		break;
//	case TORUS:
//		trs_ = static_cast<Torus*>(obj_->getShape());
//		glutSolidTorus(trs_->m_in_r,trs_->m_out_r,trs_->m_sides,trs_->m_rings);
//		break;
//	case TRIANGLE_SHAPE:
//		trngshp_ = static_cast<TriangleShape*>(obj_->getShape());
//		glBegin(GL_TRIANGLES);
//		glVertex3f(trngshp_->m_p1.x(),trngshp_->m_p1.y(),trngshp_->m_p1.z());
//		glVertex3f(trngshp_->m_p2.x(),trngshp_->m_p2.y(),trngshp_->m_p2.z());
//		glVertex3f(trngshp_->m_p3.x(),trngshp_->m_p3.y(),trngshp_->m_p3.z());
//		glEnd();
//		break;
//	case RECTANGLE:
//		rect_ = static_cast<RectangleShape*>(obj_->getShape());
//		glBegin(GL_QUADS);
//		glVertex3f(rect_->m_x/2,rect_->m_y/2,0);
//		glVertex3f(rect_->m_x/2,-rect_->m_y/2,0);
//		glVertex3f(-rect_->m_x/2,-rect_->m_y/2,0);
//		glVertex3f(-rect_->m_x/2,rect_->m_y/2,0);
//		glEnd();
//		break;
//	case CIRCLE:
//		circle_ = static_cast<Circle*>(obj_->getShape());
//		gluDisk(qdr_,0,circle_->m_r,circle_->m_slices,circle_->m_loops);
//		break;
//	case DISK:
//		disk_ = static_cast<Disk*>(obj_->getShape());
//		gluDisk(qdr_,disk_->m_in_r,disk_->m_out_r,disk_->m_slices,disk_->m_loops);
//		break;
//	case PARTIAL_DISK:
//		pdisk_ = static_cast<PartialDisk*>(obj_->getShape());
//		gluPartialDisk(qdr_,pdisk_->m_in_r,pdisk_->m_out_r,pdisk_->m_slices,pdisk_->m_loops,
//			pdisk_->start_ang,pdisk_->sweep_ang);
//		break;
//	default:
//		break;
//	}
//	glPopMatrix();
//}
void SMCanvasWidget::removeChildAt(int x_,int y_,int w_  , int h_)
{
		
	GLuint* buff = new GLuint[m_scene->objects().size()*5];
	GLint hits, view[4];
	int id;
	
	glSelectBuffer(m_scene->objects().size()*5, buff);
	glGetIntegerv(GL_VIEWPORT, view);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	gluPickMatrix((GLdouble)x_,(GLdouble)(height()-y_),w_, h_,view);

	double ratio;
	if(height() == 0) ratio = (double)width();
	else  ratio = (double)width() / (double)height();	
	glFrustum(-0.5*ratio,0.5*ratio,-0.5,0.5,1.0,1000);

	glMatrixMode(GL_MODELVIEW);
	swapBuffers();
	
	paintForPathSelection();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	hits = glRenderMode(GL_RENDER);	

	std::vector<int> list;
	int curDepth=INT_MAX;
	for(int i=0;i<hits;i++){
		if ((int)buff[i*4 + 3] != 0)
		{				
			if ((int)buff[i*4 + 2]<curDepth)
			{
				while(list.size()!=0)list.pop_back();
				list.push_back((int)buff[i*4 + 3]);
				curDepth = (int)buff[i*4 + 2];
			}					
		}		
	}
	if(list.size()>0)
	{
		m_scene->objects()[list[0]-1]->getParent()->removeChildAt(m_scene->objects()[list[0]-1]->getChildIndex());
	}

	glMatrixMode(GL_MODELVIEW);
	delete buff;
}
void SMCanvasWidget::selectCamera(int x_ , int y_ , int w_  , int h_ )
{
	GLuint* buff = new GLuint[m_scene->cameras().size()*5];
	GLint hits, view[4];
	int id;
	
	glSelectBuffer(m_scene->cameras().size()*5, buff);
	glGetIntegerv(GL_VIEWPORT, view);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	gluPickMatrix((GLdouble)x_,(GLdouble)(height()-y_),w_, h_,view);

	double ratio;
	if(height() == 0) ratio = (double)width();
	else  ratio = (double)width() / (double)height();	
	glFrustum(-0.5*ratio,0.5*ratio,-0.5,0.5,1.0,1000);

	glMatrixMode(GL_MODELVIEW);
	swapBuffers();
	
	paintForCameraSelection();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	hits = glRenderMode(GL_RENDER);	

	std::vector<int> list;
	int curDepth=INT_MAX;
	for(int i=0;i<hits;i++){
		if ((int)buff[i*4 + 3] != 0)
		{				
			if ((int)buff[i*4 + 2]<curDepth)
			{
				while(list.size()!=0)list.pop_back();
				list.push_back((int)buff[i*4 + 3]);
				curDepth = (int)buff[i*4 + 2];
			}					
		}		
	}
	if(list.size()>0)
	{
		m_scene->cameras()[list[0]-1]->select(true);
	}

	glMatrixMode(GL_MODELVIEW);
	delete buff;
}
void SMCanvasWidget::selectOnlyTarget(int x_ , int y_ , int w_ , int h_ )
{
	GLuint* buff = new GLuint[m_scene->cameras().size()*5];
	GLint hits, view[4];
	int id;

	glSelectBuffer(m_scene->cameras().size()*5, buff);
	glGetIntegerv(GL_VIEWPORT, view);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluPickMatrix((GLdouble)x_,(GLdouble)(height()-y_),w_, h_,view);

	double ratio;
	if(height() == 0) ratio = (double)width();
	else  ratio = (double)width() / (double)height();	
	glFrustum(-0.5*ratio,0.5*ratio,-0.5,0.5,1.0,1000);

	glMatrixMode(GL_MODELVIEW);
	swapBuffers();

	//paint only targets
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDrawBuffer(GL_FRONT_AND_BACK);
	gluLookAt(m_camera->position().x(),m_camera->position().y(),m_camera->position().z(),
		m_camera->atPoint().x(),m_camera->atPoint().y(),m_camera->atPoint().z(),
		m_camera->upVector().x(),m_camera->upVector().y(),m_camera->upVector().z()
		); 
	for(int i=0 ; i<m_scene->cameras().size();i++)
	{
		glLoadName(i+1);

		Camera* cm_ = m_scene->cameras()[i];
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

		glTranslatef(0,0,-lngth_);
		gluSphere(qdr_,0.3,10,10);	

		glPopMatrix();
	}
	//

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	hits = glRenderMode(GL_RENDER);	

	std::vector<int> list;
	int curDepth=INT_MAX;
	for(int i=0;i<hits;i++){
		if ((int)buff[i*4 + 3] != 0)
		{				
			if ((int)buff[i*4 + 2]<curDepth)
			{
				while(list.size()!=0)list.pop_back();
				list.push_back((int)buff[i*4 + 3]);
				curDepth = (int)buff[i*4 + 2];
			}					
		}		
	}
	if(list.size()>0)
	{
		m_scene->cameras()[list[0]-1]->select(true);
	}

	glMatrixMode(GL_MODELVIEW);
	delete buff;
}
void SMCanvasWidget::selectOnlyCamera(int x_ , int y_ , int w_  , int h_ )
{
	GLuint* buff = new GLuint[m_scene->cameras().size()*5];
	GLint hits, view[4];
	int id;

	glSelectBuffer(m_scene->cameras().size()*5, buff);
	glGetIntegerv(GL_VIEWPORT, view);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluPickMatrix((GLdouble)x_,(GLdouble)(height()-y_),w_, h_,view);

	double ratio;
	if(height() == 0) ratio = (double)width();
	else  ratio = (double)width() / (double)height();	
	glFrustum(-0.5*ratio,0.5*ratio,-0.5,0.5,1.0,1000);

	glMatrixMode(GL_MODELVIEW);
	swapBuffers();

	//paint only camera
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDrawBuffer(GL_FRONT_AND_BACK);
	gluLookAt(m_camera->position().x(),m_camera->position().y(),m_camera->position().z(),
		m_camera->atPoint().x(),m_camera->atPoint().y(),m_camera->atPoint().z(),
		m_camera->upVector().x(),m_camera->upVector().y(),m_camera->upVector().z()
		); 
	for(int i=0 ; i<m_scene->cameras().size();i++)
	{
		glLoadName(i+1);

		Camera* cm_ = m_scene->cameras()[i];
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

		glPopMatrix();

	}
	//

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	hits = glRenderMode(GL_RENDER);	

	std::vector<int> list;
	int curDepth=INT_MAX;
	for(int i=0;i<hits;i++){
		if ((int)buff[i*4 + 3] != 0)
		{				
			if ((int)buff[i*4 + 2]<curDepth)
			{
				while(list.size()!=0)list.pop_back();
				list.push_back((int)buff[i*4 + 3]);
				curDepth = (int)buff[i*4 + 2];
			}					
		}		
	}
	if(list.size()>0)
	{
		m_scene->cameras()[list[0]-1]->select(true);
	}

	glMatrixMode(GL_MODELVIEW);
	delete buff;
}
void SMCanvasWidget::selectFace(int x_ , int y_ , int w_ , int h_)
{
	GLuint* buff = new GLuint[m_scene->totalFaceCount()*5];
	GLint hits, view[4];
	int id;

	glSelectBuffer(m_scene->totalFaceCount()*5, buff);
	glGetIntegerv(GL_VIEWPORT, view);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluPickMatrix((GLdouble)x_,(GLdouble)(height()-y_),w_, h_,view);

	double ratio;
	if(height() == 0) ratio = (double)width();
	else  ratio = (double)width() / (double)height();	
	glFrustum(-0.5*ratio,0.5*ratio,-0.5,0.5,1.0,1000);

	glMatrixMode(GL_MODELVIEW);
	swapBuffers();

	paintForFaceSelection();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	hits = glRenderMode(GL_RENDER);	

	std::vector<int> list;
	int curDepth=INT_MAX;
	for(int i=0;i<hits;i++){
		if ((int)buff[i*4 + 3] != 0)
		{				
			if ((int)buff[i*4 + 2]<curDepth)
			{
				while(list.size()!=0)list.pop_back();
				list.push_back((int)buff[i*4 + 3]);
				curDepth = (int)buff[i*4 + 2];
			}					
		}		
	}
	if(list.size()>0)
	{
		int slctd_ = list[0];
		int cntr_ = 0;
		for (int k=0 ; k<m_scene->objects().size();k++)
		{
			if (m_scene->objects()[k]->getShape()->type() == TRIANGLE_MESH)
			{
				TriangleMesh* msh_ = static_cast<TriangleMesh* >(m_scene->objects()[k]->getShape());
				if (msh_->faceList().size() > slctd_-cntr_-1 )
				{
					msh_->faceList()[slctd_-cntr_-1]->select(true);
					break;
				}
				else cntr_ += msh_->faceList().size();
			}
			
		}
		//m_scene->lights()[list[0]-1]->select(true);
	}

	glMatrixMode(GL_MODELVIEW);
	delete buff;
}
void SMCanvasWidget::selectVertex(int x_ , int y_ , int w_ , int h_)
{
	GLuint* buff = new GLuint[m_scene->totalVertexCount()*5];
	GLint hits, view[4];
	int id;

	glSelectBuffer(m_scene->totalVertexCount()*5, buff);
	glGetIntegerv(GL_VIEWPORT, view);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluPickMatrix((GLdouble)x_,(GLdouble)(height()-y_),w_, h_,view);

	double ratio;
	if(height() == 0) ratio = (double)width();
	else  ratio = (double)width() / (double)height();	
	glFrustum(-0.5*ratio,0.5*ratio,-0.5,0.5,1.0,1000);

	glMatrixMode(GL_MODELVIEW);
	swapBuffers();

	paintForVertexSelection();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	hits = glRenderMode(GL_RENDER);	

	std::vector<int> list;
	int curDepth=INT_MAX;
	for(int i=0;i<hits;i++){
		if ((int)buff[i*4 + 3] != 0)
		{				
			if ((int)buff[i*4 + 2]<curDepth)
			{
				while(list.size()!=0)list.pop_back();
				list.push_back((int)buff[i*4 + 3]);
				curDepth = (int)buff[i*4 + 2];
			}					
		}		
	}
	if(list.size()>0)
	{
		int slctd_ = list[0];
		int cntr_ = 0;
		for (int k=0 ; k<m_scene->objects().size();k++)
		{
			if (m_scene->objects()[k]->getShape()->type() == TRIANGLE_MESH)
			{
				TriangleMesh* msh_ = static_cast<TriangleMesh* >(m_scene->objects()[k]->getShape());
				if (msh_->vertexList().size() > slctd_-cntr_-1 )
				{
					msh_->vertexList()[slctd_-cntr_-1]->select(true);
					break;
				}
				else cntr_ += msh_->vertexList().size();
			}
		}
		//m_scene->lights()[list[0]-1]->select(true);
	}

	glMatrixMode(GL_MODELVIEW);
	delete buff;
}
void SMCanvasWidget::selectLight(int x_ , int y_ , int w_  , int h_)
{
	GLuint* buff = new GLuint[m_scene->lights().size()*5];
	GLint hits, view[4];
	int id;
	
	glSelectBuffer(m_scene->lights().size()*5, buff);
	glGetIntegerv(GL_VIEWPORT, view);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	gluPickMatrix((GLdouble)x_,(GLdouble)(height()-y_),w_, h_,view);

	double ratio;
	if(height() == 0) ratio = (double)width();
	else  ratio = (double)width() / (double)height();	
	glFrustum(-0.5*ratio,0.5*ratio,-0.5,0.5,1.0,1000);

	glMatrixMode(GL_MODELVIEW);
	swapBuffers();
	
	paintForLightSelection();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	hits = glRenderMode(GL_RENDER);	

	std::vector<int> list;
	int curDepth=INT_MAX;
	for(int i=0;i<hits;i++){
		if ((int)buff[i*4 + 3] != 0)
		{				
			if ((int)buff[i*4 + 2]<curDepth)
			{
				while(list.size()!=0)list.pop_back();
				list.push_back((int)buff[i*4 + 3]);
				curDepth = (int)buff[i*4 + 2];
			}					
		}		
	}
	if(list.size()>0)
	{
		m_scene->lights()[list[0]-1]->select(true);
	}

	glMatrixMode(GL_MODELVIEW);
	delete buff;
}
bool SMCanvasWidget::selectObject(int x_,int y_,int w_ , int h_)
{
	bool result_ = false;
		
	GLuint* buff = new GLuint[m_scene->objects().size()*5];
	GLint hits, view[4];
	int id;
	
// Two sided selection is ON. if we want to select only front faces, we will make enable GL_CULL_FACE.
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_FRONT);

	glSelectBuffer(m_scene->objects().size()*5, buff);
	glGetIntegerv(GL_VIEWPORT, view);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	gluPickMatrix((GLdouble)x_,(GLdouble)(height()-y_),w_, h_,view);

	double ratio;
	if(height() == 0) ratio = (double)width();
	else  ratio = (double)width() / (double)height();	
	glFrustum(-0.5*ratio,0.5*ratio,-0.5,0.5,1.0,1000);

	glMatrixMode(GL_MODELVIEW);
	swapBuffers();
	
	paintForObjectSelection();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	hits = glRenderMode(GL_RENDER);	
	
	result_ = getPickedObjectsInfo(hits,buff);
	glMatrixMode(GL_MODELVIEW);
	delete buff;

	return result_;

//	glDisable(GL_CULL_FACE);
}
bool SMCanvasWidget::getPickedObjectsInfo(GLint hits_,GLuint* buff_)
{
	std::vector<int> list;
	int curDepth=INT_MAX;

	for(int i=0;i<hits_;i++){
		if ((int)buff_[i*4 + 3] != 0)
		{				
			//if (m_single_selection )
			//{
			if ((int)buff_[i*4 + 2]<curDepth)
			{
				while(list.size()!=0)list.pop_back();
				list.push_back((int)buff_[i*4 + 3]);
				curDepth = (int)buff_[i*4 + 2];
			}					
			//}
			//else
			//{
			//	list.push_back((int)buff_[i*4 + 3]);
			//}
		}		
	}

	if(list.size()>0)
	m_scene->objects()[list[0]-1]->select(true);

    //   m_obj_sel_counter = 1;
	//for(int i=0 ; i<m_scene->objects().size();i++)
	//	if(m_scene->objects()[i]->getParent() == NULL)
	//		traverseSelectedObjectList(list,m_scene->objects()[i]);
	return list.size()>0;
}
void SMCanvasWidget::paintForObjectSelection()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDrawBuffer(GL_FRONT_AND_BACK);

	glClearColor(  m_scene->backgroundColor().r ,
			       m_scene->backgroundColor().g ,
	               m_scene->backgroundColor().b ,1);

	gluLookAt(m_camera->position().x(),m_camera->position().y(),m_camera->position().z(),
	          m_camera->atPoint().x(),m_camera->atPoint().y(),m_camera->atPoint().z(),
	          m_camera->upVector().x(),m_camera->upVector().y(),m_camera->upVector().z()
		      ); 

	for(int i=0 ; i<m_scene->objects().size();i++)
	{
		glLoadName(i+1);
		drawShadedObject(m_scene->objects()[i]);
	}
}
void SMCanvasWidget::paintForPathSelection()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDrawBuffer(GL_FRONT_AND_BACK);

	glClearColor(  m_scene->backgroundColor().r ,
			       m_scene->backgroundColor().g ,
	               m_scene->backgroundColor().b ,1);

	gluLookAt(m_camera->position().x(),m_camera->position().y(),m_camera->position().z(),
	          m_camera->atPoint().x(),m_camera->atPoint().y(),m_camera->atPoint().z(),
	          m_camera->upVector().x(),m_camera->upVector().y(),m_camera->upVector().z()
		      ); 

	for(int i=0 ; i<m_scene->objects().size();i++)
	{
		glLoadName(i+1);
		drawObjectPath(m_scene->objects()[i]);
	}
}
void SMCanvasWidget::paintForCameraSelection()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDrawBuffer(GL_FRONT_AND_BACK);

	glClearColor(  m_scene->backgroundColor().r ,
			       m_scene->backgroundColor().g ,
	               m_scene->backgroundColor().b ,1);

	gluLookAt(m_camera->position().x(),m_camera->position().y(),m_camera->position().z(),
	          m_camera->atPoint().x(),m_camera->atPoint().y(),m_camera->atPoint().z(),
	          m_camera->upVector().x(),m_camera->upVector().y(),m_camera->upVector().z()
		      ); 

	for(int i=0 ; i<m_scene->cameras().size();i++)
	{
		glLoadName(i+1);
		drawCamera(m_scene->cameras()[i]);
	}
}
void SMCanvasWidget::paintForLightSelection()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDrawBuffer(GL_FRONT_AND_BACK);

	glClearColor(  m_scene->backgroundColor().r ,
			       m_scene->backgroundColor().g ,
	               m_scene->backgroundColor().b ,1);

	gluLookAt(m_camera->position().x(),m_camera->position().y(),m_camera->position().z(),
	          m_camera->atPoint().x(),m_camera->atPoint().y(),m_camera->atPoint().z(),
	          m_camera->upVector().x(),m_camera->upVector().y(),m_camera->upVector().z()
		      ); 

	for(int i=0 ; i<m_scene->lights().size();i++)
	{
		glLoadName(i+1);
		drawLight(m_scene->lights()[i]);
	}
}

//void SMCanvasWidget::traverseSelectedObjectList(std::vector<int> sel_,GfxObject* obj_)
//{
//	for(int i=0 ; i<sel_.size();i++){
//		if(sel_[i] == m_obj_sel_counter){
//			obj_->select(true);
//			break;
//		}
//	}
//	m_obj_sel_counter ++;
//	for(int i=0 ; i<obj_->getChildList().size();i++)
//		traverseSelectedObjectList(sel_,obj_->getChildList()[i]);
//}
//void SMCanvasWidget::drawGfxObjectSelections(GfxObject* obj_,Transformation tr_)
//{
//
//	Transformation trns_ = tr_ ; 
//	
//	glLoadName(m_obj_sel_counter);
//	m_obj_sel_counter++;
//	drawSingleObjectShaded(obj_,trns_);
//
//	trns_ = *obj_->getPublicTranform()+tr_ ;
//
//	for(int i=0 ; i<obj_->getChildList().size();i++)
//		drawGfxObjectSelections(obj_->getChildList()[i],trns_);
//
//}
//void SMCanvasWidget::drawObjectTreePath(GfxObject* obj_,Transformation tr_)
//{
//	Transformation trns_ = tr_ ;
//	drawSingleObjectPath(obj_,trns_);
//	trns_ = *obj_->getPublicTranform()+tr_ ; 
//	for(int i=0 ; i<obj_->getChildList().size();i++)
//		drawObjectTreePath(obj_->getChildList()[i],trns_);
//}
//void SMCanvasWidget::drawSingleObjectPath(GfxObject* obj_,Transformation tr_)
//{
//	glPushMatrix();
//	Transformation trns_ = tr_ ; 
//
//	glTranslatef(trns_.translation().x(),
//		         trns_.translation().y(),
//				 trns_.translation().z());
//
//	glScalef(trns_.scale().x(),
//		     trns_.scale().y(),
//			 trns_.scale().z());
//	glRotatef(trns_.rotation().theta(),
//			  trns_.rotation().ax(),
//		      trns_.rotation().ay(),
//			  trns_.rotation().az());
//
//	if(obj_->getParent()!= NULL)
//	{
//		Point3 p_ = obj_->getParent()->getShape()->object_bound().center();
//		Vector3 v1_ = Vector3(p_.x(),p_.y(),p_.z());
//		v1_ = v1_ + obj_->getParent()->getIndividualTranform()->translation();
//		p_ = obj_->getShape()->object_bound().center();
//		Vector3 v2_ = Vector3(p_.x(),p_.y(),p_.z());
//		v2_ = v2_ + obj_->getIndividualTranform()->translation() + obj_->getPublicTranform()->translation() ;
//		glBegin(GL_LINES);
//		glVertex3f(v1_.x(),v1_.y(),v1_.z());
//		glVertex3f(v2_.x(),v2_.y(),v2_.z());
//		glEnd();
//
//	}
//	glPopMatrix();
//}