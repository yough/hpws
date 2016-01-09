#include"common.h"

int make_socket_non_blocking(int sfd)
{
	int flags, s;

	//get the file flag
	flags=fcntl(sfd, F_GETFL, 0);
	if(flags==-1)
	{
		perror("fcntl");
		return -1;
	}

	flags|=O_NONBLOCK;
	s=fcntl(sfd, F_SETFL, flags);
	if(s==-1)
	{
		perror("fcntl");
		return -1;
	}

	return 0;
}

int setnonblocking(int fd)
{
	int old_option=fcntl(fd, F_GETFL);
	int new_option=old_option|O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);
	return old_option;
}

void addfd(int epollfd, int fd, bool oneshot)
{
	epoll_event event;
	event.data.fd=fd;
	event.events=EPOLLIN|EPOLLET;
	if(oneshot)
	{
		event.events|=EPOLLONESHOT;
	}
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	setnonblocking(fd);
}

void reset_oneshot(int epollfd, int fd)
{
	epoll_event event;
	event.data.fd=fd;
	event.events=EPOLLIN|EPOLLET|EPOLLONESHOT;
	epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}
