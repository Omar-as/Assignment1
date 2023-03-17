#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define MAX_INPUT_NUMS 1000

static int *nums;
static int *found;

void makeLifeSimple(int start, int end, int target){
    for(int i = start; i < end; i++){
        if(*found != -1){
            return;
        }
        if(nums[i] == target){
            *found = i;  
            // DEBUG
            // printf("Found target at position %d.\n", i);
            return;
        }
    }
    exit(1);
}

int main(int argc, char *argv[]){
    int nums_count = 0;
    int target = atoi(argv[1]);
    int children = atoi(argv[2]);

    // Allocate shared memory
    nums  = mmap(NULL, MAX_INPUT_NUMS * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    found = mmap(NULL,                  sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    *found = -1;

    while(nums_count < MAX_INPUT_NUMS && scanf("%d", &(nums[nums_count])) != EOF) nums_count++;


    // DEBUG
    // for(int i = 0; i < nums_count; i++)
    // {
    //     printf("nums[%d] = %d\n", i, nums[i]);
    // }

    int elements_per_child = nums_count / children;

    for (int i = 0; i < children; i++)
    {
        int beg = i * elements_per_child;
        int lst = i == (children - 1);
        int end = lst ? nums_count : (i + 1) * elements_per_child;
        
        if(fork() == 0)
        {
            makeLifeSimple(beg, end, target);
            exit(0);
        }
    }

    // Wait for all children to terminate
    while(wait(NULL) > 0);

    printf("Found target at index: %d.\n", *found);

    return 0;
}
