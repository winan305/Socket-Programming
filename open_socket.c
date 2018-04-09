#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd1, fd2, sd1, sd2;

    fd1 = open("./abc.txt", O_RDONLY, 0);
    printf("abc.txt file descriptor = %d\n", fd1);

    sd1 = socket(PF_INET, SOCK_STREAM, 0);
    printf("stream socket descriptor = %d\n", sd1);

    sd2 = socket(PF_INET, SOCK_DGRAM, 0);
    printf("datagram socket descriptor = %d\n", sd2);

    close(fd1);
    close(sd1);
    close(sd2);

    return 0;
}
