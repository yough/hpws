#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<signal.h>
#include<errno.h>
#include<strings.h>
#include<time.h>
#include<sys/epoll.h>
#include<pthread.h>
#include<stdarg.h>
#include<sys/socket.h>
#include<netdb.h>
#include<fcntl.h>

#define MAXEVENTS 1024
#define MAX_LINE 1024
#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 10

struct args
{
	int cfd;
	int efd;
};

extern int error_page(int sock_fd);
extern int parse(char *buf, char * path);
extern int write_page(int cfd, int fd, char * path);
extern int configuration(int * port, char * path);
extern int log(char *str);
extern void * worker(void *param);
extern void print(const char *fmt, ...);
extern int create_and_bind(char *port);
extern int make_socket_non_blocking(int sfd);
extern int setnonblocking(int fd);
extern void addfd(int epollfd, int fd, bool oneshot);
void reset_oneshot(int epollfd, int fd);
