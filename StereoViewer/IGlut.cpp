#include "common.h"

#include "IGlut.h"
#include "HeadTrackerClient.h"
#include "cv.h"
#include "wiimote.h"
#include "GL/glui.h"

#include <fstream>
#include <stdexcept>

#include "../SceneModeller_API/src/core/gfxobject.h"
#include "../SceneModeller_API/src/core/rectangle.h"
#include "../SceneModeller_API/src/core/cube.h"
#include "../SceneModeller_API/src/core/cylinder.h"

extern char wii_msg[255]; // to use in opengl context

HeadTrackerClient* IGlut::p_htc;

Scene* IGlut::p_scene = NULL;

Camera* IGlut::p_camera = NULL;

CanvasGrid* IGlut::p_grid;

RenderController* IGlut::p_rc;

Light* IGlut::p_light;

Shader* IGlut::p_shader;

GLUI* glui = NULL;
GLUI_FileBrowser* fb;

int IGlut::submenus[1];
GLuint IGlut::textures[1];

using namespace glut_env;

IGlut::IGlut(int argc, char** argv)
{
    full_screen = false;

    cm_win_width = 85;
    cm_win_height = 64;

    px_win_width = PX_WIN_WIDTH;
    px_win_height = PX_WIN_HEIGHT;

    cm_user_height = 70;

    cm_user_to_screen_center = 70;

    deg_user_yaw = 0.0;

    K = 0.5;

    last_x = 0;
    last_y = 0;

    Buttons[0] = 0;
    Buttons[1] = 0;
    Buttons[2] = 0;

    delta_t = 1.f;
    use_stereo_camera = false;
    use_wiimote = false;
    use_shaders = false;
    online_mode = false;

    half_eye_sep_x = 0.f;
    half_eye_sep_y = 0.f;

    p_htc = NULL;

    /// Notice: VRML file should be taken as program argument.
    //CreateScene("res/chapel_97-5.wrl");
    CreateScene("res/boxes.wrl");

    p_grid = new CanvasGrid( XY_GRID );
    p_grid->setAxesDrawn(false);

    p_shader = new Shader();

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
    delete p_grid;
    delete p_rc;
    delete p_light;
    delete p_shader;
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
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	InitTextures();

    p_shader->setShaders();

	glutMainLoop();
}

void IGlut::InitTextures()
{
    glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &textures[0]);

    glBindTexture(GL_TEXTURE_2D, textures[0]);

    glTexImage2D( GL_TEXTURE_2D, 0, 4, PX_WIN_WIDTH, PX_WIN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, frame_buf);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void IGlut::PrepareMenus()
{
    submenus[0] = glutCreateMenu( SelectOption );
    glutAddMenuEntry("Toggle fullscreen view", 0);
    glutAddMenuEntry("Use wiimote", 1);
    glutAddMenuEntry("Render the scene", 2);
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

        case TOGGLE_WIIMOTE:
            use_wiimote = !use_wiimote;

            glutChangeToMenuEntry(2, use_wiimote ? "Disconnect Wiimote" : "Use Wiimote", TOGGLE_WIIMOTE);

            if (!use_wiimote)
                disconnect_wiimote();

            break;

        case RENDER_SCENE:
            if (p_rc == NULL)
                p_rc = new RenderController();

            /// We use asymmetric frustum for off-axis projection in OpenGL;
            /// therefore we have to correct the camera direction for rendering:
            Point3 save_lookAtPoint( p_camera->lookAtPoint() );
            Vector3 save_upVector( p_camera->upVector() );

            p_camera->setLookAtPoint( Point3(0, 0, 0) );
            p_camera->setUpVector( Vector3(0, 0, 1) );

            p_rc->render(p_scene, p_camera);

            p_camera->setLookAtPoint( save_lookAtPoint );
            p_camera->setUpVector( save_upVector );

            break;
    }
}

void IGlut::GLUIControl(int ui_item_id)
{
    switch (ui_item_id)
    {
        case 1:
            char fn[127] = "res/";
            strcat( fn, fb->get_file() );
            CreateScene( fn );
            glui->close();

            glutTimerFunc(20, Timer, 0);
            break;
    }
}

void IGlut::Keyboard(unsigned char key, int x, int y)
{
    if (key == 'f' || key == 'F')
    {
        SelectOption( TOGGLE_FULLSCREEN );
    }
    else if (key == 'o' || key == 'O')
    {

        glui = GLUI_Master.create_glui("Open File..", 0);

        GLUI_Panel *ep = new GLUI_Panel(glui, "", true);

        fb = new GLUI_FileBrowser(ep, "", GLUI_PANEL_EMBOSSED, 1, GLUIControl);
        new GLUI_Button(ep, "Open..", 2, GLUIControl);

        fb->set_w( 320 );
        fb->set_h( 240 );
        fb->fbreaddir( "res/" );

        int main_window = glui->get_glut_window_id();

        glui->set_main_gfx_window(main_window);
    }
    else if (key == 'c' || key == 'C')
    {
        use_stereo_camera = !use_stereo_camera;

        if (use_stereo_camera) // Reinitialize head:
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
        if ( (delta_t = delta_t + 0.1f) > 1.f )
            delta_t = 0.1f;
    }
    else if (key == 'w' || key == 'W')
    {
        SelectOption( TOGGLE_WIIMOTE );
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
	new_obj2->getLocalTransform()->scale(4,6,0.5);
	new_obj2->getLocalTransform()->translate(4,0,6.5);
	new_obj2->getMaterial()->setDiffColor(TRadiance(0,0.5,0));


	GfxObject* new_obj3 = new GfxObject(new Cylinder(),new Material(),new Transformation());
	GfxObject* new_obj4 = new GfxObject(new Cylinder(),new Material(),new Transformation());
	GfxObject* new_obj5 = new GfxObject(new Cylinder(),new Material(),new Transformation());
	GfxObject* new_obj6 = new GfxObject(new Cylinder(),new Material(),new Transformation());

	new_obj3->getMaterial()->setDiffColor(TRadiance(1,0,0));
	new_obj4->getMaterial()->setDiffColor(TRadiance(1,0,0));
	new_obj5->getMaterial()->setDiffColor(TRadiance(1,0,0));
	new_obj6->getMaterial()->setDiffColor(TRadiance(1,0,0));

	// new_obj3->getLocalTransform()->scale(0.25, 0.16666, 2);
	// new_obj3->getLocalTransform()->translate(0.25, 4/3, -13);
    // new_obj4->getLocalTransform()->translate(1,-8,0);
	// new_obj5->getLocalTransform()->translate(-5,-8,0);
	// new_obj6->getLocalTransform()->translate(-5,8,0);

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

	*p_scene += new_obj1;
	*p_scene += new_obj2;
    // *p_scene += new_obj3;
	//*p_scene += new_obj4;
	// *p_scene += new_obj5;
	// *p_scene += new_obj6;

    */

    if (p_scene != NULL)
    {
        delete p_scene;
        delete p_camera;
    }

    p_scene = new Scene();

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

    cout << "OBJS:" << p_scene->objects().size() << endl;

    for (int i = 0; i<p_scene->objects().size(); i++)
    {
        GfxObject* gobj = p_scene->objects()[i];
        cout << "CN: " << gobj->getChildList().size() << endl;
    }

    /// skip this part;
    /*if (p_scene->cameras().size() != 0)
    {
        // blender setup
        p_camera = p_scene->cameras()[0];
        cout << "CFR: " << p_camera->position().x() << " * " << p_camera->position().y() << " * " << p_camera->position().z() << endl;
        cout << "CTO: " << p_camera->lookAtPoint().x() << " * " << p_camera->lookAtPoint().y() << " * " << p_camera->lookAtPoint().z() << endl;
        cout << "CUP: " << p_camera->upVector().x() << " * " << p_camera->upVector().y() << " * " << p_camera->upVector().z() << endl;

        cout << "OBJ::" << p_scene->objects()[0]->getName() << endl;
    }
    else
    {
        p_camera = new Camera();
        // serhat's setup:
        p_camera->setPosition(Point3(30,30,10));
        p_camera->setLookAtPoint(Point3(0,0,0));
        p_camera->setUpVector(Vector3(-0.5,-0.5,6).normalize());

        // basar's manual setup: for chapel.wrl
        //p_camera->setPosition( Point3(0, 5, 5) );
        //p_camera->setLookAtPoint( Point3(0, 0, 0) );
        //p_camera->setUpVector( Vector3(0, 1, 0).normalize() );
    }*/

    p_camera = new Camera( Point3(0, -cm_user_to_screen_center, cm_user_height) );

    //	vrml_dev.saveToFile("output.wrl", p_scene);
}

void IGlut::Timer(int timer_id)
{

    if (use_wiimote)
        update_scene_by_wiimote( p_scene, last_x, last_y );

    if (use_stereo_camera && p_htc != NULL)
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

    if ( glutGetWindow() == 1 )
	{
	    glutPostRedisplay(); // triggers a display event
        glutSwapBuffers();
	}
	else
        glutSetWindow( 1 );

    glutTimerFunc(20, Timer, 0);
}

void IGlut::Display(void)
{

    //usleep(25000);
    glDrawBuffer(GL_BACK_LEFT);
    if (use_shaders)
    {
        glReadBuffer(GL_BACK_LEFT);
        DrawToOneBuffer(half_eye_sep_x, half_eye_sep_y, 1, 2, true);
        DrawTextureWithShader(half_eye_sep_x, half_eye_sep_y);
        DrawToOneBuffer(half_eye_sep_x, half_eye_sep_y, 0.1, 1, false);
    }
    else
        DrawToOneBuffer(half_eye_sep_x, half_eye_sep_y, 0.1, 2, true);

    /*GLenum e;
    while ( (e=glGetError()) != GL_NO_ERROR )
       cout  << "Error " << e << endl;*/

	glDrawBuffer(GL_BACK_RIGHT);
	if (use_shaders)
    {
        glReadBuffer(GL_BACK_RIGHT);
        DrawToOneBuffer(-half_eye_sep_x, -half_eye_sep_y, 1, 2, true);
        DrawTextureWithShader(-half_eye_sep_x, -half_eye_sep_y);
        DrawToOneBuffer(-half_eye_sep_x, -half_eye_sep_y, 0.1, 1, false);
    }
    else
        DrawToOneBuffer(-half_eye_sep_x, -half_eye_sep_y, 0.1, 2, true);
}

void IGlut::CopyFrameBufferToTexture()
{
    /// Get a copy of framebuffer to texture0
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, px_win_width, px_win_height);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void IGlut::DrawTextureWithShader(float cm_camera_tilt_x, float cm_camera_tilt_y)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram( p_shader->sh_prog[BLUR] );

    /// Prepare orthographic 2D projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, px_win_width, 0, px_win_height, 0, 1);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    /// Use texture0 with the last frame buffer
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    /// Parameter for translating orthographic coordinates to perspective projection
    float o2p = 5.f;

    glTranslatef(cm_camera_tilt_x * o2p, cm_camera_tilt_y * o2p, 0.f);

    glNormal3f(0.f, 0.f, 1.f);

    glBegin(GL_QUADS);
        glMultiTexCoord2f(GL_TEXTURE0, 0, 0); glVertex2f( 0.f, 0.f );
        glMultiTexCoord2f(GL_TEXTURE0, 1, 0); glVertex2f( px_win_width, 0.f );
        glMultiTexCoord2f(GL_TEXTURE0, 1, 1); glVertex2f( px_win_width, px_win_height );
        glMultiTexCoord2f(GL_TEXTURE0, 0, 1); glVertex2f( 0.f, px_win_height );
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
}

float z_h = 16;

void IGlut::DrawToOneBuffer(float cm_camera_tilt_x, float cm_camera_tilt_y,
                            float frustum_z_start, float frustum_z_end,
                            bool first_pass)
{
	if (first_pass)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram( p_shader->sh_prog[SAME] );

    /** Here, t is used as both the frustum z direction start (= near clipping),
     *  and scaling parameter for x and y directions
     *  frustum z direction end is "far clipping" parameter
     */

	float frusLeft, frusRight, frusBottom, frusTop, frusNear, frusFar,
          t = frustum_z_start;

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

    frusNear = p_camera->position().z() * frustum_z_start;

    frusFar = p_camera->position().z() * frustum_z_end;

    /// Define the frustum
	glFrustum( frusLeft, frusRight, frusBottom, frusTop, frusNear, frusFar);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

    ((PointLight*)p_scene->lights()[0])->position() =
            Point3(gl_light_position[0],
                   gl_light_position[2],
                   gl_light_position[1]);

	// Assign camera values for gluLookAt
	Point3 glEyePos(p_camera->position().x() + cm_camera_tilt_x,
                    p_camera->position().y() + cm_camera_tilt_y,
                    p_camera->position().z() );

    Point3 glCenterPos(p_camera->position().x() + cm_camera_tilt_x,
                       p_camera->position().y() + cm_camera_tilt_y,
                       0.0);

    Vector3 glUpVector(0, 1, 0);

	p_camera->setPosition( glEyePos );
	p_camera->setLookAtPoint( glCenterPos );
	p_camera->setUpVector( glUpVector );

	glTranslatef(0, 0, -z_h);

    p_scene->draw(p_camera, NULL, SHADED);

    /// Display Wiimote text message if exists
    glColor3f(0.0f, 1.0f, 0.0f);
    renderString(-cm_win_width * 0.5 + 5, -cm_win_height * 0.5 + 5, 0, wii_msg);

	glPopMatrix();

    if (use_shaders && first_pass)
        CopyFrameBufferToTexture();
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
    deg_user_yaw = atan2( p_htc->lookVector->y, p_htc->lookVector->x );

    /**
    * DO NOT ASSIGN NEW VALUES DIRECTLY
    * add the difference with a delta
    */
    //cam_pos.x += ( p_htc->headPosition->x - cam_pos.x ) * delta_t;

    //cout << p_htc->lookVector->x() << ", " << p_htc->lookVector->y() << endl;
    /// constant x;
    // p_camera->position().setX( -80 );
    p_camera->position().setX( p_camera->position().x() +
                               ( p_htc->headPosition->x - p_camera->position().x() ) * delta_t );

    p_camera->position().setY( p_camera->position().y() +
                               ( p_htc->headPosition->y - p_camera->position().y() ) * delta_t );
    //cam_pos.z += ( p_htc->headPosition->z - cam_pos.z ) * delta_t;

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
    use_stereo_camera = false;
    delete p_htc;
    p_htc = NULL;
}
