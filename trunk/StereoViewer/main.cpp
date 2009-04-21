///-----------------------------------------------------------------------------
///
/// \file	main.cpp
/// \author	Rob Bateman
/// \brief	A simple viewer for a simple file format.
/// \note
///-----------------------------------------------------------------------------

#include <fstream>
#include "StereoAnalyzer.h"
#include "vrml_io.h"
#include <GL/glut.h>
#include "wiimote.h"

#include "IOpenCV.h"
#include "IFiWiCamera.h"

#define PI 3.141592654
#define PI_HALF 1.570796327

// GLUT window variables:
bool full_screen = false;
int w_no;

class Rotation
{
public:
	Rotation(float p = 0.f, float y = 0.f, float r = 0.f) { pitch = p; yaw = y; roll = r; };
	~Rotation() {};

	float pitch, yaw, roll;
};

int w_w = 1024, w_h = 768;
int user_height = 1300;     // kullanıcının ekran düzlemine göre yükseklii
int user_to_screen = 900;   // kullanıcının ekran merkezine uzaklığı
float user_yaw =  0.0;      // kullanıcının ekrana olan açısı: aşağı tıklarsan 0 saa tıklarsan 90 vs.
float K = 0.1;              // near clipping coefficient

Rotation world_r(90, 0, 0), obj_r, cam_r;
Point cam_pos(0, -user_to_screen, user_height), obj_pos(0.f, 0.f, 0.f);

const static float rad2deg = 180.f / PI;
const static float delta_acc = .005f;
const static float delta_tr = .5f;
int lastx = 0;
int lasty = 0;
unsigned char Buttons[3] = {0};
bool object_mode = false;

SceneObject *o1, *o2;
StereoAnalyzer* stereo_anl;
IFiWiCamera* cam;
IOpenCV* cv;

Point headPosition, lookVector; // actual 3D points
float M_data[4][4] = { {0.76537,    0.47926,  0.45804, -114.63},
                       {0.57352,   -0.57671, -0.65950,  123.04},
                       {0.0068819,  0.62096, -0.43108,  162.72},
                       {0,          0,        0,        1} };
Matrix4x4 coord_trans_4x4(M_data);

/**
* Initializing components
*/

void Init()
{
    stereo_anl = new StereoAnalyzer(43.0, 640.0, 480.0, 12.0); // actual values

	cam = new IFiWiCamera();
    if (cam->init())
        IOpenCV* cv = new IOpenCV( cvSize(cam->vf->size[0], cam->vf->size[1]) );
    else
        cout << "Initialization error." << endl;
}

/**
 * Checking wiimote connection and setting up if not exists
 */
void update_by_wiimote()
{
	static double ir_positions[2][2] = { { 0, 0 }, { 0, 0 } };
    static int ir_sizes[2] = { 3, 3 }; /* Expect it to be around 2-8 in wiimote state struct */

    if ( check_wiimote() )
    {
        int diffx, diffy;
		if (lastx > 0) // Valid data
		{
			diffx = g_wii_state.acc[0] - lastx,
			diffy = g_wii_state.acc[2] - lasty;
		}
		else
			diffx = diffy = 0;

		lastx = g_wii_state.acc[0];
		lasty = g_wii_state.acc[2];

		uint8_t leds = 0x00;
		for (int i=0; i < 4; i++)
        {
        	if (g_wii_state.ir_src[i].valid)
	        	leds |= 0x01 * (i+1);

        	//printf("%2d %4d %4d %4d | ", g_wii_state.ir_src[i].valid, g_wii_state.ir_src[i].pos[CWIID_X], g_wii_state.ir_src[i].pos[CWIID_Y], g_wii_state.ir_src[i].size);
            /*
            double x, y;

            if (g_wii_state.ir_src[i].valid)
            {
            	x = g_wii_state.ir_src[i].pos[CWIID_X] * 64 / ((double) CWIID_IR_X_MAX);
                y = 64 - g_wii_state.ir_src[i].pos[CWIID_Y] * 64 / (double) CWIID_IR_Y_MAX;

                ir_positions[i][0] = x;
                ir_positions[i][1] = y;

                if (g_wii_state.ir_src[i].size != -1)
                {
                    ir_sizes[i] = g_wii_state.ir_src[i].size+1;
                }
            }
            else
            {
                x = ir_positions[i][0];
                y = ir_positions[i][1];
            }*/


        }
		//printf(" LEDS: %d\n", leds);

        /* Check if the home button is pressed, then exit */
		if ( g_wii_state.buttons & CWIID_BTN_HOME )
		{
			disconnect_wiimote();
		    exit(EXIT_SUCCESS);
		}

		Point* change = (object_mode ? &cam_pos : &obj_pos);

		if ( g_wii_state.buttons & CWIID_BTN_A && g_wii_state.buttons & CWIID_BTN_B )
			object_mode = !object_mode;
		else if ( g_wii_state.buttons & CWIID_BTN_LEFT )
			change->x -= delta_tr;
		else if ( g_wii_state.buttons & CWIID_BTN_RIGHT )
			change->x += delta_tr;
		else if ( g_wii_state.buttons & CWIID_BTN_UP )
			change->y += delta_tr;
		else if ( g_wii_state.buttons & CWIID_BTN_DOWN )
			change->y -= delta_tr;
		else if ( g_wii_state.buttons & CWIID_BTN_A )
			change->z += delta_tr;
		else if ( g_wii_state.buttons & CWIID_BTN_B )
			change->z -= delta_tr;

        float a_x = ((float)g_wii_state.acc[CWIID_X] - wm_cal.zero[CWIID_X]) /
        	          (wm_cal.one[CWIID_X] - wm_cal.zero[CWIID_X]);
        float a_y = ((float)g_wii_state.acc[CWIID_Y] - wm_cal.zero[CWIID_Y]) /
        	      (wm_cal.one[CWIID_Y] - wm_cal.zero[CWIID_Y]);
        float a_z = ((float)g_wii_state.acc[CWIID_Z] - wm_cal.zero[CWIID_Z]) /
        	      (wm_cal.one[CWIID_Z] - wm_cal.zero[CWIID_Z]);
        //float a = sqrt(pow(a_x,2)+pow(a_y,2)+pow(a_z,2));

		float a_t = atan(a_x/a_z);
		if (a_z == 0.f || cos(a_t) < .000001f)
			return;

        if (a_z <= 0.f)
        	a_t += PI * ((a_x > 0.f) ? 1 : -1);

        a_t *= -1;

		//printf("%d %d %d\n",g_wii_state.acc[CWIID_X] - wm_cal.zero[CWIID_X], g_wii_state.acc[CWIID_Y] - wm_cal.zero[CWIID_Y], g_wii_state.acc[CWIID_Z] - wm_cal.zero[CWIID_Z]);

        Rotation* ch_r = (object_mode ? &world_r : &obj_r);

        ch_r->pitch = ch_r->pitch + (atan(a_y/a_z*cos(a_t)) * rad2deg - ch_r->pitch) * delta_acc;
        ch_r->roll = ch_r->roll + (a_t*rad2deg - ch_r->roll) * delta_acc;

		//printf("accelerator data\n");
		/*for (int i = 0; i < 3; i++)
			printf("%d ", g_wii_state.acc[i]);
		printf("\n");
		if (abs(diffx) > 1 || abs(diffy) > 1)
			printf("%d %d - %d %d - %d %d\n", g_wii_state.acc[0], g_wii_state.acc[2], lastx, lasty, diffx, diffy);

		printf("%d %d - %d %d - %d %d\n", g_wii_state.acc[0], g_wii_state.acc[2], lastx, lasty, diffx, diffy);
		tx += (float) 0.05f * diffx;
		ty -= (float) 0.05f * diffy;
		*/

		return;
	}
}

//-------------------------------------------------------------------------------
/// \brief	Draws the scene
///
float eye_sep_x = 0, eye_sep_y = 0, inv_eye_dist = 0;

void display_scene(float, float, float);
void update_user_position(int x, int y);

float rz1 = 0;

void display(void)
{
    // update_by_wiimote();
    if (cam->capture_image())
    {
        // pass the pointer to the left & right images to open_cv interface
        if (!cv->process_images( cam->imageBufRGB + cam->vf->size[0]*cam->vf->size[1]*3,
                                 cam->imageBufRGB ) )
            cout << "[-] OpenCV process error." << endl;
    }

    stereo_anl->findLocationVector(cornersL, cornersR, headPosition, lookVector, coord_trans_4x4);
    lookVector = Point::normalize(lookVector);
    printf("HP: %01.2f %01.2f %01.2f - LV: %01.2f %01.2f %01.2f\n",
            headPosition.x, headPosition.y, headPosition.z,
            lookVector.x, lookVector.y, lookVector.z);
    /*printf("HP: %01.2f %01.2f - LV: %01.2f %01.2f\n",
            cornersL[0].x, cornersL[0].y,
            cornersR[0].x, cornersR[0].y);*/

    /*  calibration +y <-> opengl +x AND
    *   calibration +x <-> opengl -y
    */
    update_user_position(512 - 512 * lookVector.y, 512 - 512 * lookVector.x);

    glDrawBuffer(GL_BACK_LEFT);
	display_scene(eye_sep_x, eye_sep_y, rz1);
	glDrawBuffer(GL_BACK_RIGHT);
	display_scene(-eye_sep_x, -eye_sep_y, rz1);
}

void display_scene(float eye_sep_x, float eye_sep_y, float rz)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    // rendele
	glFrustum( (-cam_pos.x-w_w*.5) * K, (-cam_pos.x+w_w*.5) * K,
			   (-cam_pos.y-w_h*.5) * K, (-cam_pos.y+w_h*.5) * K,
				user_height * K, user_height * 2);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// sert bak
	gluLookAt(cam_pos.x+eye_sep_x, cam_pos.y+eye_sep_y, cam_pos.z,
              cam_pos.x+eye_sep_x, cam_pos.y+eye_sep_y, 0.0,
              0, 1, 0);

	// kullanýcý hizasýndan ekranýn olduðu yere taþý
	//glTranslatef(0.0, user_to_screen, 0.0);

    glDisable(GL_LIGHTING);
    // draw grid
    int half_w_w = w_w * .5f,
        half_w_h = w_h * .5f,
        grid_step = 64;

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

    // sahne nesnelerini çiz
    if (o1 != NULL)
        o1->draw();

    if (o2 != NULL)
        o2->draw();

    glPopMatrix();


	glPopMatrix();

	glutPostRedisplay(); /* Inform GLUT to constantly update the screen */
	glutSwapBuffers();
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
	w_w = w;
	w_h = h;
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
    user_yaw = PI_HALF + atan2( -(y-w_h*0.5), (x-w_w*0.5) ); // *180/PI;

    cam_pos.x = user_to_screen * sin(user_yaw);
    cam_pos.y = -user_to_screen * cos(user_yaw);

    eye_sep_x = 5 * cos(user_yaw);
    eye_sep_y = 5 * sin(user_yaw);

    //printf("user_yaw = %f\n",user_yaw);
}

//-------------------------------------------------------------------------------
//
void Motion(int x, int y)
{
    if (Buttons[0])
        update_user_position(x, y);
    else if (Buttons[2])
        cam_pos.z = user_height + (y-w_w*0.5);

	glutPostRedisplay();
}

//-------------------------------------------------------------------------------
//
void Keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
		exit(0);
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

		cam_pos.z = user_height + (y-w_w*0.5);

		break;
	default:
		break;
	}
	glutPostRedisplay();
}

//-------------------------------------------------------------------------------
///
int main(int argc,char** argv)
{
    //g = new Geometry("bunny.wrl", "Whole_Bunny");
	o1 = new SceneObject("res/chapel_97.wrl","OB_Ground_Ground_M");
    o2  = new SceneObject("res/chapel_97.wrl", "OB_Thumbstone_Chapel");
	/* Write example:
	vrml_io writer;
	writer.write(g, "new.wrl", "New-Name");
	*/

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STEREO);

    if ( full_screen ) //argc > 2 && strcmp(argv[2], "f") == 0)
    {
        // Enter game mode:
        char mode_string[100];
        sprintf(mode_string, "%dx%d:%d@%d", 1024, 768, 25, 120);
        printf("GLUT-Game-Mode: %s\n", mode_string);
        glutGameModeString( mode_string );
        glutEnterGameMode();
    }
    else
    {
        glutInitWindowSize(w_w, w_h);
        glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - w_w) * 0.5, (glutGet(GLUT_SCREEN_HEIGHT) - w_h) * 0.5 );
        w_no = glutCreateWindow("VRML IO Example");
    }

	//glutFullScreen();
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat LightPosition[]={ 0.0f, 50.0f, 500.0f, 1.0f };
	GLfloat LightIntensity[]={ 0.2f, 0.2f, 0.2f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightIntensity);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightIntensity);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);
	glEnable(GL_COLOR_MATERIAL);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMotionFunc(Motion);

	Init();

	glutMainLoop();

	// disconnect_wiimote();

	delete o1; o1 = NULL;
	delete o2; o2 = NULL;

	delete stereo_anl; stereo_anl = NULL;
    delete cam; cam = NULL;
    delete cv; cv = NULL;
}
