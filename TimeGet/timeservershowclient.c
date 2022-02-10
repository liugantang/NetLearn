//
// Created by liugantang on 2022/2/9.
//

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <commondetermine.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char senddata[MAXLINE];
    time_t tick;


    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        perror("socket error");
        exit(1);
    }

    printf("create listen fd success\n");

    bzero(&servaddr, sizeof servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(COMMONPORT);

    if (bind(listenfd, (SA*)&servaddr, sizeof servaddr) < 0)
    {
        perror("bind error");
        exit(1);
    }

    printf("bind listen fd to server addr success\n");

    if (listen(listenfd, LISTENQ) < 0)
    {
        perror("listen error");
        exit(1);
    }

    printf("start listening\n");

    for(;;)
    {
        struct sockaddr_in clienaddr;
        socklen_t clienlen = sizeof clienaddr;
        if ((connfd = accept(listenfd, (SA*)&clienaddr, &clienlen))> 0) {
            char clientaddrstr[INET_ADDRSTRLEN];
            if (inet_ntop(AF_INET, &clienaddr.sin_addr, clientaddrstr, INET_ADDRSTRLEN) < 0) {
                perror("inet_ntop error");
                exit(1);
            }
            printf("client addr: %s\n", clientaddrstr);
            printf("client port:%d\n", ntohs(clienaddr.sin_port));

			struct sockaddr_in peeraddr;
			char peername[INET_ADDRSTRLEN];
			socklen_t peerlen = sizeof peeraddr;
			if (getpeername(connfd, (SA*)&peeraddr, &peerlen) < 0)
			{
				perror("get peer name error");
				exit(1);
			}
			inet_ntop(AF_INET, &peeraddr.sin_addr, peername, INET_ADDRSTRLEN);
			printf("peer name:%s\n", peername);
			printf("peer port:%d\n", ntohs(peeraddr.sin_port));

            tick = time(NULL);
            snprintf(senddata, MAXLINE, "%.24s\r\n", ctime(&tick));

            while (write(connfd, senddata, strlen(senddata)) < 0) {
                close(connfd);
                perror("write error");
                exit(1);
            }
            close(connfd);
        }

    }

    exit(0);
}