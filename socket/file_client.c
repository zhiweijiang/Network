#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <error.h>
#include <arpa/inet.h>

#define MAXLINE 4096
#define SERV_PORT 8000

int main(int argc, const char *argv[])
{
    struct sockaddr_in servaddr;
    char buf[MAXLINE];
    int sockfd, n, fd;
    char str[20] = "0";

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    servaddr.sin_port = htons(SERV_PORT);

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
        scanf("%s", str);
         if((fd =open(str, O_RDONLY|O_NONBLOCK)) < 0)
        {
            perror("open");
            exit(1);
        }
        write(sockfd, str, strlen(str)+1); 
    while(1)
    {
        n = read(fd, buf, MAXLINE);
    if(n > 0)
        write(sockfd, buf, n);
        else
         break;
     }
        n = read(sockfd, buf, MAXLINE);
        printf("Response from server:\n");
        write(STDOUT_FILENO, buf, n);

    close(fd);
    close(sockfd);
    return 0;
}
