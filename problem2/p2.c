#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int n = atoi(argv[1]);
    int count = 0;

    /* counting the number of commands name strings we have */
    while(argv[count] != NULL){
        count++;
    }

    /* creating the array of commands to use for execvp */
    char *arguments[count];
    for(int i = 2; i < count; i++){
        arguments[i-2] = argv[i];
    }
    arguments[count-2] = NULL;

    pid_t parentPID = getpid();
    for (int i = 0; i < n; i++){
        if(getpid() == parentPID){
            pid = fork();
        }
        if(pid == 0){
            int status_code = execvp(arguments[0], arguments);
        }
    }
    return 0;
}
