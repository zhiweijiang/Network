#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <error.h>
#include <arpa/inet.h>
#include <errno.h>
#include "wrap.h"

#define MAXLINE 80
#define SERV_PORT 8000

int main(int argc, const char *argv[])
{
    struct sockaddr_in servaddr;
    char buf[MAXLINE];
    int sockfd, n;
    char str[INET_ADDRSTRLEN];
    socklen_t servaddr_len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    servaddr.sin_port = htons(SERV_PORT);

    while(fgets(buf, MAXLINE, stdin) != NULL)
    {
        if((n = sendto(sockfd, buf, strlen(buf), 0,(struct sockaddr *)&servaddr, sizeof(servaddr))) == -1)
        {
            perr_exit("sendto error");
        }
        if((n = recvfrom(sockfd, buf, MAXLINE, 0, NULL, 0)) == -1)
        {
            perr_exit("recvfrom error");
        }
        Write(STDOUT_FILENO, buf, n);
    }

    Close(sockfd);

    return 0;
}
