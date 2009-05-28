///-----------------------------------------------------------------------------
///
/// \file	Server.h
/// \author	Ebutalib Agayev & Basar Ugur
/// \brief	Server header containing child process functions
/// \note
///-----------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <err.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include "fcntl.h"

#define MAXLINE 1024
#define FIFO_FILE "COORDATA"

/**
* Network server components
*/
int listenfd, connfd;
pid_t childpid;
socklen_t clilen;
struct sockaddr_in cliaddr, servaddr;
void sig_chld(int);

// static float serial_data[6];

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
    size_t n;
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

static size_t writen(int fd, const void *vptr, size_t n)
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

static void sig_child(int signo)
{
    pid_t pid;
    int	stat;

    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("child %d terminated\n", pid);
    return;
}

/**
* Child process of the server to serve 3D coordinate data to the listening client
*/
void data_process(int sockfd)
{
    ssize_t nbytes;
    char buf[MAXLINE];
    int fil_des; // file descriptor
    FILE* fptr;

    /*if ((n == readline(sockfd, line, MAXLINE)) < 0)
        errx(1, "%s", "failed to read from client");
    else if (n == 0 || strncmp("exit\n", line, MAXLINE) == 0)
        return;*/

    for ( ; ; )
    {
        // Read from named pipe:

        /*fil_des = open(FIFO_FILE, O_NONBLOCK | O_RDONLY);
        nbytes = read(fil_des, buf, MAXLINE);
        close(fil_des);*/

        fptr = fopen(FIFO_FILE, "r");
        fread_unlocked(buf, MAXLINE, 1, fptr);
        nbytes = strlen(buf);

        //printf("Received string: %s of %d bytes\n", buf, nbytes);

        if (writen(sockfd, buf, nbytes) != nbytes)
            errx(1, "%s", "failed to write to client");

        usleep(40000);
    }

}

/**
*   Network process to handle incoming "listening" requests
*/
void network_process()
{
    for ( ; ; )
    {
        clilen = sizeof(cliaddr);
        if ((connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0) {
            if (errno == EINTR)
                continue;
            else
                errx(1, NULL);
        }

        printf("[+] New connection!\n");

        if ((childpid = fork()) == 0) {	// create child process
            if (close(listenfd) == -1)
                errx(1, NULL);

            data_process(connfd);	// process the request

            exit(EXIT_SUCCESS);

        } else if (childpid == -1)
            errx(1, NULL);
        if (close(connfd) == -1)
            errx(1, NULL);
    }
}

/*
int main()
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    void sig_chld(int);

    srand(time(NULL));

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

    for ( ; ; )
    {
        clilen = sizeof(cliaddr);
        if ((connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0) {
            if (errno == EINTR)
                continue;
            else
                errx(1, NULL);
        }

        if ((childpid = fork()) == 0) {	// child process
            if (close(listenfd) == -1)
                errx(1, NULL);
            process(connfd);	// process the request
            exit(0);
        } else if (childpid == -1)
            errx(1, NULL);
        if (close(connfd) == -1)
            errx(1, NULL);
    }
}*/
