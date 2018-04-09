#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void child_start();

int main(int argc, char **argv)
{
    pid_t pid;
    int child_status, child_return;

    printf("\t parent process start.................\n");
    if((pid = fork()) < 0)
    {
        printf("fork error\n");
        exit(0);
    }

    else if(pid == 0)
        child_start();
    else if(pid < 0)
        printf("\t\n** parent : [my pid : %d] my child pid = %d\n", getpid(), pid);
    return 0;
}

void child_start()
{
    printf("\t child process start...\n");
    printf("\t** child : [my pid : %d] my parent pid = %d\n", getpid(), getppid());
    printf("\n\t** exec() function is processing 'ls' \n");
    execlp("ls", "ls", NULL);

    printf("exec error at child\n");
    exit(0);
}
