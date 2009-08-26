#include "common.h"

Scene* scne_ = NULL;
Camera* cmr_ = NULL;
SceneDrawer* drawer_ = NULL;

void initGLOptions()
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
	glClearColor(0.0f, 0.1f, 0.1f, 0.0f);			// Black Background
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

}

void createScene(Scene* scn_)
{
	/*GfxObject* new_obj1 = new GfxObject(new RectangleShape(),new Material(),new Transformation());
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

	//*scn_ += new_obj1;
	*scn_ += new_obj2;
    *scn_ += new_obj3;
	*scn_ += new_obj4;
	*scn_ += new_obj5;
	*scn_ += new_obj6;*/

    VrmlDevice vrml_dev;

    vrml_dev.loadScene("chapel_97-3.wrl", scn_);
    // cout << "OBJS:" << scn_->objects().size() << endl;

    GfxObject* ob = scn_->objects()[0];
    TriangleMesh* mesh_ = (TriangleMesh*)(ob->getShape());

    if (scn_->cameras().size() != 0)
    {
        // blender setup
        cmr_ = scn_->cameras()[0];
        cout << "CFR: " << cmr_->position().x() << " * " << cmr_->position().y() << " * " << cmr_->position().z() << endl;
        cout << "CTO: " << cmr_->atPoint().x() << " * " << cmr_->atPoint().y() << " * " << cmr_->atPoint().z() << endl;
        cout << "CUP: " << cmr_->upVector().x() << " * " << cmr_->upVector().y() << " * " << cmr_->upVector().z() << endl;

        cout << "OBJ::" << scn_->objects()[0]->getName() << endl;
    }
    else
    {
        cmr_ = new Camera();
        // serhat's setup:
        // cmr_->setPosition(Point3(30,30,10));
        // cmr_->setAtPoint(Point3(0,0,0));
        // cmr_->setUpVector(Vector3(-0.5,-0.5,6).normalize());

        // basar's manual setup: for chapel.wrl
        cmr_->setPosition( Point3(0, 5, 5) );
        cmr_->setAtPoint( Point3(0, 0, 0) );
        cmr_->setUpVector( Vector3(0, 1, 0).normalize() );
    }


//	vrml_dev.saveToFile("output.wrl", scn_);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDrawBuffer(GL_FRONT_AND_BACK);

	if (drawer_ != NULL)
	{
		drawer_->drawShadedScene(scne_, cmr_);
	}

	glutSwapBuffers();
}

void reshape(GLint w, GLint h)
{
	// Prevent a divide by zero, when window is too short
	if(h == 0) h = 1;
    double ratio = (double)w / (double)h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // no transformations

	glFrustum(-0.5*ratio, 0.5*ratio, -0.5, 0.5, 1.0, 1000);

	display();
}


bool lmd = false;
float rot = 0;
Transformation cam_x;

void mouse(int mb, int state, int x, int y)
{
    if (mb == 0)
        lmd = (state == 0);
}

void motion(int x, int y)
{
    if (lmd)
    {
        Point3 cam_pos = cmr_->position();
        rot += 0.0001;
        cam_x.rotate(0, 1, 0, rot);
        cam_pos = cam_x.rotationMatrix() * cam_pos;
        cmr_->setPosition(cam_pos);

        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) // ESC
        exit(0);
}

int main(int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitWindowSize (600, 600);
	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow ("SM_API with GLUT ");

	initGLOptions();

	scne_ = new Scene();
	createScene(scne_);
	drawer_ = new SceneDrawer();


    glutMouseFunc(mouse);
    glutMotionFunc (motion);
    glutKeyboardFunc (keyboard);
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);


	glutMainLoop ();
	return 0;
}
