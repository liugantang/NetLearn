//
// Created by liugantang on 2022/2/10.
//

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <commondetermine.h>
#include <errno.h>

extern int errno;
void str_echo(int sockfd)
{
	ssize_t n = 0;

	for (;;)
	{
		char buf[SMALLLINE+1];
		bzero(buf, sizeof buf);
		long wsize = 0;
		n = read(sockfd, &wsize, sizeof wsize);
		if (n != 0 && n != sizeof wsize)
		{
			perror("read fail");
			printf("read fail value:%ld\n", wsize);
		}
		while ((n = read(sockfd, buf, wsize)) > 0 && n > 0)
		{
			char log[MAXLINE];
			snprintf(log, MAXLINE,"read data:%s and left size: %ld\n", buf, wsize);
			fputs(log, stdout);
			wsize -= n;
			char wbuf[n+1];
			strncpy(wbuf, buf, n);
			printf("cpy buf %s\n", wbuf);
			for (int i = 0; i < n; i++)
			{
				if (buf[i]>='a'&&buf[i]<='z')
				{
					wbuf[i] = toupper(buf[i]);
				}
			}

			printf("write str:%s\n", wbuf);

			write(sockfd, wbuf, n);
		}

		if (n < 0 && errno == EINTR)
		{
			continue;
		}
		else if (n < 0)
		{
			perror("read error");
			break;
		}
	}
}

int main(int argc, char * argv[])
{
	int listenfd, connfd;
	struct sockaddr_in servaddr;

	bzero(&servaddr, sizeof servaddr);

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket error");
		exit(1);
	}
	printf("create listen fd success\n");
	servaddr.sin_port = htons(COMMONPORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_family = AF_INET;

	if (bind(listenfd, (SA*)&servaddr, sizeof servaddr) < 0)
	{
		perror("bind error");
		exit(1);
	}

	printf("bind success\n");

	if (listen(listenfd, LISTENQ) < 0)
	{
		perror("listen error\n");
		exit(1);
	}

	printf("listen queue set finished\n");

	for (;;)
	{
		connfd = accept(listenfd, NULL, 0);
		int sid;
		if ((sid = fork())>0)
		{
			close(connfd);
		}
		else if (sid == 0)
		{
			struct sockaddr_in peeraddr;
			socklen_t peerlen = sizeof peeraddr;
			char peername[INET_ADDRSTRLEN];
			getpeername(connfd, (SA*)&peeraddr, &peerlen);
			inet_ntop(AF_INET, &peeraddr.sin_addr, peername, INET_ADDRSTRLEN);
			printf("peer addr name: %s\n", peername);
			printf("peer addr port: %d\n", ntohs(peeraddr.sin_port));

			str_echo(connfd);
			close(connfd);
			close(listenfd);
			exit(0);
		}
	}

	return 0;
}