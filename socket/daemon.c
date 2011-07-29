#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, const char *argv[])
{
    int fd, i;
    pid_t pid;
    char *str = "this is a demaon    ";

    pid = fork();
    if(pid < 0)
    {
        printf("fork error\n");
        exit(1);
    }
    else if(pid == 0)
    {
        exit(0);
    }

    setsid();
    chdir("/");
    umask(0);

    for(i = 0; i < getdtablesize(); i++)
    {
        close(i);
    }
    while(1)
    {
        if((fd = open("/tmp/logfile", O_CREAT|O_WRONLY|O_APPEND))< 0)
        {
            printf("open file error\n");
            return 4;
        }
        write(fd, str, strlen(str)+1);
        close(fd);
        sleep(10);
    }

    return 0;
}
