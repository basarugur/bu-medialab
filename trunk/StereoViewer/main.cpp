///-----------------------------------------------------------------------------
///
/// \file	main.cpp
/// \author	Basar Ugur
/// \brief	Moved on from Rob Bateman's simple viewer for GLUT,
///         an enhanced Stereo VRML2.0 viewer
/// \note
///-----------------------------------------------------------------------------

#include <fstream>
#include <stdexcept>
#include "geometry.h"
#include "vrml_io.h"
#include <GL/glut.h>
#include "wiimote.h"

#include "HeadTrackerClient.h"

#define PI 3.141592654
#define PI_HALF 1.570796327

#define HALF_EYE_SEP_CM 3

// GLUT window variables:
bool full_screen = false;

int cm_win_width = 85, cm_win_height = 64,
    px_win_width = 1024, px_win_height = 768;

// kullanıcının ekran düzlemine göre yüksekliği (cm):
int cm_user_height = 70;

// kullanıcının ekran merkezine uzaklığı (cm):
int cm_user_to_screen_center = 70;

// kullanıcının ekrana olan açısı
float deg_user_yaw = 0.0;

// near clipping coefficient:
float K = 0.1;

Rotation world_rot(90, 0, 0), obj_rot, cam_rot;
Point cam_pos(0, -cm_user_to_screen_center, cm_user_height), obj_pos(0.f, 0.f, 0.f);

int last_x = 0;
int last_y = 0;

// glut mouse buttons:
unsigned char Buttons[3] = {0};

// object / world mode switch
bool object_mode = true;

// Delta_t value, for not assigning stereo calibrated data directly
static float delta_t = 1.f;

//int showgrid = 0;//*********************

SceneObject *o1, *o2;
HeadTrackerClient *p_htc;

#define SERVER_IP "79.123.176.157"

static bool use_camera = false;
static bool use_wiimote = false;
static bool offline_mode = true;

/**
* Initializing Head Tracker (+ Network Client) module
*/
void InitHeadTracker()
{
    try
    {
        p_htc = new HeadTrackerClient(SERVER_IP, offline_mode);
    }
    catch (runtime_error e)
    {
        cout << e.what() << endl;
        p_htc = NULL;
    }
}

/**
* Closing Head Tracker module
*/
void CloseHeadTracker()
{
    use_camera = false;
    delete p_htc;
    p_htc = NULL;
}

void InitGlut();

/**
*   OpenGL Fog Effect, added by Ozan Cetinaslan
*/
void FogEffect(float fogkey)
{
    int fogMode[] = {GL_EXP, GL_EXP2, GL_LINEAR};

    int fogfilter = 2;

    float fogColor[4] = {0.0f, 0.0f, 0.0f, 1.f};

    glEnable(GL_FOG);

    glFogi(GL_FOG_MODE, fogMode[fogfilter]);

    glFogfv(GL_FOG_COLOR, fogColor);

    //glFogf(GL_FOG_COORD_SRC, GL_FOG_COORD);

    glFogf(GL_FOG_DENSITY, .1f);

    glFogf(GL_FOG_START, cam_pos.z-140);//cam_pos[2]

    glFogf(GL_FOG_END, cam_pos.z + fogkey);//* 2 - 8000);

    glHint(GL_FOG_HINT,GL_FASTEST);
}

float half_eye_sep_x = 0, half_eye_sep_y = 0, inv_eye_dist = 0;

void display_scene(float, float, float);
void update_user_position_by_mouse(int mouse_x, int mouse_y);
void update_user_position_by_tracking();

float rz1 = 0;

void display(void)
{

    if (use_wiimote)
        update_object_by_wiimote( (object_mode ? &obj_rot : &world_rot),
                                  (object_mode ? &obj_pos : &cam_pos ),
                                   object_mode,
                                   last_x, last_y );

    if (use_camera && p_htc != NULL)
    {
        try
        {
            if ( offline_mode )
                p_htc->read_offline();
            else  // network client mode
                p_htc->read();

            update_user_position_by_tracking();
        }
        catch (runtime_error e)
        {
            cout << e.what() << endl;
            CloseHeadTracker();
            return;
        }
    }

    //usleep(25000);

    glDrawBuffer(GL_BACK_LEFT);
    display_scene(half_eye_sep_x, half_eye_sep_y, rz1);

	glDrawBuffer(GL_BACK_RIGHT);
    display_scene(-half_eye_sep_x, -half_eye_sep_y, rz1);
}

void DrawScene(float rz)//****************************************
{
    glDisable(GL_LIGHTING);
    // draw grid
    int grid_step = 10,
        half_win_w = cm_win_width * .5f,
        half_win_h = cm_win_height * .5f,
        half_user_h = 0; //grid_step * 2;

    half_win_h -= (half_win_h % grid_step);
    half_win_w -= (half_win_w % grid_step);

    glLineWidth(2);

    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    for(int i=-half_win_w; i<=half_win_w; i+=grid_step)
        for(int j=-half_win_h; j<=half_win_h; j+=grid_step)
            for(int k=0; k<=half_user_h; k+=grid_step)
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
        }*/

    glPushMatrix();

    glColor3f(0.7f, 1.f, 1.f);

    glRotatef(rz, 0, 0, 1);

    glRotatef(obj_rot.pitch + 90, 1, 0, 0);
    glRotatef(obj_rot.roll, 0, 1, 0);

    glTranslatef(obj_pos.x, obj_pos.y, obj_pos.z);

    /*if (showgrid)//*********************************************
    {
    // draw grid
    glBegin(GL_LINES);
        for (int j=-half_win_w;j<=half_win_w;j+=2)
        {
            for(int i=-half_win_h;i<=half_win_h;i=+2)
            {
                   glNormal3f(i,j,-half_win_w);
                   glVertex3f(i,j,-half_win_w);
                   glNormal3f(i,j,half_win_w);
                   glVertex3f(i,j,half_win_w);

                   glNormal3f(half_win_w,j,i);
                   glVertex3f(half_win_w,j,i);
                   glNormal3f(-half_win_w,j,i);
                   glVertex3f(-half_win_w,j,i);

                   glNormal3f(i,-half_win_w,j);
                   glVertex3f(i,-half_win_w,j);
                   glNormal3f(i,half_win_w,j);
                   glVertex3f(i,half_win_w,j);
            }
        }
    glEnd();
    }*/

    // sahne nesnelerini çiz
    if (o1 != NULL)
        o1->draw();

    if (o2 != NULL)
        o2->draw();

    glPopMatrix();
}

void display_scene(float cm_camera_tilt_x, float cm_camera_tilt_y, float rz)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float frusLeft, frusRight, frusBottom, frusTop, frusNear, frusFar,
          t = 0.1; // frustum scaling parameter

/*  glViewport(0, win_h/2, win_w, win_h/2);

    glScissor(0, win_h/2, win_w, win_h/2); */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    frusLeft = ( - cam_pos.x
                 - cm_win_width * .5
                 - cm_camera_tilt_x ) * t;

    frusRight = (- cam_pos.x
                 + cm_win_width * .5
                 - cm_camera_tilt_x ) * t;

    frusBottom = (- cam_pos.y
                  - cm_win_height * .5
                  - cm_camera_tilt_y ) * t;

    frusTop = ( - cam_pos.y
                + cm_win_height * .5
                - cm_camera_tilt_y ) * t;

    /*
    frusBottom = (-(cam_pos.z-cm_win_height * .5) - cm_win_height * .5) * 0.1;
    frusTop = (-(cam_pos.z-cm_win_height * .5) + cm_win_height * .5) * 0.1;
    */

    frusNear = cam_pos.z * K;
    frusFar = cam_pos.z * 2;

    // rendele
	glFrustum( frusLeft, frusRight, frusBottom, frusTop, frusNear, frusFar);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// sert bak
	Point glEyePos(cam_pos.x + cm_camera_tilt_x,
                   cam_pos.y + cm_camera_tilt_y,
                   cam_pos.z);

    Point glCenterPos(cam_pos.x + cm_camera_tilt_x,
                      cam_pos.y + cm_camera_tilt_y,
                      0.0);

    Point glUpVector(0, 1, 0);

	gluLookAt(glEyePos.x, glEyePos.y, glEyePos.z,
              glCenterPos.x, glCenterPos.y, glCenterPos.z,
              glUpVector.x, glUpVector.y, glUpVector.z);


    /*gluLookAt(cam_pos.x+eye_sep_x, cam_pos.y - cm_win_height * .5 + eye_sep_y, cam_pos.z - cm_win_height * .5,
              cam_pos.x+eye_sep_x, 0.0, cam_pos.z - cm_win_height * .5,
              0, 0, 1);*/

	// kullanıcı hizasndan ekrann olduğu yere taşı
	// glTranslatef(0.0, user_to_screen, 0.0);

    DrawScene(rz);//****************************************

    // Display text message if exists
    glColor3f(0.0f, 1.0f, 0.0f);
    renderString(-cm_win_width * 0.5 + 5, -cm_win_height * 0.5 + 5, 0, wii_msg);

	glPopMatrix();
/*
	glViewport(0, 0, win_w, win_h/2);

    glScissor(0, 0, win_w, win_h/2);

    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	left= (-cam_pos.x-win_w*.5) * K;
    right= (-cam_pos.x+win_w*.5) * K;
    bottom= (-cam_pos.y-2.0*win_h*.5*.5) * K;
    top= (-cam_pos.y+0.5*win_h*.5*.5) * K;
    near= cam_pos.z * K;
    far= cam_pos.z * 2;

    // rendele
	glFrustum( left, right, bottom, top, near, far);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// sert bak
	gluLookAt(cam_pos.x+eye_sep_x, cam_pos.y+eye_sep_y, cam_pos.z,
              cam_pos.x+eye_sep_x, cam_pos.y+eye_sep_y, 0.0,
              0, 1, 0);

    // kullanýcý hizasýndan ekranýn olduðu yere taþý
	//glTranslatef(0.0, user_to_screen, 0.0);

    DrawScene(rz);//****************************************

	glPopMatrix();
*/
    if (glutGetWindow())
	{
        glutPostRedisplay(); /* Inform GLUT to constantly update the screen */
        glutSwapBuffers();
	}
}


//-------------------------------------------------------------------------------
/// \brief	Called when the screen gets resized
/// \param	w	-	the new width
/// \param	h	-	the new height
///
void reshape(int w, int h)
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

// For simulation purposes: 1024 Pixels = 40 cm
#define PX_2_CM 0.16

void update_user_position_by_mouse(int mouse_x, int mouse_y)
{
    float user_vector_x = mouse_x - px_win_width* 0.5,
          user_vector_y = px_win_height* 0.5 - mouse_y;

    deg_user_yaw = atan2( user_vector_y, user_vector_x );

    cam_pos.x = user_vector_x * PX_2_CM; // cm_user_to_screen_center * cos(deg_user_yaw);
    cam_pos.y = user_vector_y * PX_2_CM; // cm_user_to_screen_center * sin(deg_user_yaw);
    cam_pos.z = cm_user_height;

    half_eye_sep_x = HALF_EYE_SEP_CM * -sin(deg_user_yaw);
    half_eye_sep_y = HALF_EYE_SEP_CM * cos(deg_user_yaw);

    // cout << cam_pos.z << endl;
}

void update_user_position_by_tracking()
{
    deg_user_yaw = atan2( p_htc->lookVector.y, p_htc->lookVector.x );

    /**
    * DO NOT ASSIGN NEW VALUES DIRECTLY
    * add the difference with a delta
    */
    //cam_pos.x += ( p_htc->headPosition.x - cam_pos.x ) * delta_t;
    cam_pos.x = -80;
    cam_pos.y += ( p_htc->headPosition.y - cam_pos.y ) * delta_t;
    //cam_pos.z += ( p_htc->headPosition.z - cam_pos.z ) * delta_t;

    half_eye_sep_x = HALF_EYE_SEP_CM * sin(deg_user_yaw);
    half_eye_sep_y = HALF_EYE_SEP_CM * -cos(deg_user_yaw);

    //cout << cam_pos.z << endl;
}

//-------------------------------------------------------------------------------
//
void Motion(int x, int y)
{
    if (Buttons[0])
        update_user_position_by_mouse(x, y);
    else if (Buttons[2])
    {
        // right click + y movement: affects z
        cam_pos.z = cm_user_height + (y - px_win_width*0.5)*2;
        // cout << cam_pos.z << endl;
    }

	glutPostRedisplay();
}

//-------------------------------------------------------------------------------
//
void Keyboard(unsigned char key, int x, int y)
{
    if (key == 'g' || key == 'G')
    {
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
			InitGlut();
        }
        else
            glutLeaveGameMode();
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
        if ( (delta_t = delta_t + 0.1f) > 1.f )
            delta_t = 0.1f;
    }
    else if (key == 'w' || key == 'W')
    {
        use_wiimote = !use_wiimote;

        if (!use_wiimote)
            disconnect_wiimote();
    }
    else if (key == 'z' || key == 'Z')
    {
        cout << "Height: " << cam_pos.z << endl;
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

//-------------------------------------------------------------------------------
//
void Mouse(int button, int state, int x, int y)
{
	last_x = x;
	last_y = y;

	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		Buttons[0] = (int)(state == GLUT_DOWN);

        update_user_position_by_mouse(x, y);

        break;

	case GLUT_MIDDLE_BUTTON:
		Buttons[1] = (int)(state == GLUT_DOWN);
		break;

	case GLUT_RIGHT_BUTTON:
		Buttons[2] = (int)(state == GLUT_DOWN);

		//cam_pos.z = user_height + (y-px_win_width*0.5);
        cam_pos.z = cm_user_height + (y-px_win_width*0.5)*2;

		break;

	default:
		break;
	}
	glutPostRedisplay();
}

/**
* Registering GLUT related callbacks
*/
void InitGlut()
{
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMotionFunc(Motion);

    // glutFullScreen();
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat LightPosition[]={ 0.0f, 50.0f, 0.0f, 1.0f };
	GLfloat LightIntensity[]={ 0.2f, 0.2f, 0.2f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightIntensity);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightIntensity);
	glClearColor(0.0, 0.0, 0.0, 1.0);//*************************
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_FLAT);
}


//-------------------------------------------------------------------------------
///
int main(int argc,char** argv)
{
    //if (strstr(argv[0], "-r") != NULL)//******************
        //showgrid = 1;//**********************
    //g = new Geometry("bunny.wrl", "Whole_Bunny");
	o1 = new SceneObject("res/chapel_97.wrl","OB_Ground_Ground_M");
	o1->children[0].scale(20, 20, 20);

	//o2  = new SceneObject("res/chapel_97.wrl", "OB_Thumbstone_Chapel");
    o2  = new SceneObject("res/box.wrl", "OB_rsvd_Box");

	/* Write example:
	vrml_io writer;
	writer.write(g, "new.wrl", "New-Name");
	*/

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STEREO);

    glutInitWindowSize(px_win_width, px_win_height);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - px_win_width) * 0.5,
                           (glutGet(GLUT_SCREEN_HEIGHT) - px_win_height) * 0.5 );
    glutCreateWindow("Stereo VRML Viewer | BoUn CmpE Medialab");

    InitGlut();

	//FogEffect(1.0);

	glutMainLoop();

	disconnect_wiimote();

	delete o1; o1 = NULL;
	delete o2; o2 = NULL;

	if (p_htc != NULL)
        CloseHeadTracker();
}
