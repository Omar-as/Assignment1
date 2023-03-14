#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
   pid_t childPID;
   childPID = fork();
   printf("child pid: %d",childPID);
   if(childPID > 0){
      sleep(30);
   }
   else{
      exit(0);
   }
   return 0;
}
