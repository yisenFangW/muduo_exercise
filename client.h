//
// Created by 方伟 on 2019-08-20.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include<arpa/inet.h>

#define MAXLINE     1024
#define IPADDRESS   "127.0.0.1"
#define SERV_PORT   8787
static const int kMicroSecondsPerSecond = 1000 * 1000;

#define max(a,b) (a > b) ? a : b


class Client{
public:
    int connectServer();

    void handle_connection(int sockfd);

    int64_t now();

    bool checkHeartBeat(struct pollfd *connfd, int i);

private:
    int64_t microSecondsSinceEpoch_;

};

inline double timeDiff(int64_t t1, int64_t t2){
    return ((double)(abs(t1 - t2)))/kMicroSecondsPerSecond;
}

#endif //CLIENT_CLIENT_H
