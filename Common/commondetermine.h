//
// Created by liugantang on 2022/2/8.
//

#ifndef NETLEARN_COMMONDETERMINE_H
#define NETLEARN_COMMONDETERMINE_H
#define  MAXLINE 4096
#define SMALLLINE 16
#define COMMONPORT 13333
#define LISTENQ 64
#include <signal.h>
typedef struct sockaddr SA;
typedef void Sigfunc(int);

Sigfunc * signal(int signo, Sigfunc * func);
#endif //NETLEARN_COMMONDETERMINE_H
