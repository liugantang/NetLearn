//
// Created by liugantang on 2022/2/10.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <commondetermine.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

void str_cli(FILE * fp, int sockfd)
{
	char sendline[MAXLINE];
	char recvline[MAXLINE];

	while (fgets(sendline, MAXLINE, fp) != NULL)
	{
		if (write(sockfd, sendline, strlen(sendline))<0)
		{
			perror("write error");
			return;
		}

		if (read(sockfd, recvline, MAXLINE) < 0)
		{
			perror("read error");
			return;
		}
		fputs(recvline, stdout);
	}
}

int main(int argc, char * argv[])
{
	int connfd;
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof servaddr);
	servaddr.sin_port = htons(COMMONPORT);
	servaddr.sin_family = AF_INET;
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr)<0)
	{
		perror("inet_pton error");
	}

	if ((connfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket error");
		exit(1);
	}

	if (connect(connfd, (SA*)&servaddr,sizeof servaddr) == 0)
	{
		str_cli(stdin, connfd);
	}

	close(connfd);
	return 0;
}