//
// Created by liugantang on 2022/2/21.
//
#pragma once
#include <stdio.h>
#include <commondetermine.h>
#include <unistd.h>
#include <string.h>

void str_cli(FILE * fp, int sockfd);

void str_cli(FILE * fp, int sockfd)
{
	char sendline[SMALLLINE];
	char recvline[SMALLLINE+1];

	while (fgets(sendline, SMALLLINE, fp) != NULL)
	{
		long wsize = strlen(sendline);
		//write header, describe data size
		if (write(sockfd, &wsize, sizeof wsize)<0)
		{
			perror("write error");
		}

		if (write(sockfd, sendline, wsize)<0)
		{
			perror("write error");
			return;
		}

		int n = 0;
		if ((n = read(sockfd, recvline, SMALLLINE)) < 0)
		{
			perror("read error");
			return;
		}

		write(STDOUT_FILENO, recvline, n);
	}
}