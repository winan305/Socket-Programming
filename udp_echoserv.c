#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


#define MAXLINE 511

int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr, cliaddr;
    int s, addrlen = sizeof(struct sockaddr), nbyte;
    char buf[MAXLINE+1];

    if(argc != 2)
    {
        printf("usage : ./udp_echoserv port");
        exit(0);
    }

    if((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) 
    {
        printf("socket fail\n");
        exit(0);
    }

    bzero((char *)&servaddr, addrlen);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    if(bind(s, (struct sockaddr*)&servaddr, addrlen) < 0)
    {
        printf("bind fail\n");
        exit(0);
    }

    while(1)
    {
        printf("Server : waiting request.\n");

        nbyte = recvfrom(s, buf, MAXLINE, 0, (struct sockaddr *)&cliaddr, &addrlen);
        if(nbyte < 0)
        {
            printf("recvfrom fail\n");
            exit(0);
        }

        buf[nbyte] = 0;
        printf("%d byte recv : %s\n", nbyte, buf);
        if(sendto(s, buf, nbyte, 0, (struct sockaddr*)&cliaddr, addrlen) < 0)
        {
            printf("sendto fail\n");
            exit(0);
        }
    }
    printf("sendto complete\n");
    return 0;
}










