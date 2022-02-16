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
		if (argc == 2)
		{
			str_cli(stdin, connfd);
		}
		else if (argc == 3)
		{
			FILE * fp = fopen(argv[2], "r");
			if (fp != NULL)
			{
				str_cli(fp, connfd);
			}
		}
	}

	close(connfd);
	return 0;
}