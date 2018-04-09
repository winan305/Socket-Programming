#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAXLINE 127

int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    int s, nbyte;
    char buf[MAXLINE+1];

    if(argc != 3)
    {
        exit(0);
    }

    if((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        exit(0);
    }

    bzero((char*)&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    servaddr.sin_port = htons(atoi(argv[2]));

    if(connect(s, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        exit(0);
    }

    printf("Input : ");
    if(fgets(buf, sizeof(buf), stdin) == NULL) exit(0);

    nbyte = strlen(buf);

    if(write(s, buf, nbyte) < 0) exit(0);

    printf("Ouput : ");
    if((nbyte = read(s, buf, MAXLINE)) < 0) exit(0);

    buf[nbyte] = 0;
    printf("%s", buf);
    close(s);
    return 0;
}
