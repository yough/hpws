#include"common.h"
#include<iostream>

void* worker(void* param)
{
	args *p=(args*) param; int port;
	int cfd=p->cfd; int efd=p->efd;
	char buf[512]; char path[MAX_LINE];
	
	pthread_t tid=pthread_self();
	printf("\nThread ID: %lu, Conn FD: %d, epoll ID: %d\n", tid, cfd, efd);
	close(cfd);
}
