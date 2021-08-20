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

machine stack[5] = {
    {"", CLOSED},
    {"", CLOSED},
    {"", CLOSED},
    {"", CLOSED},
    {"", CANARY}
};

int main(int argc, char *argv[]) {
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char reader[32*5];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(listenfd, 10);
    while(1){
	memset(reader, 0, 32*5);
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        read(connfd, reader, 32*5);

	puts(reader);

        char* ansver = new_query(reader, stack);
        write(connfd, ansver, strlen(ansver));

	_List_impl(reader, stack);
	puts(reader);

        close(connfd);
        sleep(1);
    }
}
