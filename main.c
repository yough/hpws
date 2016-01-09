//Main Function
//parameters: command line parameters
//return value: status code

#include"common.h"

int main(int argc, char **argv)
{
	int lfd, s, efd;
	struct epoll_event event;
	struct epoll_event *events;

	char path[MAX_LINE];
	int port;
	configuration(&port, path); 

	char port_str[6];
	bzero(port_str, 6);
	snprintf(port_str, 5, "%d", port);
	lfd=create_and_bind(port_str);
	if(lfd==-1) abort();

	s=listen(lfd, SOMAXCONN);
	if(s==-1)
	{
		perror("listen");
		abort();
	}

	efd=epoll_create1(0);
	if(efd==-1)
	{
		perror("epoll_create");
		abort();
	}
	addfd(efd, lfd, false);

	events=(struct epoll_event*)calloc(MAXEVENTS, sizeof(event));

	while(1)
	{
		int n, i;
		n=epoll_wait(efd, events, MAXEVENTS, -1);
		for(i=0; i<n; i++)
		{
			if ((events[i].events&EPOLLERR)||
				(events[i].events&EPOLLHUP)||
				(!(events[i].events&EPOLLIN)))
			{
				/* A error has occured on this fd, or the socket is not 
				 * ready for reading (why were we notified then?) */
				fprintf(stderr, "epoll error\n");
				close(events[i].data.fd);
				continue;
			}
			else if(lfd==events[i].data.fd)
			{
				/* We have a notification on the listening socket,
				 * which means one or more incoming connections. */
				while(1)
				{
					struct sockaddr in_addr;
					socklen_t in_len;
					int infd;
					char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

					in_len=sizeof(in_addr);
					infd=accept(lfd, &in_addr, &in_len);
					if(infd==-1)
					{
						if((errno==EAGAIN)||(errno==EWOULDBLOCK))
						{
							/* We have processed all incoming connections. */
							break;
						}
						else
						{
							perror("accept");
							break;
						}
					}
				
					s=getnameinfo(&in_addr, in_len, hbuf, sizeof(hbuf), sbuf, sizeof(sbuf), NI_NUMERICHOST|NI_NUMERICSERV);

					if(s==0)
					{
						print("Accepted connnection on descriptor %d: (host=%s, port=%s)\n", infd, hbuf, sbuf);
					}

					/* Make the incoming socket non-blocking and 
					 * add it to the list of fds to monitor. */
					addfd(efd, infd, true); 
				}
				continue;
			}
			else
			{
				/* We have data on the fd waiting to be read. Read and display it. 
				 * We must read whatever data is available completely, as we are running 
				 * in edge-triggered mode and won't get a notification again for the same data. */
					pthread_t thread;
					args param;
					param.cfd=events[i].data.fd;
					param.efd=efd;
				//	pthread_create(&thread, NULL, worker, (void*)&param);
				 	worker((void*)&param);
			}	
		}
	}

	free(events);
	close(lfd);
	return EXIT_SUCCESS;
}
