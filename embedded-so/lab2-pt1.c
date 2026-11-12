#include <stdio.h>

typedef struct {
    char* processName;
    int time;
}process;

//circular buffer declaration
#define BUFFERSIZE  10
process buffer[BUFFERSIZE];

//Declaration of access pointers
int start=0, end=0, current=0;

//Function to add process to buffer
void addProc(char *nname, int ntime){

  //Verification of position (full?)
  if (((end+1)%BUFFERSIZE) != start){
    //Current position update
    buffer[end].processName = nname;
    buffer[end].time = ntime;
    //increment circular buffer position
    end = (end+1)%(BUFFERSIZE);
  }
}

//Function to remove process from buffer
void removeProc (void){

  //Verification of position (empty?)
  if (end != start){
    //increment circular buffer start position
    start = (start +1)%(BUFFERSIZE);
  }
}

bool isBufferEmpty(){
  if(start == end)
    return true;
  else
    return false;
}

bool isBufferFull(){
  return ((end+1)%(BUFFERSIZE) == start);
}

void printBuffer(process buffer[]){
  printf("Beginning: %d\n", start);
  printf("End: %d\n", end);
  if(isBufferEmpty()){
    printf("Empty Buffer\n");
  }
  else{
    int current = start;
    int numProc = 0;

    while(current != end){
      printf("Process %d: %s %d\n", numProc, buffer[current].processName, buffer[current].time);
      current = (current+1) % BUFFERSIZE;
      numProc++;
    }
 }
}
  
void main (void){
  addProc("proc1", 0);
  addProc("proc2", 1);
  addProc("proc3", 2);
  printBuffer(buffer);
  removeProc();
  removeProc();
  removeProc();
}
