/*
   2018년도 1학기 네트워크 프로그래밍
   2013136110 전두영
   Ubuntu 16.04.3 LTS
   daytime_server.c
   ex) ./daytime_server 5123
*/
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>

#define MAXLINE 127

int main(int argc, char *argv[])
{
    // 서버, 클라이언트를 위한 소켓 구조체 선언
    struct sockaddr_in servaddr, cliaddr;
    // 소켓통신에 필요한 int형 변수들 선언
    int listen_sock, accp_sock, addrlen=sizeof(cliaddr), nbyte;
    // 버퍼 선언
    char buf[MAXLINE+1];
    // 시간을 위해 time 라이브러리를 사용하여 변수 선언
    time_t t;

    // argc가 2가 아니면 입력 에러이다. 입력 방법 출력 후 종료한다.
    if(argc != 2)
    {
        printf("Usage : ./datime_server [port]\n");
        exit(1);
    }
 
    // 인터넷, 스트림(TCP)를 사용하여 소켓을 생성한다.
    // 에러 발생 시 에러를 출력하고 종료한다.
    if((listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
	printf("Socket Error.\n");
	exit(0);
    }

    // servaddr을 0으로 채운다.
    bzero((char *)&servaddr, sizeof(servaddr));
    // 프로토콜, IP, 포트를 저장한다.
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    // 서버소켓을 바인딩한다. 에러발생 시 출력 후 종료한다.
    if(bind(listen_sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("Bind Error.\n");
        exit(0);
    }

    // 클라이언트 연결을 대기한다. 연결제한은 5개이다.
    listen(listen_sock, 5);

    printf("Day time Server Start.\n");
    // 클라이언트의 연결과 끊김을 무한 반복한다.
    while(1)
    {
    	// 기다림을 출력하고 accept 상태로 들어선다.
        printf("Waiting..\n");
        accp_sock = accept(listen_sock, (struct sockaddr *)&cliaddr, &addrlen);

    	// accept 에러 발생 시 출력 후 종료한다.
        if(accp_sock < 0)
        {
            printf("Accept Error.\n");
            exit(0);
        }

    	// 클라이언트가 연결되었음을 출력한다.
        printf("Client connecting.\n");
	// ctime은 시스템의 현재 시간을 문자열로 반환한다.
	// buf에 복사해준다.

	// 현재 시스템의 시간을 받아온다.
        time(&t);
        strcpy(buf, ctime(&t));
		
	// 복사한 daytime 을 소켓에 write 해 준다.
        write(accp_sock, buf, sizeof(buf));
		
	// 소켓에 write 한 day time 을 서버에 출력한다.
        printf("Write day time : %s\n", buf);
	// 클라이언트와의 연결을 끊는다.
        close(accp_sock);
    }
    // 서버소켓을 닫는다.
    close(listen_sock);
    // 프로그램 종료.
    return 0;
}










