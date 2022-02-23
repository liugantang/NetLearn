//
// Created by liugantang on 2022/2/23.
//

#include "commondetermine.h"
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void str_cli(int sockfd)
{
	char buf[MAXLINE] = { 0 };
	int a = 0, b = 0;
	while (scanf("%d %d", &a, &b) != EOF)
	{
		snprintf(buf, MAXLINE, "%d %d\n", a, b);
		write(sockfd, buf, strlen(buf));
		char ret[MAXLINE] = { 0 };
		if (read(sockfd, ret, MAXLINE) > 0)
		{
			printf("sum is %s\n", ret);
		}
		else
		{
			perror("read error");
			return;
		}
	}
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		char * str = "EchoSumClient <IP Addr>\n";
		write(STDERR_FILENO, str, strlen(str));
		exit(1);
	}

	int sockfd = 0;
	struct sockaddr_in servaddr;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
	{
		perror("socket error");
		exit(1);
	}
	bzero(&servaddr, sizeof servaddr);
	servaddr.sin_port = htons(COMMONPORT);
	servaddr.sin_family = AF_INET;
	if ((inet_pton(AF_INET, argv[1], &servaddr.sin_addr)) < 0)
	{
		perror("inet_pton error");
		exit(1);
	}
	printf("start connect\n");
	if (connect(sockfd, (SA*)&servaddr, sizeof servaddr) < 0)
	{
		perror("connect error");
		exit(1);
	}

	str_cli(sockfd);

}