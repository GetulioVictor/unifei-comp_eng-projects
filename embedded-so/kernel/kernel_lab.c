/*
Getúlio Victor Faustino Moreira - 2024016055 
ECOS03 - Lab Kernel
*/
#include <stdio.h>

//kernel internal variables
int start, end;
int count = 0;
int maxIterations = 0;

//return code
#define SUCCESS   0
#define FAIL      1
#define REPEAT    2
#define POOL_SIZE 5

char tst1(void){
   printf("Process 1\n");
   return REPEAT;
}
char tst2(void){
   printf("Process 2\n");
   return SUCCESS;
}
char tst3(void){
   printf("Process 3\n");
   return REPEAT;
}

//function pointer declaration
typedef char(*ptrFunc)(void);

//process struct
typedef struct {
    ptrFunc func;
    int rescheduleCount;
    int rescheduleLimit;
    int remaining_time;
    int priority;
} process;

process * pool[POOL_SIZE];

// ponteiro de função do escalonador
typedef void(*ptrScheduler)(void);
ptrScheduler scheduler;

char kernelInit(int limit){
    start = 0;
    end = 0;
    maxIterations = limit;
    return SUCCESS;
}

char kernelAddProc(process * newProc){
    if ( ((end+1)%POOL_SIZE) != start){
        pool[end] = newProc;
        end = (end+1)%POOL_SIZE;
        return SUCCESS;
    }
    printf("Error: Couldn't add the process\n");
    return FAIL;
}

void schedulerFIFO(void){
    for(;;){
        if (start != end){
            if (pool[start]->func() == REPEAT){
                if(pool[start]->rescheduleCount < pool[start]->rescheduleLimit){
                    kernelAddProc(pool[start]);
                    pool[start]->rescheduleCount++;
                } else {
                    printf("Process reached reschedule limit\n");
                }
            }
            start = (start+1)%POOL_SIZE;
        }
        count++;
        if (count >= maxIterations) break;
    }
}

void schedulerSJF(void){
    for(;;){
        if (start != end){
            // percorre o buffer procurando menor remaining_time
            int minIndex = start;
            int i = (start+1)%POOL_SIZE;
            while(i != end){
                if(pool[i]->remaining_time < pool[minIndex]->remaining_time){
                    minIndex = i;
                }
                i = (i+1)%POOL_SIZE;
            }
            // troca o processo de menor tempo com o do inicio
            process * temp = pool[start];
            pool[start] = pool[minIndex];
            pool[minIndex] = temp;

            // executa normalmente
            if (pool[start]->func() == REPEAT){
                if(pool[start]->rescheduleCount < pool[start]->rescheduleLimit){
                    kernelAddProc(pool[start]);
                    pool[start]->rescheduleCount++;
                } else {
                    printf("Process reached reschedule limit\n");
                }
            }
            start = (start+1)%POOL_SIZE;
        }
        count++;
        if (count >= maxIterations) break;
    }
}

void main(void){
    // {func, rescheduleCount, rescheduleLimit, remaining_time, priority}
    process p1 = {tst1, 0, 4, 5, 1};
    process p2 = {tst2, 0, 2, 2, 2};
    process p3 = {tst3, 0, 3, 8, 3};
    
    int alg;
    
    
    if(kernelInit(10) == FAIL){
        printf("Error: Kernel init failed\n");
        return;
    }

    if(kernelAddProc(&p1) == SUCCESS){
        printf("1st process added\n");
    } else {
        printf("Error: Failed to add process 1\n");
    }

    if(kernelAddProc(&p2) == SUCCESS){
        printf("2nd process added\n");
    } else {
        printf("Error: Failed to add process 2\n");
    }

    if(kernelAddProc(&p3) == SUCCESS){
        printf("3rd process added\n");
    } else {
        printf("Error: Failed to add process 3\n");
    }
    
    printf("Select the scheduler:\n");
    printf("1 - FIFO:\n");
    printf("2 - SJF\n");
    scanf("%d" , &alg);
    
    if(alg == 1){
        scheduler = schedulerFIFO;
    }
    else if(alg == 2){
        scheduler = schedulerSJF;
    }
    else{
        printf("Invalid scheduler");
        return;
    }
    scheduler();
}
