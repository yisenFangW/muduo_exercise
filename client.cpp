//
// Created by 方伟 on 2019-08-20.
//
#include "client.h"

int Client::connectServer() {
    int sockfd;
    struct sockaddr_in  servaddr;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET,IPADDRESS,&servaddr.sin_addr);
    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    return sockfd;
}

void Client::handle_connection(int sockfd)
{
    char    sendline[MAXLINE],recvline[MAXLINE];
    struct pollfd pfds[2];
    int n;
    //添加连接描述符
    pfds[0].fd = sockfd;
    pfds[0].events = POLLIN;
    // 添加标准输入描述符
    pfds[1].fd = STDIN_FILENO;
    pfds[1].events = POLLIN;
    for (; ;){
        poll(pfds,2,-1);
        if (pfds[0].revents & POLLIN){
            n = read(sockfd,recvline,MAXLINE);
            if (n == 0){
                fprintf(stderr,"client: server is closed.\n");
                close(sockfd);
                break;
            }
            write(STDOUT_FILENO,recvline,n);
        }
        // 测试标准输入是否准备好
        if (pfds[1].revents & POLLIN){
            n = read(STDIN_FILENO,sendline,MAXLINE);
            if (n == 0){
                shutdown(sockfd, SHUT_WR);
                continue;
            }
            write(sockfd,sendline,n);
        }
    }
}

int64_t Client::now(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t seconds = tv.tv_sec;
    return seconds*kMicroSecondsPerSecond + tv.tv_usec;
}

// 发送心跳包，看对面是否能回复，因为是echo服务器，所以肯定是能回复的，要是不能回复，就是对面凉了；
bool Client::checkHeartBeat(struct pollfd *connfd, int i) {
    char buf[] = "check session is alive!";
    write(connfd[i].fd, buf, sizeof(buf));
    return false;
}

int main(int argc,char *argv[])
{
    Client client;
    int sockfd = client.connectServer();
    client.handle_connection(sockfd);
    return 0;
}