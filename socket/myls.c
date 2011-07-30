#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

int my_read_dir(const char *path)
{
    DIR *my_dir;
    struct dirent *dir;

    if((my_dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
    }

    while((dir = readdir(my_dir)) != NULL)
    {
        printf("file name: %s\n", dir->d_name);
    }
    closedir(my_dir);

    return 0;
}


int main(int argc, char *argv[])
{
    struct stat buf;

    argv[1] = "./";
/*    if(argc < 2)
    {
        printf("usage: %s para\n",__FILE__);
        exit(2);
    }
*/
    stat(argv[1], &buf);
    if(!S_ISDIR(buf.st_mode))
    {
        printf("diretory not found!\n");
        exit(3);
    }
    if(my_read_dir(argv[1]))
    {
        perror("my_read_dir");
        return -1;
    }

    return 0;
}
