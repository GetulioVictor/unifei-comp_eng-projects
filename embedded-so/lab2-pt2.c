#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef int (*ptrFunc)(void);

typedef struct {
    char * name;
    int time;
    ptrFunc func;
    int priority;
} process;

#define BUFFERSIZE  10

process buffer[BUFFERSIZE];
int start = 0, end = 0;

void addProc(process newProcess) {
    if (((end + 1) % BUFFERSIZE) != start) {
        buffer[end].name = strdup(newProcess.name);
        buffer[end].time = newProcess.time;
        buffer[end].func = newProcess.func;
        buffer[end].priority = newProcess.priority;
        end = (end + 1) % BUFFERSIZE;
    } else {
        printf("Buffer cheio, processo %s nao adicionado.\n", newProcess.name);
    }
}

//letra b
int execProc(process proc){
    printf("Executando: '%s'\n", proc.name);
    int tmp = proc.func();          // executa e salva retorno
    printf("Retorno: %d\n", tmp);
    return tmp;   
}

void priorityBuffer(void){
    //copiar os processos do buffer para um array temporario
    process temp[BUFFERSIZE];
    process swap;
    int idx;
    
    // Calcula quantos processos estão no buffer
    int count = (end - start + BUFFERSIZE) % BUFFERSIZE;
    
    //buffer vazio
    if(count == 0)
      return;
  
    for (int i = 0; i < count; i++) {
        idx = (start + i) % BUFFERSIZE;
        temp[i] = buffer[idx];
        temp[i].name = strdup(buffer[idx].name); //duplica a string
    }
    
    //ordernar o array 
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (temp[j].priority > temp[j + 1].priority) {
                swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }
  
    //retornar os processos para o buffer circular
    for (int i = 0; i < count; i++) {
        buffer[(start + i) % BUFFERSIZE] = temp[i];
    }

    printf("Buffer ordenado por prioridade.\n\n");    


}

void removeProc(void) {

    if (start == end) {
        printf("Buffer vazio.\n");
        return;
    }

    // Mostra estado do buffer antes de remover
    printf("----------------------------------\n");
    printf("Buffer: start=%d end=%d\n", start, end);
    printf("Removendo: '%s'\n", buffer[start].name);

    process atual = buffer[start];
    //int tmp = atual.func(); - letra a
    int tmp = execProc(buffer[start]);

    //printf("Retorno: %d\n", tmp); - letra a

    if (tmp == 0) {
        printf("Acao: CONCLUIDO\n");
        free(buffer[start].name);
        start = (start + 1) % BUFFERSIZE;
    }
    else if (tmp >= 1 && tmp <= 14) {
        printf("Acao: REAGENDAR %d vez(es)\n", tmp);
        free(buffer[start].name);
        start = (start + 1) % BUFFERSIZE;
        addProc(atual);
    }
    else if (tmp == 15) {
        printf("Acao: REAGENDAR INDEFINIDAMENTE\n");
        free(buffer[start].name);
        start = (start + 1) % BUFFERSIZE;
        addProc(atual);
    }

    // Mostra estado do buffer depois de remover
    printf("Buffer: start=%d end=%d\n", start, end);
    printf("----------------------------------\n\n");
}

/* =========================================================
 * printBuffer: Mostra estado atual do buffer
 * ========================================================= */
void printBuffer(void) {
    int count = (end - start + BUFFERSIZE) % BUFFERSIZE;

    printf("=== Estado do Buffer (%d processos) ===\n", count);
    for (int i = 0; i < count; i++) {
        int idx = (start + i) % BUFFERSIZE;
        printf("  [%d] '%s' | time=%d | priority=%d\n",
               idx,
               buffer[idx].name,
               buffer[idx].time,
               buffer[idx].priority);
    }
    printf("\n");
}

int func1(void) { printf("Executando func1\n"); return 0;  }
int func2(void) { printf("Executando func2\n"); return 3;  } // reagenda 3x
int func3(void) { printf("Executando func3\n"); return 15; } // indefinido

int main(void) {
    process p1 = {"Processo 1", 1, func1, 3};
    process p2 = {"Processo 2", 2, func2, 1};
    process p3 = {"Processo 3", 3, func3, 2};

    addProc(p1);
    addProc(p2);
    addProc(p3);
    
    printf("Antes\n");
    printBuffer();
    
    priorityBuffer();
    printf("Depois\n");
    printBuffer();

    removeProc();
    removeProc();
    removeProc();

    return 0;
}
