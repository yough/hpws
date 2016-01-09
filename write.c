#include "common.h"

int write_page(int cfd, int fd, char * path)
{
	int n;
	char buf[MAX_LINE];

	sprintf(buf, "HTTP/1.1 200 OK\r\n");
	if(write(cfd, buf, strlen(buf))==-1)
	{
		print("1. write: %s\n", strerror(errno)); 
		return -1;
	}

	sprintf(buf, "Content-Type: ");
	if(write(cfd, buf, strlen(buf))==-1)
	{
		print("2. write: %s\n", strerror(errno)); 
		return -1;
	}

	n=strlen(path);
	if(strcasecmp(&path[n-3], "jpg")==0||strcasecmp(&path[n-3], "jpeg")==0)
		if(write(cfd, "image/jpeg", strlen("image/jpeg"))==-1)
		{
			print("3. write: %s\n", strerror(errno)); 
			return -1;
		}
	else if(strcasecmp(&path[n-3], "gif")==0)
		if(write(cfd, "image/gif", strlen("image/gif"))==-1)
		{
			print("4. write: %s\n", strerror(errno)); 
			return -1;
		}
	else if(strcasecmp(&path[n-3], "png")==0)
		if(write(cfd, "image/png", strlen("image/png"))==-1)
		{
			print("5. write: %s\n", strerror(errno)); 
			return -1;
		}
	else
		if(write(cfd, "text/html", strlen("text/html"))==-1)
		{
			print("6. write: %s\n", strerror(errno)); 
			return -1;
		}

	if(write(cfd, "\r\n\r\n", 4)==-1)
	{
		print("7. write: %s\n", strerror(errno)); 
		return -1;
	}

	while((n=read(fd, buf, MAX_LINE))>0)
	{
		
		//printf("n=%d, buf=%s\n", n, buf);
		if(write(cfd, buf, n)==-1)
		{
			print("write: %s, cfd=%d, fd=%d\n", strerror(errno), cfd, fd);
			return -1;
		}
	}

	return 0;
}
