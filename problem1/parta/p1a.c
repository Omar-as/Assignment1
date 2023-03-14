#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int n = atoi(argv[1]);
    printf("Main Process ID: %d, level: 0\n", getpid());
    int level = 0;
    for(int i = 0; i < n; i++){
        pid = fork();
        if(pid == 0){
            level++;
            printf("Process ID: %d, Parent ID: %d, level: %d\n",getpid(),getppid(),level);
        }
        wait(NULL);
    }
    return 0;
}
