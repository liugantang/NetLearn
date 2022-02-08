#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include "commondetermine.h"

int main(int argc, char* argv[])
{
	int sockfd,n;
    char recvline[MAXLINE+1];
    struct sockaddr_in servaddr;

    if (argc != 2)
    {
        printf("usage: a.out <IPAddress>\n");
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0)
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
    }


    while ((n = read(sockfd, recvline, MAXLINE))>0)
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
