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

// generic function pointer: tasks take no args and return a status char
typedef char (*ptrFunc)(void);

// process descriptor: holds the task function
typedef struct
{
	ptrFunc func;
	int processSize;
	int processStatus;
} process;

// circular buffer of process pointers
process *pool[POOL_SIZE];

// ---- Buffer helpers ----

// returns 1 if the pool has no room for a new process
char bufferFull(void)
{
	return ((end + 1) % POOL_SIZE) == start;
}

// returns 1 if the pool has no processes pending
char bufferEmpty(void)
{
	return start == end;
}

// ---- Kernel API ----

// resets the scheduler state; must be called before any other kernel function
char kernelInit(void)
{
	start = 0;
	end = 0;
	return SUCCESS;
}

// enqueues a process into the pool; returns FAIL if the pool is full
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

// prints whether a process was successfully added to the pool
void printAddResult(char result, int id)
{
	if (result == SUCCESS)
		printf("Process %d added successfully\n", id);
	else
		printf("Process %d failed to add\n", id);
}

// runs the scheduler until MAX_ITERATIONS ticks are reached
void kernelLoop(void)
{
	for (;;)
	{
		if (!bufferEmpty())
		{
			pool[start]->func();
        	start = (start+1)%POOL_SIZE;
		}

		count++;
		if (count >= MAX_ITERATIONS)
			break;
	}
}

// ---- Entry point ----
void main(void)
{
	// process descriptors: {task function}
	process p1 = {sensorTask};
	process p2 = {ledTask};
	process p3 = {displayTask};
	process p4 = {logTask};
	process p5 = {uartTask};

	// initialize kernel
	kernelInit();

	// register processes and report result
	printf("Registering processes...\n");
	printAddResult(kernelAddProc(&p1), 1);
	printAddResult(kernelAddProc(&p2), 2);
	printAddResult(kernelAddProc(&p3), 3);
	printAddResult(kernelAddProc(&p4), 4);
	printAddResult(kernelAddProc(&p5), 5);

	printf("\nStarting scheduler loop...\n\n");
	kernelLoop();
}
