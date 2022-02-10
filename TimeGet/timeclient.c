#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include "commondetermine.h"

int main(int argc, char* argv[])
{
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if (argc != 2)
	{
		printf("usage: a.out <IPAddress>\n");
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket error");
	}

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(COMMONPORT);

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
	{
		char errMsg[MAXLINE];
		sprintf(errMsg, "inet_pton error for %s", argv[1]);
		perror(errMsg);
	}

	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("connect error");
		exit(1);
	}

	struct sockaddr_in clientaddr;
	socklen_t clientlen = sizeof clientaddr;
	if (getsockname(sockfd, (SA*)&clientaddr, &clientlen) < 0)
	{
		perror("get sock name fail");
		exit(1);
	}

	char sockname[INET_ADDRSTRLEN];
	if (inet_ntop(AF_INET, &clientaddr.sin_addr, sockname, INET_ADDRSTRLEN) < 0)
	{
		perror("inet_ntop error");
		exit(1);
	}

	printf("sock name: %s\n", sockname);
	printf("sock port: %d\n", ntohs(clientaddr.sin_port));

	while ((n = read(sockfd, recvline, MAXLINE)) > 0)
	{
		//add end to the data,it avoids the messy code or previous data disturb the current data
		recvline[n] = 0;
		if (fputs(recvline, stdout) == EOF)
		{
			perror("fputs error");
		}
	}

	if (n < 0)
	{
		perror("read error");
	}
	return 0;
}
