#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/time.h>
#include <fcntl.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int count = 0;
    int fd;
    struct timeval t1, t2;
    double elapsedTime;
    char elapsedTimeStr[100];
    double max = 0.0;
    double min = 0.0;
    double avg = 0.0;

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

            char write_msg[BUFFER_SIZE];
            char read_msg[BUFFER_SIZE];
            int fd2[2];

            if (pipe(fd2) == -1) {
                fprintf(stderr,"Pipe failed");
                return 1;
            }

            if(fork() == 0){
                gettimeofday(&t1, NULL);
                fd = open("/dev/null",O_WRONLY | O_CREAT, 0666);
                if(fork() == 0){
                    dup2(fd, 1);
                    int status_code = execvp(arguments[0], arguments);
                }
                
                wait(NULL);
                close(fd);
                
                gettimeofday(&t2, NULL);
                elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
                elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
               
                close(fd2[READ_END]);
                sprintf(elapsedTimeStr, "%f", elapsedTime);
                write(fd2[WRITE_END], elapsedTimeStr, strlen(elapsedTimeStr)+1);
                close(fd2[WRITE_END]);

                exit(0);
            }
            close(fd2[WRITE_END]);
            read(fd2[READ_END], read_msg, BUFFER_SIZE);

            elapsedTime = strtod(read_msg,NULL);

            if(i == 0){
                max = elapsedTime;
                min = elapsedTime;
            }else if(i != 0){
                if(elapsedTime > max){
                    max = elapsedTime;
                }
                if(elapsedTime < min){
                    min = elapsedTime;
                }
            }
            avg += elapsedTime;


            printf("Child %d Executed in %s millis\n",i+1,read_msg);
            close(fd2[READ_END]);
        }
    }
    avg = avg/n;
    printf("\nMax: %f millis\n",max);
    printf("Min: %f millis\n",min);
    printf("Avgerage: %f millis\n",avg);
    return 0;
}
