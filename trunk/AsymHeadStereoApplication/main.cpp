#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "geometry.h"
#include "vrml_io.h"
#include <GL/glut.h>

#define TRUE    1
#define FALSE   0
#define ESC     27
#define PI      3.141592654
#define PI_2    1.570796327

int fullscreen = FALSE;
int stereo = FALSE;
int showgrid = FALSE;
int debug = FALSE;
int stereomode=TRUE;

int user_height = 1300; // kullan�c�n�n ekran d�zlemine g�re y�ksekli�i
int user_height2 = 1300; // kullan�c�n�n ekran d�zlemine g�re y�ksekli�i
int user_to_screen = 900; // kullan�c�n�n ekran merkezine uzakl���
int user_to_screen2 = 0;//904.8360040; // kullan�c�n�n ekran merkezine uzakl���
float K = 0.995; // near clipping coefficient
float user_yaw =  0.0; // kullan�c�n�n ekrana olan a��s�, a�a�� t�klarsan 0 sa�a t�klarsan 90 vs.

float cam_pos[3] = {0, -user_to_screen, user_height};
float cam_pos2[3] = {0, -user_to_screen2, user_height2};

float sw=1024.0;
float sh=768.0;

int wwidth=1024, wheight=768;

double rotateangle = 0.0;

float z=0.0;

Geometry *g;

void display_pane(float, float,float);

void Init (void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_NORMALIZE);

    glEnable(GL_DEPTH_TEST);

    glLineWidth(2.0);

    glDepthFunc(GL_LEQUAL);

    glCullFace(GL_BACK);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

}

void Lighting(void)
{
    GLfloat LightPosition[4]={ 400.0f, 0.0f, 1300.0f, 1.0f };

    GLfloat ambient[4] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat fullambient[4] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat diffuse[4] = { 0.8, 0.8, 0.8, 1.0 };

    GLfloat specular[4] = { 0.4, 0.4, 0.4, 1.0 };

    GLfloat shiny[1] = { 5.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, fullambient);

    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
}

void FogEffect(float fogkey)
{
    int    fogMode[]={GL_EXP,GL_EXP2,GL_LINEAR};

    int fogfilter=2;

    float fogColor[4]={0.0f,0.0f,0.0f,1.0f};

    glEnable(GL_FOG);

    glFogi(GL_FOG_MODE,fogMode[fogfilter]);

    glFogfv(GL_FOG_COLOR,fogColor);

    glFogf(GL_FOG_DENSITY,1.0);

    glFogf(GL_FOG_START, cam_pos[2]);//cam_pos[2]

    glFogf(GL_FOG_END, cam_pos[2]+fogkey);

    glHint(GL_FOG_HINT,GL_FASTEST);
}

void DrawScene(void)
{
    glPushMatrix();

    glRotatef(z, 0.0, 0.0, 1.0);

    //Axis of rotation

    //Rotation about spin axis
    glPushMatrix();//***********************************************************

    if (showgrid)
    {
    // draw grid
    glBegin(GL_LINES);
        for (int j=-2;j<=2;++j)
        {
            for(int i=-2;i<=2;++i)
            {
                   glNormal3f(i*2,j*2,-4);
                   glVertex3f(i*2,j*2,-4);
                   glNormal3f(i*2,j*2,4);
                   glVertex3f(i*2,j*2,4);

                   glNormal3f(4,j*2,i*2);
                   glVertex3f(4,j*2,i*2);
                   glNormal3f(-4,j*2,i*2);
                   glVertex3f(-4,j*2,i*2);

                   glNormal3f(i*2,-4,j*2);
                   glVertex3f(i*2,-4,j*2);
                   glNormal3f(i*2,4,j*2);
                   glVertex3f(i*2,4,j*2);
            }
        }
    glEnd();
    }

    glDisable(GL_CULL_FACE);

    //glRotatef(70.0, 1.0, 0.0, 0.0);

    glBegin(GL_TRIANGLES);

        g->draw();

    glEnd();

    glEnable(GL_CULL_FACE);

    glPopMatrix();//********************************************************************/

    //glutSolidCube(4.0);//********************************************************************

    glPopMatrix();

    //z=z+0.02;
}

void display(void)
{
    float eye_sep_x = 0.3 * cos(user_yaw),
          eye_sep_y = 0.3 * sin(user_yaw),
          eye_sep_z = 0.3 * sin(user_yaw);

        if(stereo)
        {
            glDrawBuffer(GL_BACK_LEFT);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            display_pane(eye_sep_x, eye_sep_y, eye_sep_z);

            glDrawBuffer(GL_BACK_RIGHT);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            display_pane(-eye_sep_x, -eye_sep_y, -eye_sep_z);
        }

        else
        {
            glDrawBuffer(GL_BACK_LEFT);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            display_pane(eye_sep_x, eye_sep_y, eye_sep_z);
        }
}

void display_pane(float eye_sep_x, float eye_sep_y, float eye_sep_z)
{
    double left, right, bottom, top, near, far;

    glViewport(0, sh/2, sw, sh/2);

    glScissor(0, sh/2, sw, sh/2);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    left= (-cam_pos[0]-sw*.0065) * K;//-ratio * wd2 - 2.5 * ndfl;
    right= (-cam_pos[0]+sw*.0065) * K;//ratio * wd2 - 2.5 * ndfl;
    bottom= (-cam_pos[1]+(sh/2)*.0065) * K;//-wd2;
    top= (-cam_pos[1]+2.5*(sh/2)*.0065) * K;//wd2;
    near= user_height * K;
    far= user_height * 20;

    /*left= (-cam_pos2[0]-sw*.0065) * K;//-ratio * wd2 - 2.5 * ndfl;
    right= (-cam_pos2[0]+sw*.0065) * K;//ratio * wd2 - 2.5 * ndfl;
    bottom= (-cam_pos2[1]-(sh/2)*.0065) * K;//-wd2;
    top= (-cam_pos2[1]+(sh/2)*.0065) * K;//wd2;
    near= user_height2 * K;
    far= user_height2 * 20;*/

                // rendele
    glFrustum(left, right, bottom, top, near, far );//

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // sert bak
    gluLookAt(cam_pos[0]-eye_sep_x, cam_pos[1]-eye_sep_y,cam_pos[2]-eye_sep_z,
              cam_pos[0]-eye_sep_x, cam_pos[1]-eye_sep_y, 0.0-eye_sep_z,
              0.0, 1.0, 0.0);

    // sert bak
    /*gluLookAt(cam_pos2[0]-eye_sep_x, cam_pos2[1]-eye_sep_y,cam_pos2[2]-eye_sep_z,
              cam_pos2[0]-eye_sep_x, cam_pos2[1]-eye_sep_y, 0.0-eye_sep_z,
              0.0, 1.0, 0.0);*/

   
    Lighting();

    DrawScene();

    glPopMatrix();

    glViewport(0, 0, sw, sh/2);

    glScissor(0, 0, sw, sh/2);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    left= (-cam_pos[0]-sw*.0065) * K;//-ratio * wd2 - 2.5 * ndfl;
    right= (-cam_pos[0]+sw*.0065) * K;//ratio * wd2 - 2.5 * ndfl;
    bottom= (-cam_pos[1]-(sh/2)*.0065) * K;//-wd2;
    top= (-cam_pos[1]+(sh/2)*.0065) * K;//wd2;
    near= user_height * K;
    far= user_height * 20;

          // rendele
    glFrustum( left, right, bottom, top, near, far);//

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

           // sert bak
    gluLookAt(cam_pos[0]+eye_sep_x, cam_pos[1]+eye_sep_y,cam_pos[2]+eye_sep_z,
              cam_pos[0]+eye_sep_x, cam_pos[1]+eye_sep_y, 0.0+eye_sep_z,
              0.0, 1.0, 1.0);

    Lighting();

    DrawScene();

    glPopMatrix();

    glutPostRedisplay(); /* Inform GLUT to constantly update the screen */

    glutSwapBuffers();
}

void drag(int x, int y)
{
    user_yaw = PI_2 + atan2( -(y-wheight*0.5), (x-wwidth*0.5) ); // *180/PI;2048x768

    cam_pos[0] = user_to_screen * sin(user_yaw);
    cam_pos[1] = -user_to_screen * cos(user_yaw);

    printf("user_yaw = %f\n",user_yaw);

    display();
}

void mouse(int button, int state, int x, int y)
{
    user_yaw = PI_2 + atan2( -(y-wheight*0.5), (x-wwidth*0.5) ); // *180/PI;

    cam_pos[0] = user_to_screen * sin(user_yaw);
    cam_pos[1] = -user_to_screen * cos(user_yaw);

    printf("user_yaw = %f\n",user_yaw);

    display();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ESC:            // Quit

        case 'Q':

        case 'q':
            exit(0);
            break;

        case 'g':            // Toggle grid

        case 'G':
            showgrid = !showgrid;
            break;

        case '1':
            FogEffect(1.0);
            break;

        case '2':
            FogEffect(2.0);
            break;

        case '3':
            FogEffect(3.0);
            break;

        case '4':
            FogEffect(4.0);
            break;

        case '5':
            FogEffect(5.0);
            break;

        case '6':
            FogEffect(6.0);
            break;

        case '7':
            FogEffect(100.0);
            break;
    }
}

void Reshape(int w, int h)
{
    sw = w;

    sh = h;
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        if (strstr(argv[i], "-f") != NULL)
        fullscreen = TRUE;

        if (strstr(argv[i], "-s") != NULL)
        stereo = TRUE;

        if (strstr(argv[i], "-d") != NULL)
        debug = TRUE;

        if (strstr(argv[i], "-g") != NULL)
        showgrid = TRUE;
    }

    glutInit(&argc,argv);

    if (!stereo)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    else
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STEREO);

    glutCreateWindow("Stereo Application");

    glutReshapeWindow(sw, sh);

    if (fullscreen==TRUE)
    {
        glutGameModeString( "1280x1600:16@120" );//1280x800 1024x768 2048x768 2560x800 1024x1536 1280x1600
        glutEnterGameMode();
    }

    Init();

     FogEffect(1.0);

    glutDisplayFunc(display);

    glutReshapeFunc(Reshape);

    glutKeyboardFunc(keyboard);

    glutMouseFunc(mouse);

    glutMotionFunc(drag);



          g = new Geometry("nefertiti.wrl", "Mesh-FACES");

    printf("Size: %d\n", g->faces.size());

    glutMainLoop();

    delete g;

    return 0;
} 