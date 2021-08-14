#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include "statem.h"


int main(int argc, char *argv[]) {
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char* sendBuff = "HTTP/1.1 200 OK\n\n<head>Sebe derni, pes!<hr></head><body><a href = titi>dernut</a></body>";
    char reader[2024] = {0};

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(listenfd, 10);
    while(1) {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        read(connfd, reader, 2024);
        puts(reader);

        write(connfd, sendBuff, strlen(sendBuff));

        close(connfd);
        sleep(1);
        }
}