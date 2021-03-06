#include "common.h"

int create_and_bind(char *port)
{
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int s, sfd;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family=AF_UNSPEC;			/* return IPv4 and IPv6 chocies */
	hints.ai_socktype=SOCK_STREAM; 		/* We want a TCP socket */
	hints.ai_flags=AI_PASSIVE;			/* All interfaces */

	s=getaddrinfo(NULL, port, &hints, &result);
	if(s!=0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		return -1;
	}

	for(rp=result; rp!=NULL; rp=rp->ai_next)
	{
		sfd=socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if(sfd==-1) continue;

		s=bind(sfd, rp->ai_addr, rp->ai_addrlen);
		if(s==0)
		{
			/* We managed to bind successfully. */
			break;
		}
		close(sfd);
	}

	if(rp==NULL)
	{
		fprintf(stderr, "Could not bind\n");
		return -1;
	}

	freeaddrinfo(result);
	return sfd;
}
