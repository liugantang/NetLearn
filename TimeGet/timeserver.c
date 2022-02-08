#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <commondetermine.h>
#include <string.h>
#include <time.h>

int main(int argc, char * argv[])
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket error");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(COMMONPORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    printf("create listen fd success\n");
    if (bind(listenfd, (SA*)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind error");
    }

    printf("bind listen fd success\n");

    if (listen(listenfd, LISTENQ) < 0)
    {
        perror("listen error");
    }

    printf("set listen queue success, start listening\n");
    for (;;)
    {
        connfd = accept(listenfd, (SA*)NULL, NULL);
        ticks = time(NULL);
        snprintf(buff, sizeof buff, "%.24s\r\n", ctime(&ticks));
        if (write(connfd, buff, strlen(buff) ) < 0)
        {
            perror("write error");
            close(connfd);
            break;
        }
        close(connfd);
    }
	return 0;
}