#include <stdio.h>

// ---- Kernel state ----
int start, end;  // circular buffer head and tail indices
int count = 0;   // global iteration counter

// ---- Return codes ----
#define SUCCESS       0
#define FAIL          1

// ---- Kernel configuration ----
#define POOL_SIZE      10   // max number of processes in the pool
#define MAX_ITERATIONS 10   // scheduler stops after this many ticks
#define KERNEL_SLICE   5    // max iterations a process can run before being preempted

// ---- Task definitions ----
char sensorTask(void)
{
    printf("Executing Sensor Task\n");
    return SUCCESS;
}
char ledTask(void)
{
    printf("Executing LED Task\n");
    return SUCCESS;
}
char displayTask(void)
{
    printf("Executing Display Task\n");
    return SUCCESS;
}
char logTask(void)
{
    printf("Executing Log Task\n");
    return SUCCESS;
}
char uartTask(void)
{
    printf("Executing UART Task\n");
    return SUCCESS;
}

// ---- Process abstraction ----
typedef char (*ptrFunc)(void);

// process descriptor: task function + tamanho total e status atual de execução
typedef struct
{
    ptrFunc func;
    int processSize;    // quantas execuções o processo precisa para terminar
    int processStatus;  // quantas execuções já foram feitas
} process;

// circular buffer de ponteiros para processos
process *pool[POOL_SIZE];

// ---- Buffer helpers ----
char bufferFull(void)
{
    return ((end + 1) % POOL_SIZE) == start;
}
char bufferEmpty(void)
{
    return start == end;
}

// ---- Kernel API ----
char kernelInit(void)
{
    start = 0;
    end = 0;
    return SUCCESS;
}

char kernelAddProc(process *newProc)
{
    if (!bufferFull())
    {
        pool[end] = newProc;
        end = (end + 1) % POOL_SIZE;
        return SUCCESS;
    }
    return FAIL;
}

void printAddResult(char result, int id)
{
    if (result == SUCCESS)
        printf("Process %d added successfully\n", id);
    else
        printf("Process %d failed to add\n", id);
}

// executa o scheduler com fatia de tempo (quantum) por processo
void kernelLoop(void)
{
    for (;;)
    {
        if (bufferEmpty())
        {
            printf("\nQueue empty, scheduler done.\n");
            break;
        }

        process *current = pool[start];
        start = (start + 1) % POOL_SIZE;

        int sliceUsed = 0;

        printf("\n-- Dispatching process (size=%d, status=%d) --\n",
               current->processSize, current->processStatus);

        while (current->processStatus < current->processSize &&
               sliceUsed < KERNEL_SLICE)
        {
            current->func();
            current->processStatus++;
            sliceUsed++;
        }

        if (current->processStatus < current->processSize)
        {
            printf("-- Slice expired (status=%d/%d), requeueing --\n",
                   current->processStatus, current->processSize);

            if (!bufferFull())
            {
                pool[end] = current;
                end = (end + 1) % POOL_SIZE;
            }
            else
            {
                printf("Pool full, process lost\n");
            }
        }
        else
        {
            printf("-- Process finished (size=%d) --\n", current->processSize);
        }
    }
}

// ---- Entry point ----
void main(void)
{
    process p1 = {sensorTask, 6, 0};
    process p2 = {ledTask, 2, 0};
    process p3 = {displayTask, 3, 0};
    process p4 = {logTask, 7, 0};
    process p5 = {uartTask, 3, 0};

    kernelInit();

    printf("Registering processes...\n");
    printAddResult(kernelAddProc(&p1), 1);
    printAddResult(kernelAddProc(&p2), 2);
    printAddResult(kernelAddProc(&p3), 3);
    printAddResult(kernelAddProc(&p4), 4);
    printAddResult(kernelAddProc(&p5), 5);

    printf("\nStarting scheduler loop...\n\n");
    kernelLoop();
}