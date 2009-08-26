///-----------------------------------------------------------------------------
///
/// \file	Server.h
/// \author	Ebutalib Agayev & Basar Ugur
/// \brief	Network client implementation, simply expecting to receive "6 float"
///         data
/// \note
///-----------------------------------------------------------------------------

#include "common.h"

#include <stdexcept>
#include <cstring>
#include <errno.h>
#include <iostream>

#include "../HeadTracker/StereoAnalyzer.h"
#include "../HeadTracker/IOpenCV.h"
#include "../HeadTracker/IFiWiCamera.h"

#include "HeadTrackerClient.h"

using std::string;
using std::runtime_error;

static ssize_t my_read(int fd, char *ptr)
{
    static int	read_cnt = 0;
    static char	*read_ptr;
    static char	read_buf[MAXLINE];

    if (read_cnt <= 0) {
    again:
        if ( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
            if (errno == EINTR)
                goto again;
            return -1;
        } else if (read_cnt == 0)
            return 0;
        read_ptr = read_buf;
    }
    read_cnt--;
    *ptr = *read_ptr++;
    return 1;
}

static ssize_t readline(int fd, void *vptr, size_t maxlen)
{
    size_t      n;
    int rc;
    char	c, *ptr;

    ptr = (char *)vptr;
    for (n = 1; n < maxlen; n++) {
        if ( (rc = my_read(fd, &c)) == 1) {
            *ptr++ = c;
            if (c == '\n')
                break;
        } else if (rc == 0) {
            if (n == 1)
                return 0;
            else
                break;
        } else
            return -1;
    }
    *ptr = 0;
    return n;
}

static ssize_t writen(int fd, const void *vptr, size_t n)
{
    size_t		nleft;
    ssize_t		nwritten;
    const char	*ptr;

    ptr = (const char *)vptr;
    nleft = n;
    while (nleft > 0) {
        if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
            if (errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }
        nleft -= nwritten;
        ptr   += nwritten;
    }
    return(n);
}

HeadTrackerClient::HeadTrackerClient(const string& ip, bool online_mode): remote_ip(ip)
{
    headPosition = Point3(0, -30, 250);
    lookVector = Vector3(0, 1, 0);
    coord_trans = new Matrix(M_data);

    if (!online_mode)
    {
        stereo_anl = new StereoAnalyzer(43.0, 640.0, 480.0, 12.0); // actual values

        cam = new IFiWiCamera();
        if (cam->init())
            cv = new IOpenCV( cvSize(cam->vf->size[0], cam->vf->size[1]) );
        else
            cout << "Initialization error." << endl;

        return;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port   = htons(3333);

    if (inet_pton(AF_INET, remote_ip.c_str(), &server_addr.sin_addr) <= 0)
        throw runtime_error("not a valid IP address");

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw runtime_error("failed to create a socket");

    if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        throw runtime_error("failed to connect to remote server");
}

HeadTrackerClient::~HeadTrackerClient()
{
    delete stereo_anl; stereo_anl = NULL;
    delete cam; cam = NULL;
    delete cv; cv = NULL;
    delete coord_trans; coord_trans = NULL;
}

bool HeadTrackerClient::read_online()
{
    ssize_t n;

	/*if (writen(sockfd, "\n", 1) != 1)
        throw runtime_error("failed to write to socket");
      */
    if ((n = readline(sockfd, recvline, MAXLINE)) < 0)
    {
	    printf("[-] Failed to read from socket but.. continuing!\n");
        //throw runtime_error("failed to read from socket");
    }
    else if (n == 0)
        throw runtime_error("[-] Server terminated prematurely");

	if (sscanf(recvline, "%f %f %f %f %f %f", tempo, tempo+1, tempo+2, tempo+3, tempo+4, tempo+5) != 6)
    {
    	printf("[-] Invalid data received from server: %s\n", recvline);
        //throw runtime_error("invalid data received from server");
    }
    else // Valid data!
    {
        headPosition = Point3( tempo[0], tempo[1], tempo[2] );
        lookVector = Vector3( tempo[3], tempo[4], tempo[5] );
        cout << tempo[0] << " " << tempo[1] << " " << tempo[2] << endl;
    }

    return true;
}

bool HeadTrackerClient::read_offline()
{
    // try to capture image
    if (!cam->capture_image() ||
        // pass the pointer to the left & right images to open_cv interface
        !cv->process_images( cam->imageBufRGB + cam->vf->size[0]*cam->vf->size[1]*3,
                             cam->imageBufRGB ) )
    {
        throw runtime_error("[-] OpenCV process exited");
    }

    stereo_anl->findLocationVector(cornersL, cornersR, headPosition, lookVector, *coord_trans);
    lookVector = lookVector.normalize();

    // cout << "HP:" << headPosition.x() << " " << headPosition.y() << " " << headPosition.z() << endl;

    return true;
}
