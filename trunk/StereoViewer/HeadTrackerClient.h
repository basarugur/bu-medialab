///-----------------------------------------------------------------------------
///
/// \file	Server.h
/// \author	Ebutalib Agayev
/// \brief	Network client header, expecting to receive "6 float" data
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

class HeadTrackerClient {
public:
    HeadTrackerClient(const std::string& ip);
    bool read(float *data);
private:
    std::string remote_ip;
    struct sockaddr_in server_addr;
    int sockfd;
};


#endif
