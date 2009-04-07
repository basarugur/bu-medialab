///-----------------------------------------------------------------------------
///
/// \file    main.cpp
/// \author    Rob Bateman
/// \brief    A simple viewer for a simple file format.
/// \note
/// \extra note very much modified by ozzy
///-----------------------------------------------------------------------------

#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "geometry.h"
#include "vrml_io.h"
#include <GL/glut.h>

#define ABS(x) (x < 0 ? -(x) : (x))
#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)
#define TRUE  1
#define FALSE 0
#define ESC 27
#define PI 3.141592653589793238462643
#define DTOR            0.0174532925
#define RTOD            57.2957795
#define CROSSPROD(p1,p2,p3) \
   p3.x = p1.y*p2.z - p1.z*p2.y; \
   p3.y = p1.z*p2.x - p1.x*p2.z; \
   p3.z = p1.x*p2.y - p1.y*p2.x

int fullscreen = FALSE;
int stereo = FALSE;
int showconstruct = FALSE;
int debug = FALSE;
int stereomode=1;

int currentbutton = -1;
double rotatespeed = 0.1;
double dtheta = 3;

double rotateangle = 30.0;

typedef struct {
    double r, g, b;
} COLOUR;

typedef struct {
    double x, y, z;
} XYZ;

typedef struct {
    XYZ vp;            /* View position           */
    XYZ vd;            /* View direction vector   */
    XYZ vu;            /* View up direction       */
    XYZ pr;            /* Point to rotate about   */
    double focallength;        /* Focal Length along vd   */
    double aperture;        /* Camera aperture         */
    double eyesep;        /* Eye separation          */
    int screenwidth, screenheight;
} CAMERA;

CAMERA camera;

XYZ origin = { 0.0, 0.0, 0.0 };

Geometry *g;


//-------------------------------------------------------------------------------
/// \brief    Normalisation Function
///

void Normalise(XYZ * p)
{
    double length;

    length = sqrt(p->x * p->x + p->y * p->y + p->z * p->z);

    if (length != 0)
    {
    p->x /= length;
    p->y /= length;
    p->z /= length;
    }
    else
    {
    p->x = 0;
    p->y = 0;
    p->z = 0;
    }
}

//-------------------------------------------------------------------------------
/// \brief    Initialises the openGL scene
///
void Init(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);	/* Background colour */

    glEnable(GL_DEPTH_TEST);

    glDisable(GL_LINE_SMOOTH);

    glDisable(GL_POINT_SMOOTH);

    glDisable(GL_POLYGON_SMOOTH);

    glDisable(GL_DITHER);

    glEnable(GL_CULL_FACE);

    glEnable(GL_SCISSOR_TEST);

    glLineWidth(2.0);
    glPointSize(1.0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glFrontFace(GL_CCW);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void FogEffect(float fogkey)
{

    int	fogMode[]={GL_EXP,GL_EXP2,GL_LINEAR};

    int fogfilter=2;

    float fogColor[4]={0.0f,0.0f,0.0f,1.0f};

    glEnable(GL_FOG);

    glFogi(GL_FOG_MODE,fogMode[fogfilter]);

    glFogfv(GL_FOG_COLOR,fogColor);

    glFogf(GL_FOG_DENSITY,1.0);

    glFogf(GL_FOG_START, camera.vp.z);

    glFogf(GL_FOG_END, camera.vp.z+fogkey);

    glHint(GL_FOG_HINT,GL_NICEST);
}

//-------------------------------------------------------------------------------
/// \brief    Draws the scene
///

void DrawScene()
{
    COLOUR white = { 1.0, 1.0, 1.0 };

    //Top level rotation  - spin

    glPushMatrix();

    glRotatef(rotateangle, 0.0, 1.0, 0.0);

    //Axis of rotation

    if (showconstruct)
    {
        glColor3f(white.r, white.g, white.b);

        glBegin(GL_LINES);

        glVertex3f(0.0, -60.0, 0.0);

        glVertex3f(0.0, 60.0, 0.0);

        glEnd();
    }
    //Rotation about spin axis
    glPushMatrix();

    glRotatef(50.0, 0.0, 0.0, 1.0);
    //
    if (showconstruct)
    {
        glColor3f(white.r, white.g, white.b);

        glBegin(GL_LINES);
            glVertex3f(0.0, -60.0, 0.0);
            glVertex3f(0.0, 60.0, 0.0);
        glEnd();
    }

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

    glDisable(GL_CULL_FACE);

    glBegin(GL_TRIANGLES);

        g->draw();

    glEnd();

    glEnable(GL_CULL_FACE);

    glPopMatrix();

    glPopMatrix();
}

//-------------------------------------------------------------------------------
/// \brief    Setting Up Lighting Environment
///

void Lighting(void)
{
    GLfloat fullambient[4] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat position[4] = { 3.95327, 0.0, 48.0975, 1.0 }; //{ 40, 0.0, 27, 1.0 }

    GLfloat ambient[4] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat diffuse[4] = { 0.8, 0.8, 0.8, 1.0 };

    GLfloat specular[4] = { 0.4, 0.4, 0.4, 1.0 };

    GLfloat shiny[1] = { 100.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

    //Turn on the appropriate lights

    //glLightfv(GL_LIGHT0, GL_POSITION, position);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, fullambient);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
      //Turn lighting on

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
}

//-------------------------------------------------------------------------------
/// \brief    Initialize Camera Positions
///

void CameraHome(int mode)
{
    camera.aperture = 13;

    camera.focallength = 50;

    camera.eyesep = camera.focallength / 10;

    camera.pr = origin;

    //Special camera position so the beam crosses the viewcd

    camera.vp.x = 3.95327;// 40
    camera.vp.y = 0;
    camera.vp.z = 48.0975;// 27

    camera.vd.x = -camera.vp.x;
    camera.vd.y = -camera.vp.y;
    camera.vd.z = -camera.vp.z;

    camera.vu.x = 0;
    camera.vu.y = 1;
    camera.vu.z = 0;
}

//-------------------------------------------------------------------------------
/// \brief    Rotation of the Camera
///

void RotateCamera(int ix, int iy, int iz)
{
    XYZ vp, vu, vd;

    XYZ right;

    XYZ newvp, newr;

    double radius, dd, radians;

    double dx, dy, dz;

    vu = camera.vu;

    Normalise(&vu);

    vp = camera.vp;
    vd = camera.vd;

    Normalise(&vd);

    CROSSPROD(vd, vu, right);

    Normalise(&right);

    radians = dtheta * PI / 180.0;

    // Handle the roll
    if (iz != 0)
    {
    camera.vu.x += iz * right.x * radians;
    camera.vu.y += iz * right.y * radians;
    camera.vu.z += iz * right.z * radians;

        Normalise(&camera.vu);

        return;
    }

    // Distance from the rotate point
    dx = camera.vp.x - camera.pr.x;
    dy = camera.vp.y - camera.pr.y;
    dz = camera.vp.z - camera.pr.z;

    radius = sqrt(dx * dx + dy * dy + dz * dz);

    // Determine the new view point
    dd = radius * radians;
    newvp.x = vp.x + dd * ix * right.x + dd * iy * vu.x - camera.pr.x;
    newvp.y = vp.y + dd * ix * right.y + dd * iy * vu.y - camera.pr.y;
    newvp.z = vp.z + dd * ix * right.z + dd * iy * vu.z - camera.pr.z;

    Normalise(&newvp);

    camera.vp.x = camera.pr.x + radius * newvp.x;
    camera.vp.y = camera.pr.y + radius * newvp.y;
    camera.vp.z = camera.pr.z + radius * newvp.z;

    // Determine the new right vector
    newr.x = camera.vp.x + right.x - camera.pr.x;
    newr.y = camera.vp.y + right.y - camera.pr.y;
    newr.z = camera.vp.z + right.z - camera.pr.z;

    Normalise(&newr);

    newr.x = camera.pr.x + radius * newr.x - camera.vp.x;
    newr.y = camera.pr.y + radius * newr.y - camera.vp.y;
    newr.z = camera.pr.z + radius * newr.z - camera.vp.z;

    camera.vd.x = camera.pr.x - camera.vp.x;
    camera.vd.y = camera.pr.y - camera.vp.y;
    camera.vd.z = camera.pr.z - camera.vp.z;

    Normalise(&camera.vd);

    // Determine the new up vector
    CROSSPROD(newr, camera.vd, camera.vu);

    Normalise(&camera.vu);

    if (debug)
    fprintf(stderr, "Camera position: (%g,%g,%g)\n", camera.vp.x, camera.vp.y, camera.vp.z);
}

//-------------------------------------------------------------------------------
/// \brief    Translation of the Camera
///

void TranslateCamera(int ix, int iy)
{
    XYZ vp, vu, vd;

    XYZ right;

    XYZ newvp, newr;

    double radians, delta;

    vu = camera.vu;

    Normalise(&vu);

    vp = camera.vp;
    vd = camera.vd;

    Normalise(&vd);

    CROSSPROD(vd, vu, right);

    Normalise(&right);

    radians = dtheta * PI / 180.0;

    delta = dtheta * camera.focallength / 90.0;

    camera.vp.x += iy * vu.x * delta;
    camera.vp.y += iy * vu.y * delta;
    camera.vp.z += iy * vu.z * delta;
    camera.pr.x += iy * vu.x * delta;
    camera.pr.y += iy * vu.y * delta;
    camera.pr.z += iy * vu.z * delta;

    camera.vp.x += ix * right.x * delta;
    camera.vp.y += ix * right.y * delta;
    camera.vp.z += ix * right.z * delta;
    camera.pr.x += ix * right.x * delta;
    camera.pr.y += ix * right.y * delta;
    camera.pr.z += ix * right.z * delta;
}

//-------------------------------------------------------------------------------
/// \brief    Stereo Display Application
///

void Display1(void)
{
    XYZ r;

    double dist, ratio, radians, scale, wd2, ndfl;

    double left, right, top, bottom, near = 0.1, far = 10000;

    //Clip to avoid extreme stereo
        if (stereo)
            near = camera.focallength / 5;

        // Misc stuff
        ratio = camera.screenwidth / (double) camera.screenheight/2;

        radians = DTOR * camera.aperture / 2;

        wd2 = near * tan(radians);

        ndfl = near / camera.focallength;

        if (stereo)
        {
            //Derive the two eye positions
            CROSSPROD(camera.vd, camera.vu, r);

            Normalise(&r);

            r.x *= camera.eyesep / 2.0;
            r.y *= camera.eyesep / 2.0;
            r.z *= camera.eyesep / 2.0;



            for(int g=0; g<2; g++)
            {
                if (g==0)
                {
                    glViewport(0, 0, camera.screenwidth/2, camera.screenheight);

                    glScissor(0, 0, camera.screenwidth/2, camera.screenheight);

                    glMatrixMode(GL_PROJECTION);

                    glLoadIdentity();

                    left = -ratio * wd2 - 0.5 * camera.eyesep * ndfl;
                    right = ratio * wd2 - 0.5 * camera.eyesep * ndfl;
                    top = wd2;
                    bottom = -wd2;

                    glFrustum(left, right, bottom, top, near, far);

                    glMatrixMode(GL_MODELVIEW);

                    glPushMatrix();

                    glDrawBuffer(GL_BACK_RIGHT);

                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    //glLoadIdentity();

                    gluLookAt(camera.vp.x + r.x, camera.vp.y + r.y, camera.vp.z + r.z, camera.vp.x + r.x + camera.vd.x, camera.vp.y + r.y + camera.vd.y, camera.vp.z + r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

                    Lighting();

                    DrawScene();

                    glPopMatrix();

                    glMatrixMode(GL_PROJECTION);

                    glLoadIdentity();

                    left = -ratio * wd2 + 0.5 * camera.eyesep * ndfl;
                    right = ratio * wd2 + 0.5 * camera.eyesep * ndfl;
                    top = wd2;
                    bottom = -wd2;

                    glFrustum(left, right, bottom, top, near, far);

                    glMatrixMode(GL_MODELVIEW);

                    glPushMatrix();

                    glDrawBuffer(GL_BACK_LEFT);

                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    //glLoadIdentity();

                    gluLookAt(camera.vp.x - r.x, camera.vp.y - r.y, camera.vp.z - r.z, camera.vp.x - r.x + camera.vd.x, camera.vp.y - r.y + camera.vd.y, camera.vp.z - r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

                    Lighting();

                    DrawScene();
                    
                    glPopMatrix();
                }
            // goruntunun diger taraftada gosterilmesi///////////////////////////////////////////

                if (g==1)
                {
                    glViewport(camera.screenwidth/2, 0, camera.screenwidth/2, camera.screenheight);

                    glScissor(camera.screenwidth/2, 0, camera.screenwidth/2, camera.screenheight);

                    glMatrixMode(GL_PROJECTION);

                    glLoadIdentity();

                    left = -ratio * wd2 - 0.5 * camera.eyesep * ndfl;
                    right = ratio * wd2 - 0.5 * camera.eyesep * ndfl;
                    top = wd2;
                    bottom = -wd2;

                    glFrustum(left, right, bottom, top, near, far);

                    glMatrixMode(GL_MODELVIEW);

                    glPushMatrix();

                    glDrawBuffer(GL_BACK_RIGHT);

                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    //glLoadIdentity();

                    gluLookAt(camera.vp.x + r.x, camera.vp.y + r.y, camera.vp.z + r.z, camera.vp.x + r.x + camera.vd.x, camera.vp.y + r.y + camera.vd.y, camera.vp.z + r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

                    Lighting();

                    DrawScene();

                    glPopMatrix();

                    glMatrixMode(GL_PROJECTION);

                    glLoadIdentity();

                    left = -ratio * wd2 + 0.5 * camera.eyesep * ndfl;
                    right = ratio * wd2 + 0.5 * camera.eyesep * ndfl;
                    top = wd2;
                    bottom = -wd2;

                    glFrustum(left, right, bottom, top, near, far);

                    glMatrixMode(GL_MODELVIEW);

                    glPushMatrix();

                    glDrawBuffer(GL_BACK_LEFT);

                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    //glLoadIdentity();

                    gluLookAt(camera.vp.x - r.x, camera.vp.y - r.y, camera.vp.z - r.z, camera.vp.x - r.x + camera.vd.x, camera.vp.y - r.y + camera.vd.y, camera.vp.z - r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

                    Lighting();

                    DrawScene();

                    glPopMatrix();
                }
            }

        }
        else
        {

            left = -ratio * wd2;
            right = ratio * wd2;
            top = wd2;
            bottom = -wd2;

            //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            for(int g=0; g<=1; g++)
            {

                if (g==0)
                {

                    glViewport(0, 0, camera.screenwidth/2, camera.screenheight);

                    glScissor(0, 0, camera.screenwidth/2, camera.screenheight);

                    glMatrixMode(GL_PROJECTION);

                    glLoadIdentity();

                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    glFrustum(left, right, bottom, top, near, far);

                }

                //goruntunun diger taraftada gosterilmesi//////////////////////////////////////////

                 if (g==1)
                {

                    glViewport(camera.screenwidth/2, 0, camera.screenwidth/2, camera.screenheight);

                    glScissor(camera.screenwidth/2, 0, camera.screenwidth/2, camera.screenheight);

                    glMatrixMode(GL_PROJECTION);

                    glLoadIdentity();

                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    glFrustum(left, right, bottom, top, near, far);
                 }

                 glDrawBuffer(GL_BACK_LEFT);

                 glMatrixMode(GL_MODELVIEW);

                 glPushMatrix();

                 gluLookAt(camera.vp.x, camera.vp.y, camera.vp.z, camera.vp.x + camera.vd.x, camera.vp.y + camera.vd.y, camera.vp.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

                 Lighting();

                 DrawScene();

                 glPopMatrix();                
            }
        }

    //glFlush();
    glutSwapBuffers();

    //Next angle for rotating
    rotateangle += rotatespeed;
}

void Display2(void)
{
    XYZ r;

    double dist, ratio, radians, scale, wd2, ndfl;

    double left, right, top, bottom, near = 0.1, far = 10000;

    //Clip to avoid extreme stereo
        if (stereo)
            near = camera.focallength / 5;

        // Misc stuff
        ratio = camera.screenwidth / (double) camera.screenheight;

        radians = DTOR * camera.aperture / 2;

        wd2 = near * tan(radians);

        ndfl = near / camera.focallength;

        if (stereo)
        {
            //Derive the two eye positions
            CROSSPROD(camera.vd, camera.vu, r);

            Normalise(&r);

            r.x *= camera.eyesep / 2.0;
            r.y *= camera.eyesep / 2.0;
            r.z *= camera.eyesep / 2.0;


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

            left = -ratio * wd2 - 0.5 * camera.eyesep * ndfl;
            right = ratio * wd2 - 0.5 * camera.eyesep * ndfl;
            top = wd2;
            bottom = -wd2;

            glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();

            glRotatef(45,0.0,0.0,1.0);

            glTranslatef(1.4 , 1.4, 0.0);

            glViewport(0, 0, camera.screenwidth, camera.screenheight);

            glDrawBuffer(GL_BACK_RIGHT);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //glLoadIdentity();

            gluLookAt(camera.vp.x + r.x, camera.vp.y + r.y, camera.vp.z + r.z, camera.vp.x + r.x + camera.vd.x, camera.vp.y + r.y + camera.vd.y, camera.vp.z + r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

            Lighting();

            DrawScene();

            glPopMatrix();


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

            left = -ratio * wd2 + 0.5 * camera.eyesep * ndfl;
            right = ratio * wd2 + 0.5 * camera.eyesep * ndfl;
            top = wd2;
            bottom = -wd2;

            glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();

            glRotatef(45,0.0,0.0,1.0);

            glTranslatef(0.0, -1.9, 0.0);

            glViewport(0, 0, camera.screenwidth, camera.screenheight);

            glDrawBuffer(GL_BACK_LEFT);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //glLoadIdentity();

            gluLookAt(camera.vp.x - r.x, camera.vp.y - r.y, camera.vp.z - r.z, camera.vp.x - r.x + camera.vd.x, camera.vp.y - r.y + camera.vd.y, camera.vp.z - r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

            Lighting();

            DrawScene();

            glPopMatrix();


        }
        else
        {


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

            left = -ratio * wd2;
            right = ratio * wd2;
            top = wd2;
            bottom = -wd2;

            glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);


            glPushMatrix();

            glRotatef(45,0.0,0.0,1.0);

            glViewport(0, 0, camera.screenwidth, camera.screenheight);

            glDrawBuffer(GL_BACK_LEFT);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //glLoadIdentity();

            gluLookAt(camera.vp.x, camera.vp.y, camera.vp.z, camera.vp.x + camera.vd.x, camera.vp.y + camera.vd.y, camera.vp.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

            Lighting();

            DrawScene();

            glPopMatrix();

        }

        //glFlush();
        glutSwapBuffers();

        //Next angle for rotating
        rotateangle += rotatespeed;
}

void Display3(void)
{
    XYZ r;

    double dist, ratio, radians, scale, wd2, ndfl;

    double left, right, top, bottom, near = 0.1, far = 10000;

    //Clip to avoid extreme stereo
        if (stereo)
        near = camera.focallength / 5;

        // Misc stuff
        ratio = camera.screenwidth / (double) camera.screenheight;

        radians = DTOR * camera.aperture / 2;

        wd2 = near * tan(radians);

        ndfl = near / camera.focallength;

        if (stereo)
        {
                //Derive the two eye positions
            CROSSPROD(camera.vd, camera.vu, r);

                Normalise(&r);

                r.x *= camera.eyesep / 2.0;
            r.y *= camera.eyesep / 2.0;
            r.z *= camera.eyesep / 2.0;


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

                left = -ratio * wd2 - 0.5 * camera.eyesep * ndfl;
            right = ratio * wd2 - 0.5 * camera.eyesep * ndfl;
            top = wd2;
            bottom = -wd2;

                glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();

                glRotatef(90,0.0,0.0,1.0);

                glTranslatef(2.4 , 2.0, 0.0);

                glViewport(0, 0, camera.screenwidth, camera.screenheight);

                glDrawBuffer(GL_BACK_RIGHT);

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //glLoadIdentity();

                gluLookAt(camera.vp.x + r.x, camera.vp.y + r.y, camera.vp.z + r.z, camera.vp.x + r.x + camera.vd.x, camera.vp.y + r.y + camera.vd.y, camera.vp.z + r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

                Lighting();

                DrawScene();

                glPopMatrix();


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

                left = -ratio * wd2 + 0.5 * camera.eyesep * ndfl;
            right = ratio * wd2 + 0.5 * camera.eyesep * ndfl;
            top = wd2;
            bottom = -wd2;

                glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();

                glRotatef(90,0.0,0.0,1.0);

                glTranslatef(-2.4, -2.6, 0.0);

                glViewport(0, 0, camera.screenwidth, camera.screenheight);

            glDrawBuffer(GL_BACK_LEFT);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //glLoadIdentity();

                gluLookAt(camera.vp.x - r.x, camera.vp.y - r.y, camera.vp.z - r.z, camera.vp.x - r.x + camera.vd.x, camera.vp.y - r.y + camera.vd.y, camera.vp.z - r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

                Lighting();

                DrawScene();

                glPopMatrix();
        }
        else
        {
                glMatrixMode(GL_PROJECTION);

                glLoadIdentity();

                left = -ratio * wd2;
                right = ratio * wd2;
                top = wd2;
                bottom = -wd2;

                glFrustum(left, right, bottom, top, near, far);

                glMatrixMode(GL_MODELVIEW);


                glPushMatrix();

                glRotatef(90,0.0,0.0,1.0);

                glViewport(0, 0, camera.screenwidth, camera.screenheight);

                glDrawBuffer(GL_BACK_LEFT);

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //glLoadIdentity();

                gluLookAt(camera.vp.x, camera.vp.y, camera.vp.z, camera.vp.x + camera.vd.x, camera.vp.y + camera.vd.y, camera.vp.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

                Lighting();

                DrawScene();

                glPopMatrix();

        }

        //glFlush();
        glutSwapBuffers();

        //Next angle for rotating
        rotateangle += rotatespeed;
}

void Display4(void)
{
    XYZ r;

    double dist, ratio, radians, scale, wd2, ndfl;

    double left, right, top, bottom, near = 0.1, far = 10000;

    //Clip to avoid extreme stereo
        if (stereo)
        near = camera.focallength / 5;

        // Misc stuff
        ratio = camera.screenwidth / (double) camera.screenheight;

        radians = DTOR * camera.aperture / 2;

        wd2 = near * tan(radians);

        ndfl = near / camera.focallength;

        if (stereo)
        {
            //Derive the two eye positions
            CROSSPROD(camera.vd, camera.vu, r);

                Normalise(&r);

                r.x *= camera.eyesep / 2.0;
            r.y *= camera.eyesep / 2.0;
            r.z *= camera.eyesep / 2.0;


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

                left = -ratio * wd2 - 0.5 * camera.eyesep * ndfl;
            right = ratio * wd2 - 0.5 * camera.eyesep * ndfl;
            top = wd2;
            bottom = -wd2;

            glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();

            glRotatef(135,0.0,0.0,1.0);

            glTranslatef(4.0 , 1.8, 0.0);

            glViewport(0, 0, camera.screenwidth, camera.screenheight);

            glDrawBuffer(GL_BACK_RIGHT);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //glLoadIdentity();

            gluLookAt(camera.vp.x + r.x, camera.vp.y + r.y, camera.vp.z + r.z, camera.vp.x + r.x + camera.vd.x, camera.vp.y + r.y + camera.vd.y, camera.vp.z + r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

            Lighting();

            DrawScene();

            glPopMatrix();


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

                left = -ratio * wd2 + 0.5 * camera.eyesep * ndfl;
            right = ratio * wd2 + 0.5 * camera.eyesep * ndfl;
            top = wd2;
            bottom = -wd2;

                glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();

            glRotatef(135,0.0,0.0,1.0);

            glTranslatef(-4.0, -1.5, 0.0);

            glViewport(0, 0, camera.screenwidth, camera.screenheight);

            glDrawBuffer(GL_BACK_LEFT);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //glLoadIdentity();

                gluLookAt(camera.vp.x - r.x, camera.vp.y - r.y, camera.vp.z - r.z, camera.vp.x - r.x + camera.vd.x, camera.vp.y - r.y + camera.vd.y, camera.vp.z - r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

                Lighting();

                DrawScene();

                glPopMatrix();


        }
        else
        {


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

            left = -ratio * wd2;
            right = ratio * wd2;
            top = wd2;
            bottom = -wd2;

                glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);


            glPushMatrix();

            glRotatef(135,0.0,0.0,1.0);

            glViewport(0, 0, camera.screenwidth, camera.screenheight);

            glDrawBuffer(GL_BACK_LEFT);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //glLoadIdentity();

            gluLookAt(camera.vp.x, camera.vp.y, camera.vp.z, camera.vp.x + camera.vd.x, camera.vp.y + camera.vd.y, camera.vp.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

            Lighting();

            DrawScene();

            glPopMatrix();
    }

        //glFlush();
        glutSwapBuffers();

        //Next angle for rotating
        rotateangle += rotatespeed;
}

void Display5(void)
{
    XYZ r;

    double dist, ratio, radians, scale, wd2, ndfl;

    double left, right, top, bottom, near = 0.1, far = 10000;

    //Clip to avoid extreme stereo
        if (stereo)
        near = camera.focallength / 5;

        // Misc stuff
        ratio = camera.screenwidth / (double) camera.screenheight;

        radians = DTOR * camera.aperture / 2;

        wd2 = near * tan(radians);

        ndfl = near / camera.focallength;

        if (stereo)
        {
            //Derive the two eye positions
            CROSSPROD(camera.vd, camera.vu, r);

                Normalise(&r);

                r.x *= camera.eyesep / 2.0;
            r.y *= camera.eyesep / 2.0;
            r.z *= camera.eyesep / 2.0;


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

                left = -ratio * wd2 - 0.5 * camera.eyesep * ndfl;
            right = ratio * wd2 - 0.5 * camera.eyesep * ndfl;
            top = wd2;
            bottom = -wd2;

            glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();

                glRotatef(180,0.0,0.0,1.0);

                glTranslatef(3.7 , 0.5, 0.0);

                glViewport(0, 0, camera.screenwidth, camera.screenheight);

            glDrawBuffer(GL_BACK_RIGHT);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //glLoadIdentity();

            gluLookAt(camera.vp.x + r.x, camera.vp.y + r.y, camera.vp.z + r.z, camera.vp.x + r.x + camera.vd.x, camera.vp.y + r.y + camera.vd.y, camera.vp.z + r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

            Lighting();

            DrawScene();

            glPopMatrix();


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

            left = -ratio * wd2 + 0.5 * camera.eyesep * ndfl;
            right = ratio * wd2 + 0.5 * camera.eyesep * ndfl;
            top = wd2;
            bottom = -wd2;

            glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();

                glRotatef(180,0.0,0.0,1.0);

                glTranslatef(-5.7, 0.5, 0.0);

                glViewport(0, 0, camera.screenwidth, camera.screenheight);

            glDrawBuffer(GL_BACK_LEFT);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //glLoadIdentity();

            gluLookAt(camera.vp.x - r.x, camera.vp.y - r.y, camera.vp.z - r.z, camera.vp.x - r.x + camera.vd.x, camera.vp.y - r.y + camera.vd.y, camera.vp.z - r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

            Lighting();

            DrawScene();

            glPopMatrix();
        }
        else
        {
            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

            left = -ratio * wd2;
            right = ratio * wd2;
            top = wd2;
            bottom = -wd2;

                glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);


                glPushMatrix();

                glRotatef(180,0.0,0.0,1.0);

                glViewport(0, 0, camera.screenwidth, camera.screenheight);

                glDrawBuffer(GL_BACK_LEFT);

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //glLoadIdentity();

                gluLookAt(camera.vp.x, camera.vp.y, camera.vp.z, camera.vp.x + camera.vd.x, camera.vp.y + camera.vd.y, camera.vp.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

                Lighting();

                DrawScene();

                glPopMatrix();

        }

        //glFlush();
        glutSwapBuffers();

        //Next angle for rotating
        rotateangle += rotatespeed;
}

void Display6(void)
{
    XYZ r;

    double dist, ratio, radians, scale, wd2, ndfl;

    double left, right, top, bottom, near = 0.1, far = 10000;

    //Clip to avoid extreme stereo
        if (stereo)
        near = camera.focallength / 5;

        // Misc stuff
        ratio = camera.screenwidth / (double) camera.screenheight;

        radians = DTOR * camera.aperture / 2;

        wd2 = near * tan(radians);

        ndfl = near / camera.focallength;

        if (stereo)
        {
                //Derive the two eye positions
            CROSSPROD(camera.vd, camera.vu, r);

                Normalise(&r);

                r.x *= camera.eyesep / 2.0;
            r.y *= camera.eyesep / 2.0;
            r.z *= camera.eyesep / 2.0;


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

                left = -ratio * wd2 - 0.5 * camera.eyesep * ndfl;
            right = ratio * wd2 - 0.5 * camera.eyesep * ndfl;
            top = wd2;
            bottom = -wd2;

                glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();

                glRotatef(225,0.0,0.0,1.0);

                glTranslatef(4.7 , -1.4, 0.0);

                glViewport(0, 0, camera.screenwidth, camera.screenheight);

                glDrawBuffer(GL_BACK_RIGHT);

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //glLoadIdentity();

                gluLookAt(camera.vp.x + r.x, camera.vp.y + r.y, camera.vp.z + r.z, camera.vp.x + r.x + camera.vd.x, camera.vp.y + r.y + camera.vd.y, camera.vp.z + r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

                Lighting();

                DrawScene();

                glPopMatrix();


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

                left = -ratio * wd2 + 0.5 * camera.eyesep * ndfl;
            right = ratio * wd2 + 0.5 * camera.eyesep * ndfl;
            top = wd2;
            bottom = -wd2;

                glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();

                glRotatef(225,0.0,0.0,1.0);

                glTranslatef(-3.4 , 2.0, 0.0);

                glViewport(0, 0, camera.screenwidth, camera.screenheight);

            glDrawBuffer(GL_BACK_LEFT);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //glLoadIdentity();

                gluLookAt(camera.vp.x - r.x, camera.vp.y - r.y, camera.vp.z - r.z, camera.vp.x - r.x + camera.vd.x, camera.vp.y - r.y + camera.vd.y, camera.vp.z - r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

                Lighting();

                DrawScene();

                glPopMatrix();


        }
        else
        {


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

            left = -ratio * wd2;
            right = ratio * wd2;
            top = wd2;
            bottom = -wd2;

                glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);


                glPushMatrix();

                glRotatef(225,0.0,0.0,1.0);

                glViewport(0, 0, camera.screenwidth, camera.screenheight);

                glDrawBuffer(GL_BACK_LEFT);

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //glLoadIdentity();

                gluLookAt(camera.vp.x, camera.vp.y, camera.vp.z, camera.vp.x + camera.vd.x, camera.vp.y + camera.vd.y, camera.vp.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

                Lighting();

                DrawScene();

                glPopMatrix();

        }

        //glFlush();
        glutSwapBuffers();

        //Next angle for rotating
        rotateangle += rotatespeed;
}

void Display7(void)
{
    XYZ r;

    double dist, ratio, radians, scale, wd2, ndfl;

    double left, right, top, bottom, near = 0.1, far = 10000;

    //Clip to avoid extreme stereo
        if (stereo)
        near = camera.focallength / 5;

        // Misc stuff
        ratio = camera.screenwidth / (double) camera.screenheight;

        radians = DTOR * camera.aperture / 2;

        wd2 = near * tan(radians);

        ndfl = near / camera.focallength;

        if (stereo)
        {
                //Derive the two eye positions
            CROSSPROD(camera.vd, camera.vu, r);

                Normalise(&r);

                r.x *= camera.eyesep / 2.0;
            r.y *= camera.eyesep / 2.0;
            r.z *= camera.eyesep / 2.0;


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

                left = -ratio * wd2 - 0.5 * camera.eyesep * ndfl;
            right = ratio * wd2 - 0.5 * camera.eyesep * ndfl;
            top = wd2;
            bottom = -wd2;

                glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();

                glRotatef(270,0.0,0.0,1.0);

                glTranslatef(1.3 , -2.7, 0.0);

                glViewport(0, 0, camera.screenwidth, camera.screenheight);

                glDrawBuffer(GL_BACK_RIGHT);

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //glLoadIdentity();

                gluLookAt(camera.vp.x + r.x, camera.vp.y + r.y, camera.vp.z + r.z, camera.vp.x + r.x + camera.vd.x, camera.vp.y + r.y + camera.vd.y, camera.vp.z + r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

                Lighting();

                DrawScene();

                glPopMatrix();


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

                left = -ratio * wd2 + 0.5 * camera.eyesep * ndfl;
            right = ratio * wd2 + 0.5 * camera.eyesep * ndfl;
            top = wd2;
            bottom = -wd2;

                glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();

                glRotatef(270,0.0,0.0,1.0);

                glTranslatef(-3.4 , 2.0, 0.0);

                glViewport(0, 0, camera.screenwidth, camera.screenheight);

            glDrawBuffer(GL_BACK_LEFT);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //glLoadIdentity();

                gluLookAt(camera.vp.x - r.x, camera.vp.y - r.y, camera.vp.z - r.z, camera.vp.x - r.x + camera.vd.x, camera.vp.y - r.y + camera.vd.y, camera.vp.z - r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

                Lighting();

                DrawScene();

                glPopMatrix();


        }
        else
        {


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

            left = -ratio * wd2;
            right = ratio * wd2;
            top = wd2;
            bottom = -wd2;

                glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);


                glPushMatrix();

                glRotatef(270,0.0,0.0,1.0);

                glViewport(0, 0, camera.screenwidth, camera.screenheight);

                glDrawBuffer(GL_BACK_LEFT);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //glLoadIdentity();

            gluLookAt(camera.vp.x, camera.vp.y, camera.vp.z, camera.vp.x + camera.vd.x, camera.vp.y + camera.vd.y, camera.vp.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

            Lighting();

            DrawScene();

            glPopMatrix();
        }

        //glFlush();
        glutSwapBuffers();

        //Next angle for rotating
        rotateangle += rotatespeed;
}

void Display8(void)
{
    XYZ r;

    double dist, ratio, radians, scale, wd2, ndfl;

    double left, right, top, bottom, near = 0.1, far = 10000;

    //Clip to avoid extreme stereo
        if (stereo)
        near = camera.focallength / 5;

        // Misc stuff
        ratio = camera.screenwidth / (double) camera.screenheight;

        radians = DTOR * camera.aperture / 2;

        wd2 = near * tan(radians);

        ndfl = near / camera.focallength;

        if (stereo)
        {
                //Derive the two eye positions
            CROSSPROD(camera.vd, camera.vu, r);

                Normalise(&r);

                r.x *= camera.eyesep / 2.0;
            r.y *= camera.eyesep / 2.0;
            r.z *= camera.eyesep / 2.0;


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

                left = -ratio * wd2 - 0.5 * camera.eyesep * ndfl;
            right = ratio * wd2 - 0.5 * camera.eyesep * ndfl;
            top = wd2;
            bottom = -wd2;

            glFrustum(left, right, bottom, top, near, far);

        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();

                glRotatef(315,0.0,0.0,1.0);

                glTranslatef(0.0 , -1.6, 0.0);

                glViewport(0, 0, camera.screenwidth, camera.screenheight);

            glDrawBuffer(GL_BACK_RIGHT);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //glLoadIdentity();

            gluLookAt(camera.vp.x + r.x, camera.vp.y + r.y, camera.vp.z + r.z, camera.vp.x + r.x + camera.vd.x, camera.vp.y + r.y + camera.vd.y, camera.vp.z + r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

            Lighting();

            DrawScene();

            glPopMatrix();


            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

                left = -ratio * wd2 + 0.5 * camera.eyesep * ndfl;
            right = ratio * wd2 + 0.5 * camera.eyesep * ndfl;
            top = wd2;
            bottom = -wd2;

                glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();

                glRotatef(315,0.0,0.0,1.0);

                glTranslatef(-1.4 , 1.7, 0.0);

                glViewport(0, 0, camera.screenwidth, camera.screenheight);

            glDrawBuffer(GL_BACK_LEFT);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //glLoadIdentity();

            gluLookAt(camera.vp.x - r.x, camera.vp.y - r.y, camera.vp.z - r.z, camera.vp.x - r.x + camera.vd.x, camera.vp.y - r.y + camera.vd.y, camera.vp.z - r.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

            Lighting();

            DrawScene();

            glPopMatrix();


        }
        else
        {
            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();

            left = -ratio * wd2;
            right = ratio * wd2;
            top = wd2;
            bottom = -wd2;

                glFrustum(left, right, bottom, top, near, far);

            glMatrixMode(GL_MODELVIEW);


                glPushMatrix();

                glRotatef(315,0.0,0.0,1.0);

                glViewport(0, 0, camera.screenwidth, camera.screenheight);

                glDrawBuffer(GL_BACK_LEFT);

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //glLoadIdentity();

                gluLookAt(camera.vp.x, camera.vp.y, camera.vp.z, camera.vp.x + camera.vd.x, camera.vp.y + camera.vd.y, camera.vp.z + camera.vd.z, camera.vu.x, camera.vu.y, camera.vu.z);

                Lighting();

                DrawScene();

                glPopMatrix();
        }

        //glFlush();
        glutSwapBuffers();

        //Next angle for rotating
        rotateangle += rotatespeed;
}

//-------------------------------------------------------------------------------
/// \brief    Settşng Up Keyboard
///

void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ESC:            // Quit

        case 'Q':

        case 'q':
            exit(0);
            break;

        case 'c':            // Toggle constructs

        case 'C':
            showconstruct = !showconstruct;
            break;

        case 'h':            // Go home

        case 'H':
            CameraHome(0);
            break;

        case '[':            // Roll anti clockwise
            RotateCamera(0, 0, -1);
            break;

        case ']':            // Roll clockwise
            RotateCamera(0, 0, 1);
            break;

        case 'i':            // Translate camera up

        case 'I':
            TranslateCamera(0, 1);
            break;

        case 'k':            // Translate camera down

        case 'K':
            TranslateCamera(0, -1);
            break;

        case 'j':            // Translate camera left

        case 'J':
            TranslateCamera(-1, 0);
            break;

        case 'l':            // Translate camera right

        case 'L':
            TranslateCamera(1, 0);
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
            FogEffect(-100.0);
            break;
    }
}

//-------------------------------------------------------------------------------
/// \brief    Settşng Up Extra Keyboard
///

void ExtraKeyboard(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_LEFT:
            RotateCamera(-1, 0, 0);
            break;

        case GLUT_KEY_RIGHT:
            RotateCamera(1, 0, 0);
            break;

        case GLUT_KEY_UP:
            RotateCamera(0, 1, 0);
            break;

        case GLUT_KEY_DOWN:
            RotateCamera(0, -1, 0);
            break;
    }
}

//-------------------------------------------------------------------------------
/// \brief    Setting Up the Mouse
///

void Mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
    if (button == GLUT_LEFT_BUTTON)
        {
        currentbutton = GLUT_LEFT_BUTTON;
    }
        else if (button == GLUT_MIDDLE_BUTTON)
        {
        currentbutton = GLUT_MIDDLE_BUTTON;
    }
    }
}

//-------------------------------------------------------------------------------
/// \brief    Setting Up the Mouse Menu
///

void MainMenu(int whichone)
{
    switch (whichone)
    {
        case 1:
            showconstruct = !showconstruct;
            break;
        case 9:
            exit(0);
            break;
    }
}

//-------------------------------------------------------------------------------
/// \brief    Setting Up the Speed Menu
///

void SpeedMenu(int whichone)
{
    switch (whichone)
    {
        case 1:
            rotatespeed = 0.0;
            break;

        case 2:
            rotatespeed = 0.01;
            break;

        case 3:
            rotatespeed = 0.1;
            break;

        case 4:
            rotatespeed = 0.5;
            break;

        case 5:
            rotatespeed = 0.8;
            break;
    }
}

//-------------------------------------------------------------------------------
/// \brief    Setting Up the Spin Menu
///

void SpinMenu(int whichone)
{
    switch (whichone)
    {
        case 1:
            dtheta = 1;
            break;

        case 2:
            dtheta = 2;
            break;

        case 3:
            dtheta = 3;
            break;

        case 4:
            dtheta = 5;
            break;
    }
}

//-------------------------------------------------------------------------------
/// \brief    Idle
///

void Idle(void)
{
    glutPostRedisplay();
}

//-------------------------------------------------------------------------------
/// \brief    Visibility
///

void Visibility(int visible)
{
    if (visible == GLUT_VISIBLE)
    glutIdleFunc(Idle);
    else
    glutIdleFunc(NULL);
}

//-------------------------------------------------------------------------------
/// \brief    Reshape
///

void Reshape(int w, int h)
{
    //glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    camera.screenwidth = w;

    camera.screenheight = h;
}

//-------------------------------------------------------------------------------
/// \brief    Moving Mouse
///

void MouseMotion(int x, int y)
{
    static int xlast = -1, ylast = -1;

    int dx, dy;

    dx = x - xlast;
    dy = y - ylast;

    if (dx < 0)
    dx = -1;

    else if (dx > 0)
    dx = 1;

    if (dy < 0)
    dy = -1;

    else if (dy > 0)
    dy = 1;

    if (currentbutton == GLUT_LEFT_BUTTON)
    RotateCamera(-dx, dy, 0);

    else if (currentbutton == GLUT_MIDDLE_BUTTON)//
    RotateCamera(0, 0, dx);

    xlast = x;

    ylast = y;
}

void DisplayMode(int stereomode)
{
    switch (stereomode)
    {
        case 1:
            glutDisplayFunc(Display1);
        break;

        case 2:
            glutDisplayFunc(Display2);
        break;

        case 3:
            glutDisplayFunc(Display3);
        break;

        case 4:
            glutDisplayFunc(Display4);
        break;

        case 5:
            glutDisplayFunc(Display5);
        break;

        case 6:
            glutDisplayFunc(Display6);
        break;

        case 7:
            glutDisplayFunc(Display7);
        break;

        case 8:
            glutDisplayFunc(Display8);
        break;
    }
}


//-------------------------------------------------------------------------------
///
int main(int argc,char** argv)
{
    int i;
    int mainmenu, speedmenu, spinmenu, viewanglemenu;

    camera.screenwidth = 1024;
    camera.screenheight = 768;

    /* Parse the command line arguments */
    for (i = 1; i < argc; i++)
    {
        if (strstr(argv[i], "-f") != NULL)
        fullscreen = TRUE;

        if (strstr(argv[i], "-s") != NULL)
        stereo = TRUE;

        if (strstr(argv[i], "-d") != NULL)
        debug = TRUE;

        if (strstr(argv[i], "-c") != NULL)
        showconstruct = TRUE;
    }

    glutInit(&argc,argv);

    if (!stereo)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    else
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STEREO);

    glutCreateWindow("Stereo Application");

    //glutInitWindowSize(800, 600);

    glutReshapeWindow(camera.screenwidth, camera.screenheight);

    if (fullscreen==TRUE)
    {
        glutGameModeString( "1280x800:16@120" );//1280x800 1024x768 2048x768 2560x800
        glutEnterGameMode();
    }

    glEnable(GL_NORMALIZE);

    Init();

    DisplayMode(stereomode);

    glutReshapeFunc(Reshape);

    glutVisibilityFunc(Visibility);

    glutKeyboardFunc(Keyboard);

    glutSpecialFunc(ExtraKeyboard);

    glutMouseFunc(Mouse);

    glutMotionFunc(MouseMotion);

    CameraHome(0);

    FogEffect(1.0);

    //Set up the speed menu
    speedmenu = glutCreateMenu(SpeedMenu);

    glutAddMenuEntry("Stop", 1);
    glutAddMenuEntry("Slow", 2);
    glutAddMenuEntry("Medium", 3);
    glutAddMenuEntry("Fast", 4);
    glutAddMenuEntry("Very fast", 5);

    //Set up the spin menu
    spinmenu = glutCreateMenu(SpinMenu);

    glutAddMenuEntry("1 degree",  1);
    glutAddMenuEntry("2 degrees", 2);
    glutAddMenuEntry("3 degrees", 3);
    glutAddMenuEntry("5 degrees", 4);

    //Set up the view angle menu
    viewanglemenu = glutCreateMenu(DisplayMode);

    glutAddMenuEntry("1. View", 1);
    glutAddMenuEntry("2. View", 2);
    glutAddMenuEntry("3. View", 3);
    glutAddMenuEntry("4. View", 4);
    glutAddMenuEntry("5. View", 5);
    glutAddMenuEntry("6. View", 6);
    glutAddMenuEntry("7. View", 7);
    glutAddMenuEntry("8. View", 8);

    //Set up the main menu
    mainmenu = glutCreateMenu(MainMenu);

    glutAddSubMenu("Rotation", speedmenu);
    glutAddSubMenu("Camera rotation steps", spinmenu);
    glutAddSubMenu("Different View Angles", viewanglemenu);
    glutAddMenuEntry("Toggle construction lines", 1);
    glutAddMenuEntry("Quit", 9);

    glutAttachMenu(GLUT_RIGHT_BUTTON);


    g = new Geometry("nefertiti.wrl", "Mesh-FACES");

    printf("Size: %d\n", g->faces.size());

    glutMainLoop();

    delete g;
}
