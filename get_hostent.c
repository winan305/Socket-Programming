#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>


int main(int argc, char *argv[])
{
    struct in_addr in;
    struct hostent *hp;
    int i;
    char buf[20];

    if(argc < 2)
    {
        printf("Use : %s hostname \n", argv[0]);
        exit(0);
    }

    hp = gethostbyname(argv[1]);
    if(hp==NULL)
    {
        printf("gethostbyname fail\n");
    }

    printf("Host name        : %s\n", hp -> h_name);
    printf("Host addr type   : %d\n", hp -> h_addrtype);
    printf("Host addr length : %d bytes \n", hp -> h_length);

    for(i = 0; hp -> h_addr_list[i]; i++)
    {
        memcpy(&in.s_addr, hp -> h_addr_list[i], sizeof(in.s_addr));
        inet_ntop(AF_INET, &in, buf, sizeof(buf));
        printf("IP Addr (no. %d) : %s\n", i+1, buf);
    }
   
    for(i = 0; hp -> h_aliases[i]; i++)
        printf("Host aliases (no. %d) : %s\n", i+1, hp -> h_aliases[i]);
    return 0;
}

