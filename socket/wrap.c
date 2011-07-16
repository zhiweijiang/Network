#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>

void perr_exit(const char *s)
{
    perror(s);
    exit(1);
}

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    int n;

    while(1)
    {
        if((n = accept(fd, sa, salenptr)) < 0)
        {
            if((errno != ECONNABORTED) && (errno != EINTR))
            {
                perr_exit("accept error");
                break;
            }
        }
        else 
            break;
    }

    return n;
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if(bind(fd, sa, salen) < 0)
    {
        perr_exit("bind error");
    }
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if(connect(fd, sa, salen) < 0)
    {
        perr_exit("connect error");
    }
}

void Listen(int fd, int backlog)
{
    if(listen(fd, backlog) < 0)
    {
        perr_exit("listen error");
    }
}

int Socket(int family, int type, int protocol)
{
    int n;
    
    if((n = socket(family, type, protocol)) < 0)
    {
        perr_exit("socket error");
    }

    return n;
}

ssize_t Read(int fd, void *ptr, size_t nbytes)
{
    ssize_t n;

    while(1)
    {
        if((n = read(fd, ptr, nbytes)) == -1)
        {
            if(errno != EINTR)
            {
                return -1;
            }
        }
        else 
            break;
    }

    return n;
}

ssize_t Write(int fd, void *ptr, size_t nbytes)
{
    ssize_t n;

    while(1)
    {
        if((n = write(fd, ptr, nbytes)) == -1)
        {
            if(errno != EINTR)
            {
                return -1;
            }
        }
        else 
            break;
    }

    return n;
}


void Close(int fd)
{
    if(close(fd) == -1)
    {
        perr_exit("close error");
    }
}

ssize_t Readn(int fd, void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nread;
    char *ptr;

    ptr = vptr;
    nleft = n;
    while(nleft > 0)
    {
        if(( nread = read(fd, ptr, nleft)) < 0)
        {
            if(errno == EINTR)
            {
                nread = 0;
            }
            else
            {
                return -1;
            }
         }
        else if(nread == 0)
        {
            break;
        }

            nleft -= nread;
            ptr += nread;
    }

    return n - nleft;
}


ssize_t Writen(int fd, void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nwrite;
    char *ptr;

    ptr = vptr;
    nleft = n;
    while(nleft > 0)
    {
        if(( nwrite = write(fd, ptr, nleft)) < 0)
        {
            if(errno == EINTR)
            {
                nwrite = 0;
            }
            else
            {
                return -1;
            }
         }
        else if(nwrite == 0)
        {
            break;
        }

            nleft -= nwrite;
            ptr += nwrite;
    }

    return n - nleft;
}

static ssize_t my_read(int fd, char *ptr)
{
    static int read_cnt;
    static char *read_ptr;
    static char read_buf[100];

    if(read_cnt <= 0)
    {
        while(1)
        {
            if((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0)
            {
                if(errno != EINTR)
                {
                    return -1;
                }
            }
            else if(read_cnt == 0)
            {
                return 0;
            }
        }
        read_ptr = read_buf;
    }
    read_cnt --;
    *ptr = *read_ptr++;

    return 1;
}    

ssize_t Readline(int fd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char c, *ptr;

    ptr = vptr;
    for(n = 1; n < maxlen; n++)
    {
        if((rc = my_read(fd, &c)) == 1)
        {
            *ptr++ = c;
            if(c == '\n')
                break;
        }
        else if(rc == 0)
        {
            *ptr = 0;
            return n - 1;
        }
        else
        {
            return -1;    
        }
    }
    *ptr = 0;

    return n;
}
