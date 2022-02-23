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
#include <sys/wait.h>
#include <errno.h>

void str_echo(int sockfd){
	char data[MAXLINE];
	while (read(sockfd, data, MAXLINE) > 0)
	{
		int a = 0,b = 0;
		sscanf(data, "%d%d",&a,&b);
		printf("a=%d,b=%d\n",a,b);
		int sum = a+b;
		printf("sum is %d\n", sum);
		char send_data[MAXLINE];
		snprintf(send_data, MAXLINE, "%d\n", sum);
		write(sockfd, send_data,MAXLINE);

	}
}

void sig_chld(int signo)
{
	pid_t pid;
	int stat;
	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
	{
		printf("terminate child %d\n",pid);
	}
}
int main(int argc, char * argv[])
{
	int listenfd=0,connfd=0;
	struct sockaddr_in servaddr;
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0) )< 0)
	{
		perror("socket error");
		exit(1);
	}
	bzero(&servaddr, sizeof servaddr);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(COMMONPORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(listenfd, (SA*)&servaddr, sizeof servaddr) < 0)
	{
		perror("bind error");
		exit(1);
	}

	signal(SIGCHLD, sig_chld);

	if (listen(listenfd, LISTENQ) < 0)
	{
		perror("listen error");
		exit(1);
	}


	printf("start accept\n");

	for(;;)
	{
		connfd = accept(listenfd,NULL,0);
		if (connfd < 0 && errno == EINTR)
		{
			printf("connfd less zero becase EINTR\n");
			continue;
		}
		else if (connfd < 0)
		{
			perror("accecpt error\n");
			close(listenfd);
			break;
		}
		int sid;
		if ((sid = fork())>0)
		{

			struct sockaddr_in cliaddr;
			bzero(&cliaddr, sizeof cliaddr);
			socklen_t len = sizeof cliaddr;
			getpeername(connfd, (SA*)&cliaddr, &len);
			char cliip[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &cliaddr.sin_addr,cliip,INET_ADDRSTRLEN);
			printf("ip:%s\n", cliip);
			printf("port:%d\n", ntohs(cliaddr.sin_port));

			close(connfd);
		}
		else if (sid == 0)
		{
			close(listenfd);
			str_echo(connfd);
			close(connfd);
		}
	}
}