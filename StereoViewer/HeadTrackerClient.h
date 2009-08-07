///-----------------------------------------------------------------------------
///
/// \file	Server.h
/// \author	Ebutalib Agayev & Basar Ugur
/// \brief	Network client header, simply expecting to receive "6 float" data
/// \note
///-----------------------------------------------------------------------------

#ifndef HTC_DEFINED
#define HTC_DEFINED

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include "geometry.h"

#define MAXLINE 1024

/*
static float M_data[4][4] = { {0.76537,    0.47926,  0.45804, -114.63},
                              {0.57352,   -0.57671, -0.65950,  123.04},
                              {0.0068819,  0.62096, -0.43108,  172.72},
                              {0,          0,        0,        1} }; */

static float M_data[4][4] = { { 0.64148,  -0.60438, -0.64574,  72.029},
                              {-0.67855,  -0.60354, -0.54447,  95.697},
                              {-0.065157,  0.52556, -0.37574,  158.82},
                              { 0,          0,        0,        1} };

class StereoAnalyzer;
class IFiWiCamera;
class IOpenCV;

class HeadTrackerClient
{
public:
    HeadTrackerClient(const std::string& ip, bool offline_mode);
    ~HeadTrackerClient();
    bool read();
    bool read_offline();
    StereoAnalyzer* stereo_anl;
    IFiWiCamera* cam;
    IOpenCV* cv;
    Point headPosition, lookVector; // actual 3D points
    Matrix4x4 *coord_trans_4x4;

private:
    std::string remote_ip;
    struct sockaddr_in server_addr;
    int sockfd;

    // temporary variables in frequently called functions; not to be allocated everytime:
    char recvline[MAXLINE];
    float tempo[6]; // tempo! tempo!
};


#endif
