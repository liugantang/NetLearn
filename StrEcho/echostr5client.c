//
// Created by liugantang on 2022/2/21.
//

#pragma once
#include "strcli.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	int i, sockfd[5];
	struct sockaddr_in servaddr;

	if (argc != 2)
	{
		perror("need id addr as arg");
		exit(1);
	}

	for (i = 0; i < 5; i++)
	{
		sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd[i] < 0)
		{
			perror("socket error");
			exit(1);
		}
		bzero(&servaddr, sizeof servaddr);
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(COMMONPORT);
		inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
		connect(sockfd[i],(SA*)&servaddr, sizeof servaddr);
	}
	str_cli(stdin, sockfd[0]);
	exit(0);
}