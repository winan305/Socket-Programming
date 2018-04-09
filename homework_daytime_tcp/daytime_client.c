/*
   2018년도 1학기 네트워크 프로그래밍
   2013136110 전두영
   Ubuntu 16.04.3 LTS
   daytime_client.c
   ex) ./daytime_clinet 127.0.0.1 5123
*/
   
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
    // 소켓구조체, 소켓, 데이터 송수신을 위한 바이트, 버퍼 선언
    struct sockaddr_in servaddr;
    int s, nbyte;
    char buf[MAXLINE+1];

    // 입력값 체크, argc가 3이 아니면 사용법 오류
    if(argc != 3)
    {
	// 사용법을 출력하고 종료한다.
        printf("Usage : ./daytime_client [IP Address] [Port]\n");
        exit(0);
    }

    // 소켓을 인터넷, 스트림(TCP)로 생성하고, 에러 발생 시 출력후 종료한다.
    if((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket Error.\n");
        exit(0);
    }

    // servaddr을 0으로 채우고 프로토콜, 아이피, 포트번호를 저장한다.
    bzero((char*)&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    servaddr.sin_port = htons(atoi(argv[2]));

    // 서버소켓과 연결한다. 에러 발생 시 출력 후 종료한다.
    if(connect(s, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("Connect Error.\n");
        exit(0);
    }

    // 소켓 s로부터 buf에 MAXLINE 까지 읽어들인다. nbyte가 음수이면 에러이므로 출력 후 종료한다.
    if((nbyte = read(s, buf, MAXLINE)) < 0) 
    {
	printf("Read Error.\n");
	exit(0);
    }

    // 버퍼의 끝을 0으로 저장하고 서버로부터 읽어들인 day time 을 출력한다. 
    buf[nbyte] = 0;
    printf("Read day time : %s\n", buf);
    // 소켓 연결을 종료한다.
    close(s);
    // 클라이언트 프로그램 종료.
    return 0;
}
