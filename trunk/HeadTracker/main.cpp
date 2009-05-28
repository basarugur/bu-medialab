///-----------------------------------------------------------------------------
///
/// \file	main.cpp
/// \author	Basar Ugur
/// \brief	A simple server which applies HeadTracking and serves found
///         coordinate data on network
/// \note
///-----------------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include "StereoAnalyzer.h"

#include "IOpenCV.h"
#include "IFiWiCamera.h"

#include "Server.h"

#define PI 3.141592654
#define PI_HALF 1.570796327

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
* Initializing camera components
*/

void CameraInit()
{
    stereo_anl = new StereoAnalyzer(43.0, 640.0, 480.0, 12.0); // actual values

	cam = new IFiWiCamera();
    if (cam->init())
        IOpenCV* cv = new IOpenCV( cvSize(cam->vf->size[0], cam->vf->size[1]) );
    else
        cout << "Initialization error." << endl;
}

/**
* Initializing network server components
*/
void ServerInit()
{
    srand(time(NULL));

    // Inter-process communication: Named Pipe; create the FIFO
    umask(0);
    mknod(FIFO_FILE, S_IFIFO|0666, 0);

    cout << "Waiting for network client connection..";

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        errx(1, NULL);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(3333);

    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        errx(1, NULL);

    if (listen(listenfd, 10) < 0)
        errx(1, NULL);

    if (signal(SIGCHLD, sig_child) == SIG_ERR)
        errx(1, NULL);

    if ((childpid = fork()) == 0) // create main network server process
    {
        // start process
        network_process();

        exit(EXIT_SUCCESS);
    }
    else if (childpid == -1) // error: can't fork
        errx(1, NULL);

    // accepting client connection for network
    /*clilen = sizeof(cliaddr);
    if ((connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0) {
        //if (errno == EINTR)
        //    continue;
        //else
        //    errx(1, NULL);
        if (errno != EINTR)
            errx(1, NULL);
    }
    else if (close(listenfd) == -1)
        errx(1, NULL);

    cout << " Established!" << endl;*/
}


//-------------------------------------------------------------------------------
///
int main(int argc,char** argv)
{
	CameraInit();

	ServerInit();

    char line[MAXLINE] = "";
    FILE* fptr;

    while (true)
    {
            // try to capture image
        if (!cam->capture_image() ||
            // pass the pointer to the left & right images to open_cv interface
            !cv->process_images( cam->imageBufRGB + cam->vf->size[0]*cam->vf->size[1]*3,
                                 cam->imageBufRGB ) )
        {
            cout << "[-] OpenCV process exited." << endl;
            break;
        }

        stereo_anl->findLocationVector(cornersL, cornersR, headPosition, lookVector, coord_trans_4x4);
        lookVector = Point::normalize(lookVector);

        /*memcpy(serial_data, (void*)(&headPosition), 3*sizeof(float));
        memcpy(serial_data+3, (void*)(&lookVector), 3*sizeof(float));
        printf("Sample [0]: %g\n", serial_data[0]);*/
        sprintf(line,
                "%g %g %g %g %g %g\n",
                headPosition.x, headPosition.y, headPosition.z,
                lookVector.x, lookVector.y, lookVector.z);

        //if (rand()%100 < 20)
        //    printf("line [%d]: %s", strlen(line), line);

        fptr = fopen(FIFO_FILE, "w");
        fwrite_unlocked(line, 1, strlen(line)+1, fptr);
        fclose(fptr);

    }

    if (close(connfd) == -1)
        errx(1, NULL);

	delete stereo_anl; stereo_anl = NULL;
    delete cam; cam = NULL;
    delete cv; cv = NULL;
}
