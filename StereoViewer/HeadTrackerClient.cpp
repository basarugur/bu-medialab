///-----------------------------------------------------------------------------
///
/// \file	Server.h
/// \author	Ebutalib Agayev & Basar Ugur
/// \brief	Network client implementation, expecting to receive "6 float" data
/// \note
///-----------------------------------------------------------------------------

#include <stdexcept>
#include <cstring>
#include <string>
#include <errno.h>

#include "HeadTrackerClient.h"

#define MAXLINE 1024

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

HeadTrackerClient::HeadTrackerClient(const string& ip): remote_ip(ip)
{
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

bool HeadTrackerClient::read(float *data)
{
    ssize_t n;
    char recvline[MAXLINE];

	/*if (writen(sockfd, "\n", 1) != 1)
        throw runtime_error("failed to write to socket");
      */
    if ((n = readline(sockfd, recvline, MAXLINE)) < 0)
    {
	    printf("[-] Failed to read from socket but.. continuing!\n");
        //throw runtime_error("failed to read from socket");
    }
    else if (n == 0)
        throw runtime_error("server terminated prematurely");

	if (sscanf(recvline, "%f %f %f %f %f %f", data, data+1, data+2, data+3, data+4, data+5) != 6)
    {
    	printf("[-] Invalid data received from server: %s\n", recvline);
        //throw runtime_error("invalid data received from server");
    }

    return true;
}
