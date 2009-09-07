#include "common.h"

#include "IGlut.h"
#include "HeadTrackerClient.h"
#include "wiimote.h"

#include <fstream>
#include <stdexcept>

extern char wii_msg[255]; // to use in opengl context

HeadTrackerClient* IGlut::p_htc;

Scene* IGlut::p_scene;

Camera* IGlut::p_camera;

CanvasGrid* IGlut::p_grid;

SceneDrawer* IGlut::p_drawer;

RenderController* IGlut::p_rc;

Light* IGlut::p_light;

int IGlut::submenus[1];

using namespace glut_env;

IGlut::IGlut(int argc, char** argv)
{
    full_screen = false;

    cm_win_width = 85;
    cm_win_height = 64;

    px_win_width = 1024;
    px_win_height = 768;

    cm_user_height = 70;

    cm_user_to_screen_center = 70;

    deg_user_yaw = 0.0;

    K = 0.1;

    last_x = 0;
    last_y = 0;

    Buttons[0] = 0;
    Buttons[1] = 0;
    Buttons[2] = 0;

    delta_t = 1.f;
    use_camera = false;
    use_wiimote = false;
    online_mode = false;

    half_eye_sep_x = 0.f;
    half_eye_sep_y = 0.f;

    p_htc = NULL;

    p_scene = new Scene();

    /// VRML file should be taken as program argument.
    //CreateScene(p_scene, argv[1]);
    CreateScene("res/chapel_97-5.wrl");
    //CreateScene("res/box.wrl");

    p_camera = new Camera( Point3(0, -cm_user_to_screen_center, cm_user_height) );

    p_grid = new CanvasGrid( XY_GRID );
    p_grid->setAxesDrawn(false);

    p_drawer = new SceneDrawer();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STEREO);

    glutInitWindowSize(px_win_width, px_win_height);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - px_win_width) * 0.5,
                           (glutGet(GLUT_SCREEN_HEIGHT) - px_win_height) * 0.5 );

    glutCreateWindow("Stereo VRML Viewer | BoUn CmpE Medialab");

}

IGlut::~IGlut()
{
    if (p_htc != NULL)
        CloseHeadTracker();

    disconnect_wiimote();

    delete p_scene;
    delete p_camera;
    delete p_drawer;
    delete p_grid;
    delete p_rc;
    delete p_light;
}

void IGlut::Init()
{
    glutDisplayFunc(Display);
    glutTimerFunc(20, Timer, 0);
    glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMotionFunc(Motion);

    PrepareMenus();

    // glutFullScreen();
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, gl_light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, gl_ambient_intensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, gl_light_intensity);
	glLightfv(GL_LIGHT0, GL_SPECULAR, gl_light_intensity);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_FLAT);

	glutMainLoop();
}

void IGlut::PrepareMenus()
{
    submenus[0] = glutCreateMenu( SelectOption );
    glutAddMenuEntry("Toggle fullscreen view", 0);
    glutAddMenuEntry("Render the scene", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void IGlut::Motion(int x, int y)
{
    if (Buttons[0])
    {
        UpdateUserPositionByMouse(x, y);
    }
    else if (Buttons[2])
    {
        // right click + y movement: affects z
        p_camera->setPosition( Point3(p_camera->position().x(),
                                      p_camera->position().y(),
                                      cm_user_height + (y - px_win_width*0.5) * 2) );
        // cout << cam_pos.z << endl;
    }

	glutPostRedisplay();
}

void IGlut::SelectOption(int opt)
{
    glutSetMenu( -1 );

    switch (opt)
    {
        case TOGGLE_FULLSCREEN:
            full_screen = !full_screen;

            if ( full_screen && glutGameModeGet(GLUT_GAME_MODE_ACTIVE) == 0 ) //argc > 2 && strcmp(argv[2], "f") == 0)
            {
                // Enter game mode:
                char mode_string[100];
                // DOUBLE SCREEN:
                // sprintf(mode_string, "%dx%d:%d@%d", 1024, 1536, 32, 120);
                // SINGLE SCREEN:
                sprintf(mode_string, "%dx%d:%d@%d", 1024, 768, 32, 120);
                cout << "GLUT-Game-Mode: " << mode_string << endl;
                glutGameModeString( mode_string );
                glutEnterGameMode();

                // register callbacks again
                Init();
            }
            else
            {
                glutLeaveGameMode();
            }
            break;

        case RENDER_SCENE:
            if (p_rc == NULL)
                p_rc = new RenderController();

            /// We use asymmetric frustum for off-axis projection in OpenGL;
            /// therefore we have to correct the camera direction for rendering:
            Point3 save_lookAt( p_camera->atPoint() );
            Vector3 save_upVector( p_camera->upVector() );

            p_camera->setAtPoint( Point3(0, 0, 0) );
            p_camera->setUpVector( Vector3(0, 0, 1) );

            p_rc->render(p_scene, p_camera);

            p_camera->setAtPoint( save_lookAt );
            p_camera->setUpVector( save_upVector );

            break;
    }
}

void IGlut::Keyboard(unsigned char key, int x, int y)
{
    if (key == 'g' || key == 'G')
    {
        SelectOption( TOGGLE_FULLSCREEN );
    }
    else if (key == 'c' || key == 'C')
    {
        use_camera = !use_camera;

        if (use_camera) // Reinitialize head:
        {
            if (p_htc == NULL)
                InitHeadTracker();
        }
        else
            CloseHeadTracker();
    }
    else if (key == 'd' || key == 'D')
    {
        // let maximum delta_t be 1.f
        /*if ( (delta_t = delta_t + 0.1f) > 1.f )
            delta_t = 0.1f;*/
    }
    else if (key == 'w' || key == 'W')
    {
        use_wiimote = !use_wiimote;

        if (!use_wiimote)
            disconnect_wiimote();
    }
    else if (key == 'z' || key == 'Z')
    {
        cout << "Height: " << p_camera->position().z() << endl;
    }
    else if (key == 'r' || key == 'R')
    {
        SelectOption( RENDER_SCENE );
    }

    /*else if (key == 'f' || key == 'F')
        FogEffect(.01);*/
    else if (key == 27)
		exit(0);

    switch (key)//************************************
    {
        case '1':
            FogEffect(20.0);
            break;

        case '2':
            FogEffect(40.0);
            break;

        case '3':
            FogEffect(60.0);
            break;

        case '4':
            FogEffect(80.0);
            break;

        case '5':
            FogEffect(100.0);
            break;

        case '6':
            FogEffect(120.0);
            break;

        case '7':
            FogEffect(500.0);
            break;

        /*case 'r':            // Toggle grid

        case 'R':
            showgrid = !showgrid;
            break;*/
    }
}


void IGlut::Mouse(int button, int state, int x, int y)
{
	last_x = x;
	last_y = y;

	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		Buttons[0] = (int)(state == GLUT_DOWN);

        UpdateUserPositionByMouse(x, y);

        break;

	case GLUT_MIDDLE_BUTTON:
		Buttons[1] = (int)(state == GLUT_DOWN);
		break;

	case GLUT_RIGHT_BUTTON:
		Buttons[2] = (int)(state == GLUT_DOWN);

		//cam_pos.z = user_height + (y-px_win_width*0.5);
        p_camera->position().setZ( cm_user_height + (y-px_win_width*0.5)*2 );

		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void IGlut::Reshape(int w, int h)
{
	// prevent divide by 0 error when minimized
	if (w==0)
		h = 1;

	px_win_width = w;

	px_win_height = h;

	/*glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)w/h,0.1,100);
	//glFrustum(-.20, .20, .1, .4, 0.15, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/
}

void IGlut::CreateScene(string VRMLfile)
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

	//*p_scene += new_obj1;
	*p_scene += new_obj2;
    *p_scene += new_obj3;
	*p_scene += new_obj4;
	*p_scene += new_obj5;
	*p_scene += new_obj6;*/

    VrmlDevice vrml_dev;

    vrml_dev.loadScene(VRMLfile, p_scene);

    // Add GL lights to the Scene;
    Point3 l_pos( gl_light_position[0], gl_light_position[2], gl_light_position[1] );
    Vector3 l_dir( -gl_light_position[0], -gl_light_position[2], -gl_light_position[1] );

    p_light = new PointLight( l_pos, l_dir );

    if ( p_scene->lights().empty() )
        p_scene->lights().push_back( p_light );
    else
        p_scene->lights()[0] = p_light;

    // cout << "OBJS:" << p_scene->objects().size() << endl;

    for (int i = 0; i<p_scene->objects().size(); i++)
    {
        GfxObject* gobj = p_scene->objects()[i];
        /*if (gobj->getChildList().size() == 0)
        {
            Transformation xf;
            xf.rotate(1, 0, 0, 90);
            gobj->setPublicTransform( &xf );
        }*/
    }

    return;

    /// skip this part;
    if (p_scene->cameras().size() != 0)
    {
        // blender setup
        p_camera = p_scene->cameras()[0];
        cout << "CFR: " << p_camera->position().x() << " * " << p_camera->position().y() << " * " << p_camera->position().z() << endl;
        cout << "CTO: " << p_camera->atPoint().x() << " * " << p_camera->atPoint().y() << " * " << p_camera->atPoint().z() << endl;
        cout << "CUP: " << p_camera->upVector().x() << " * " << p_camera->upVector().y() << " * " << p_camera->upVector().z() << endl;

        cout << "OBJ::" << p_scene->objects()[0]->getName() << endl;
    }
    else
    {
        p_camera = new Camera();
        // serhat's setup:
        // cmr_->setPosition(Point3(30,30,10));
        // cmr_->setAtPoint(Point3(0,0,0));
        // cmr_->setUpVector(Vector3(-0.5,-0.5,6).normalize());

        // basar's manual setup: for chapel.wrl
        //p_camera->setPosition( Point3(0, 5, 5) );
        p_camera->setAtPoint( Point3(0, 0, 0) );
        p_camera->setUpVector( Vector3(0, 1, 0).normalize() );
    }


    //	vrml_dev.saveToFile("output.wrl", p_scene);
}

void IGlut::Timer(int timer_id)
{
    if (use_wiimote)
        update_scene_by_wiimote( p_scene, last_x, last_y );

    if (use_camera && p_htc != NULL)
    {
        try
        {
            if ( online_mode ) // network client mode
                p_htc->read_online();
            else
                p_htc->read_offline();

            UpdateUserPositionByTracking();
        }
        catch (runtime_error e)
        {
            cout << e.what() << endl;
            CloseHeadTracker();
            return;
        }
    }

    if ( glutGetWindow())
	{
	    glutPostRedisplay(); // triggers a display event
        glutSwapBuffers();
	}

    glutTimerFunc(20, Timer, 0);
}

void IGlut::Display(void)
{
    //usleep(25000);

    glDrawBuffer(GL_BACK_LEFT);
    DrawToOneBuffer(half_eye_sep_x, half_eye_sep_y);

	glDrawBuffer(GL_BACK_RIGHT);
    DrawToOneBuffer(-half_eye_sep_x, -half_eye_sep_y);
}

void IGlut::DrawBaseGrid()
{
    glDisable(GL_LIGHTING);

    float grid_step = 0.1;
    int half_win_w = 1, //cm_win_width * .5f,
        half_win_h = 1; // cm_win_height * .5f,
    float half_user_h = 0.5; //grid_step * 2;

    half_win_h = ((float)half_win_h / grid_step) * grid_step;
    half_win_w = ((float)half_win_w / grid_step) * grid_step;

    glLineWidth(2);


    /*glBegin(GL_QUADS);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-grid_step, -grid_step, 0);
        glColor3f(0.f, 0.5f, 0.f);
        glVertex3f(grid_step, -grid_step, 0);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(grid_step, grid_step, 0);
        glVertex3f(-grid_step, grid_step, 0);
    glEnd();*/

    glBegin(GL_LINES);
    for(float i=-half_win_w; i<=half_win_w; i+=grid_step)
        for(float j=-half_win_h; j<=half_win_h; j+=grid_step)
            for(float k=half_user_h; k<=half_user_h; k+=grid_step)
            {
                glVertex3f(i, -half_win_h, k);
                glVertex3f(i, half_win_h, k);

                glVertex3f(-half_win_w, j, k);
                glVertex3f(half_win_w, j, k);

                glVertex3f(i, j, 0);
                glVertex3f(i, j, half_user_h);
            }

    glEnd();
    glEnable(GL_LIGHTING);
}

/*void IGlut::DrawScene()
{
    DrawBaseGrid();

    /*float mult=0.5;
	for(float y=-*mult;y<=500*mult;y+=200*mult)
        for(float x=-700*mult;x<=700*mult;x+=200*mult)
        {
            glPushMatrix();

            // düzlemin üstüne koy
            glTranslatef(x, y, 0);

            // küpleri çiz
            glutSolidCube(50.0*mult);

            glPopMatrix();
        }*\

    glPushMatrix();

    glColor3f(0.7f, 1.f, 1.f);

    glRotatef(obj_rot.pitch + 90, 1, 0, 0);
    glRotatef(obj_rot.roll, 0, 1, 0);

    glTranslatef(obj_pos.x, obj_pos.y, obj_pos.z);

    glPopMatrix();
}*/
float z_h = 10;

void IGlut::DrawToOneBuffer(float cm_camera_tilt_x, float cm_camera_tilt_y)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float frusLeft, frusRight, frusBottom, frusTop, frusNear, frusFar,
          t = 0.1; // frustum scaling parameter

/*  glViewport(0, win_h/2, win_w, win_h/2);

    glScissor(0, win_h/2, win_w, win_h/2); */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    frusLeft = ( - p_camera->position().x()
                 - cm_win_width * .5
                 - cm_camera_tilt_x ) * t;

    frusRight = (- p_camera->position().x()
                 + cm_win_width * .5
                 - cm_camera_tilt_x ) * t;

    frusBottom = (- p_camera->position().y()
                  - cm_win_height * .5
                  - cm_camera_tilt_y ) * t;

    frusTop = ( - p_camera->position().y()
                + cm_win_height * .5
                - cm_camera_tilt_y ) * t;

    /*
    frusBottom = (-(cam_pos.z-cm_win_height * .5) - cm_win_height * .5) * 0.1;
    frusTop = (-(cam_pos.z-cm_win_height * .5) + cm_win_height * .5) * 0.1;
    */

    frusNear = p_camera->position().z() * K;

    frusFar = p_camera->position().z() * 2;

    // rendele
	glFrustum( frusLeft, frusRight, frusBottom, frusTop, frusNear, frusFar);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

    ((PointLight*)p_scene->lights()[0])->position() =
            Point3(gl_light_position[0],
                   gl_light_position[2],
                   gl_light_position[1]);

	// sert bak
	Point3 glEyePos(p_camera->position().x() + cm_camera_tilt_x,
                    p_camera->position().y() + cm_camera_tilt_y,
                    p_camera->position().z() );

    Point3 glCenterPos(p_camera->position().x() + cm_camera_tilt_x,
                       p_camera->position().y() + cm_camera_tilt_y,
                       0.0);

    Vector3 glUpVector(0, 1, 0);

	p_camera->setPosition( glEyePos );
	p_camera->setAtPoint( glCenterPos );
	p_camera->setUpVector( glUpVector );

	/*gluLookAt(cam_pos.x+eye_sep_x, cam_pos.y - cm_win_height * .5 + eye_sep_y, cam_pos.z - cm_win_height * .5,
              cam_pos.x+eye_sep_x, 0.0, cam_pos.z - cm_win_height * .5,
              0, 0, 1);*/

	/// kullanıcı hizasından ekranın olduğu yere taşı
	// glTranslatef(0.0, user_to_screen, 0.0);

	/// obsolete:
	// DrawScene();

    // DrawBaseGrid();

    glTranslatef(0, 0, -z_h);

    if (p_drawer != NULL)
	{
		p_drawer->drawShadedScene(p_scene, p_camera);
	}

    /// Display Wiimote text message if exists
    glColor3f(0.0f, 1.0f, 0.0f);
    renderString(-cm_win_width * 0.5 + 5, -cm_win_height * 0.5 + 5, 0, wii_msg);

	glPopMatrix();

}

void IGlut::UpdateUserPositionByMouse(int mouse_x, int mouse_y)
{
    float user_vector_x = mouse_x - px_win_width* 0.5,
          user_vector_y = px_win_height* 0.5 - mouse_y;

    deg_user_yaw = atan2( user_vector_y, user_vector_x );

    p_camera->setPosition( Point3( user_vector_x * PX_2_CM, // cm_user_to_screen_center * cos(deg_user_yaw);
                                    user_vector_y * PX_2_CM, // cm_user_to_screen_center * sin(deg_user_yaw);
                                    cm_user_height + z_h ) );

    half_eye_sep_x = HALF_EYE_SEP_CM * -sin(deg_user_yaw);
    half_eye_sep_y = HALF_EYE_SEP_CM * cos(deg_user_yaw);

    // cout << cam_pos.z << endl;
}

void IGlut::UpdateUserPositionByTracking()
{
    deg_user_yaw = atan2( p_htc->lookVector.y(), p_htc->lookVector.x() );

    /**
    * DO NOT ASSIGN NEW VALUES DIRECTLY
    * add the difference with a delta
    */
    //cam_pos.x += ( p_htc->headPosition.x - cam_pos.x ) * delta_t;

    //cout << p_htc->lookVector.x() << ", " << p_htc->lookVector.y() << endl;
    /// constant x;
    // p_camera->position().setX( -80 );
    p_camera->position().setX( p_camera->position().x() +
                               ( p_htc->headPosition.x() - p_camera->position().x() ) * delta_t );

    p_camera->position().setY( p_camera->position().y() +
                               ( p_htc->headPosition.y() - p_camera->position().y() ) * delta_t );
    //cam_pos.z += ( p_htc->headPosition.z - cam_pos.z ) * delta_t;

    half_eye_sep_x = HALF_EYE_SEP_CM * sin(deg_user_yaw);
    half_eye_sep_y = HALF_EYE_SEP_CM * -cos(deg_user_yaw);

    //cout << cam_pos.z << endl;
}

void IGlut::FogEffect(float fogkey)
{
    int fogMode[] = {GL_EXP, GL_EXP2, GL_LINEAR};

    int fogfilter = 2;

    float fogColor[4] = {0.0f, 0.0f, 0.0f, 1.f};

    glEnable(GL_FOG);

    glFogi(GL_FOG_MODE, fogMode[fogfilter]);

    glFogfv(GL_FOG_COLOR, fogColor);

    //glFogf(GL_FOG_COORD_SRC, GL_FOG_COORD);

    glFogf(GL_FOG_DENSITY, .1f);

    glFogf(GL_FOG_START, p_camera->position().z()-140);//cam_pos[2]

    glFogf(GL_FOG_END, p_camera->position().z() + fogkey);//* 2 - 8000);

    glHint(GL_FOG_HINT,GL_FASTEST);
}

void IGlut::InitHeadTracker()
{
    try
    {
        p_htc = new HeadTrackerClient(SERVER_IP, online_mode);
    }
    catch (runtime_error e)
    {
        cout << e.what() << endl;
        p_htc = NULL;
    }
}

void IGlut::CloseHeadTracker()
{
    use_camera = false;
    delete p_htc;
    p_htc = NULL;
}
