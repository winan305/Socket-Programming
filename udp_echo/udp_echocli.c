#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAXLINE 511

int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    int s, nbyte, addrlen = sizeof(servaddr);
    char buf[MAXLINE+1];

    if(argc != 3)
    {
        printf("usage : ./udp_echocli [IP Address]\n");    
        exit(0);
    }

    if((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        exit(0);
    }

    bzero((char*)&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(atoi(argv[2]));

    printf("Input : ");
    if(fgets(buf, MAXLINE, stdin) == NULL)
    {
        printf("fgets fail\n");
        exit(0);
    }

    if(sendto(s, buf, strlen(buf), 0, (struct sockaddr *)&servaddr, addrlen) < 0)
    {
        printf("sendto fail\n");
        exit(0);
    }

    if((nbyte = recvfrom(s, buf, MAXLINE, 0, (struct sockaddr*)&servaddr, &addrlen)) < 0)
    {
        printf("recvfrom fail\n");
        exit(0);
    }

    buf[nbyte] = 0;
    printf("%s", buf);
    close(s);
    return 0;
}
