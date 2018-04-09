#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main()
{
    struct servent *servent;
    servent = getservbyname("echo", "udp");
    if(servent == NULL)
    {
        printf("Can't get service information.\n\n");
        exit(0);
    }

    printf("UDP echo port(Network order) : %d\n", servent -> s_port);
    printf("UDP echo port(Host order) : %d\n", ntohs(servent -> s_port));

    return 0;
}
