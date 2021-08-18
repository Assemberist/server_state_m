#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include "statem.h"

void fuck(){
    perror("Alyarma");
    exit(-1);
}

int main(int argc, char *argv[]) {
    int sockfd = 0, n = 0;
    char recvBuff[32*5];
    struct sockaddr_in serv_addr;

    if(argc > 2) {
        errno = E2BIG;
        fuck();
    }

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) fuck();

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(5000);

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) fuck();

    sprintf(recvBuff, "init:qwe");
    write(sockfd, recvBuff, strlen(recvBuff));

    while( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0){
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF) fuck();
    }

    if(n < 0) puts("\n Read error");
    return 0;
}