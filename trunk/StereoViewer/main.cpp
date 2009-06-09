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

// GLUT window variables:
bool full_screen = false;

int cm_w_width = 85, cm_w_height = 64,
    px_w_width = 1024, px_w_height = 768;
int user_height = 70;       // kullanıcının ekran düzlemine göre yüksekliği
int user_to_screen = 70;    // kullanıcının ekran merkezine uzaklığı
float user_yaw =  0.0;      // kullanıcının ekrana olan açısı: aşağı tıklarsan 0 saa tıklarsan 90 vs.
float K = 0.1;              // near clipping coefficient

Rotation world_r(90, 0, 0), obj_r, cam_r;
Point cam_pos(0, -user_to_screen, user_height), obj_pos(0.f, 0.f, 0.f);

int lastx = 0;
int lasty = 0;
unsigned char Buttons[3] = {0};
bool object_mode = false;
//int showgrid = 0;//*********************

SceneObject *o1, *o2;

HeadTrackerClient *p_htc;

Point headPosition, lookVector; // actual 3D points

float M_data[4][4] = { {0.76537,    0.47926,  0.45804, -114.63},
                       {0.57352,   -0.57671, -0.65950,  123.04},
                       {0.0068819,  0.62096, -0.43108,  162.72},
                       {0,          0,        0,        1} };

Matrix4x4 coord_trans_4x4(M_data);

#define SERVER_IP "79.123.176.157"
static bool use_camera = false;

/**
* Initializing head position and orientation
*/
void InitHead()
{
    headPosition = Point(0, -30, 250);
    lookVector = Point(0, 1, 0);
}

/**
* Initializing Head Tracker (Network-) Client module
*/
void InitHeadTracker()
{
    try
    {
        p_htc = new HeadTrackerClient(SERVER_IP);
    }
    catch (runtime_error e)
    {
        cout << e.what() << endl;
        p_htc = NULL;
    }
}

void InitGlut();

void FogEffect(float fogkey)
{
    int fogMode[]={GL_EXP, GL_EXP2, GL_LINEAR};

    int fogfilter=2;

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

//-------------------------------------------------------------------------------
/// \brief	Draws the scene
///
float eye_sep_x = 0, eye_sep_y = 0, inv_eye_dist = 0;

void display_scene(float, float, float);
void update_user_position(int x, int y);
void update_user_position();

float rz1 = 0, data[6];

void display(void)
{
    /*update_by_wiimote( (object_mode ? &world_r : &obj_r),
                       (object_mode ? &cam_pos : &obj_pos),
                       object_mode,
                       lastx, lasty );*/
    if (use_camera)
    {
        try
        {
            if (p_htc->read(data))
            {
                cout << data[0] << " " << data[1] << " " << data[2] << endl;
                headPosition = Point(data);
                lookVector = Point(data+3);
            }
        }
        catch (runtime_error e)
        {
            cout << e.what() << endl;
        }
        /*  calibration +y <-> opengl +x AND
        *   calibration +x <-> opengl -y
        */
        update_user_position(); //512 - 512 * lookVector.y, 512 - 512 * lookVector.x);
    }

    glDrawBuffer(GL_BACK_LEFT);
    display_scene(eye_sep_x, eye_sep_y, rz1);
	glDrawBuffer(GL_BACK_RIGHT);
	display_scene(-eye_sep_x, -eye_sep_y, rz1);
}

void DrawScene(float rz)//****************************************
{
    glDisable(GL_LIGHTING);
    // draw grid
    int half_w_w = cm_w_width * .5f,
        half_w_h = cm_w_height * .5f,
        grid_step = 5;

    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_LINES);
    for(int i=-half_w_w; i<=half_w_w; i+=grid_step)
    {
        glVertex3f(i, -half_w_h, 0);
        glVertex3f(i, half_w_h, 0);
    }
    for(int j=-half_w_h; j<=half_w_h; j+=grid_step)
    {
        glVertex3f(-half_w_w, j, 0);
        glVertex3f(half_w_w, j, 0);
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

    glRotatef(obj_r.pitch + 90, 1, 0, 0);
    glRotatef(obj_r.roll, 0, -1, 0);

    glTranslatef(obj_pos.x, obj_pos.y, obj_pos.z);

    /*if (showgrid)//*********************************************
    {
    // draw grid
    glBegin(GL_LINES);
        for (int j=-half_w_w;j<=half_w_w;j+=2)
        {
            for(int i=-half_w_h;i<=half_w_h;i=+2)
            {
                   glNormal3f(i,j,-half_w_w);
                   glVertex3f(i,j,-half_w_w);
                   glNormal3f(i,j,half_w_w);
                   glVertex3f(i,j,half_w_w);

                   glNormal3f(half_w_w,j,i);
                   glVertex3f(half_w_w,j,i);
                   glNormal3f(-half_w_w,j,i);
                   glVertex3f(-half_w_w,j,i);

                   glNormal3f(i,-half_w_w,j);
                   glVertex3f(i,-half_w_w,j);
                   glNormal3f(i,half_w_w,j);
                   glVertex3f(i,half_w_w,j);
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

void display_scene(float eye_sep_x, float eye_sep_y, float rz)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	double left, right, bottom, top, near, far;

/*    glViewport(0, w_h/2, w_w, w_h/2);

    glScissor(0, w_h/2, w_w, w_h/2);
*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    left = (-cam_pos.x - cm_w_width * .5) * 0.1;
    right = (-cam_pos.x + cm_w_width * .5) * 0.1;

    bottom = (-cam_pos.y - cm_w_height * .5) * 0.1;
    top = (-cam_pos.y + cm_w_height * .5) * 0.1;

    near = cam_pos.z * K;
    far = cam_pos.z * 2;

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
/*
	glViewport(0, 0, w_w, w_h/2);

    glScissor(0, 0, w_w, w_h/2);

    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	left= (-cam_pos.x-w_w*.5) * K;
    right= (-cam_pos.x+w_w*.5) * K;
    bottom= (-cam_pos.y-2.0*w_h*.5*.5) * K;
    top= (-cam_pos.y+0.5*w_h*.5*.5) * K;
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
	if(w==0)
		h = 1;
	px_w_width = w;
	px_w_height = h;
	/*glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)w/h,0.1,100);
	//glFrustum(-.20, .20, .1, .4, 0.15, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/
}

void update_user_position(int x, int y)
{
    user_yaw = PI_HALF + atan2( -(y - px_w_height*0.5), (x - px_w_width* 0.5) ); // *180/PI;

    cam_pos.x = user_to_screen * sin(user_yaw);
    cam_pos.y = -user_to_screen * cos(user_yaw);

    eye_sep_x = 5 * cos(user_yaw);
    eye_sep_y = 5 * sin(user_yaw);

    //printf("user_yaw = %f\n",user_yaw);
}

#define CM_2_COORD 11.377777778
#define x_offset -45 * CM_2_COORD
#define y_offset -32 * CM_2_COORD

void update_user_position()
{
    user_yaw = PI_HALF + atan2( lookVector.x, lookVector.y ); // *180/PI;

    eye_sep_x = 5 * cos(user_yaw);
    eye_sep_y = 5 * sin(user_yaw);

    // cout << "user_yaw = " << user_yaw << " " << eye_sep_x << " " << eye_sep_y << endl;

    cam_pos.x += ( x_offset + headPosition.y * CM_2_COORD - cam_pos.x ) * delta_tr;
    cam_pos.y += ( y_offset - headPosition.x * CM_2_COORD - cam_pos.y ) * delta_tr;

    cam_pos.z += ( headPosition.z * CM_2_COORD - cam_pos.z ) * delta_tr;
}

//-------------------------------------------------------------------------------
//
void Motion(int x, int y)
{
    if (Buttons[0])
        update_user_position(x, y);
    else if (Buttons[2])
    {
        cam_pos.z = user_height + (y-px_w_width*0.5)*2;
        cout << cam_pos.z << endl;
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
            InitHead();
        else if (p_htc == NULL)
            InitHeadTracker();
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
void Mouse(int b,int s,int x,int y)
{
	lastx = x;
	lasty = y;
	switch(b)
	{
	case GLUT_LEFT_BUTTON:
		Buttons[0] = ((GLUT_DOWN==s)?1:0);

        update_user_position(x, y);

        break;
	case GLUT_MIDDLE_BUTTON:
		Buttons[1] = ((GLUT_DOWN==s)?1:0);

		break;
	case GLUT_RIGHT_BUTTON:
		Buttons[2] = ((GLUT_DOWN==s)?1:0);

		//cam_pos.z = user_height + (y-px_w_width*0.5);
        cam_pos.z = user_height + (y-px_w_width*0.5)*2;

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
	GLfloat LightPosition[]={ 0.0f, 50.0f, 500.0f, 1.0f };
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
	// glShadeModel(GL_FLAT);
}


//-------------------------------------------------------------------------------
///
int main(int argc,char** argv)
{
    //if (strstr(argv[0], "-r") != NULL)//******************
        //showgrid = 1;//**********************
    //g = new Geometry("bunny.wrl", "Whole_Bunny");
	o1 = new SceneObject("res/chapel_97.wrl","OB_Ground_Ground_M");
    //o2  = new SceneObject("res/chapel_97.wrl", "OB_Thumbstone_Chapel");
    o2  = new SceneObject("res/box.wrl", "OB_rsvd_Box");

	/* Write example:
	vrml_io writer;
	writer.write(g, "new.wrl", "New-Name");
	*/

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STEREO);

    glutInitWindowSize(px_w_width, px_w_height);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - px_w_width) * 0.5, (glutGet(GLUT_SCREEN_HEIGHT) - px_w_height) * 0.5 );
    glutCreateWindow("VRML IO Example");

    InitGlut();

    InitHead();

	InitHeadTracker();

	//FogEffect(1.0);

	glutMainLoop();

	// disconnect_wiimote();

	delete o1; o1 = NULL;
	delete o2; o2 = NULL;
}
