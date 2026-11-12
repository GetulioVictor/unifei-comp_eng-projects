#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *ponteiro;
    char dados[64];
    char pilha[64];
} Secao;

typedef struct {
    char codigo[40];
    int duracao;
    int prioridade;
    Secao secao;
} Registro;

void somarEmA(int *A, int B) {
    *A = *A + B;
}

void exercicio1() {
    Registro registros[5];
    int i;

    printf("\n====== EXERCICIO 1: ESTRUTURAS DE DADOS ======\n\n");
    printf("=== CRIACAO DE REGISTROS ===\n\n");

    for (i = 0; i < 5; i++) {
        printf("Registro %d:\n", i + 1);

        printf("Codigo (max 40 letras): ");
        fgets(registros[i].codigo, sizeof(registros[i].codigo), stdin);
        registros[i].codigo[strcspn(registros[i].codigo, "\n")] = '\0';

        printf("Duracao (inteiro): ");
        scanf("%d", &registros[i].duracao);

        printf("Prioridade (inteiro): ");
        scanf("%d", &registros[i].prioridade);
        getchar();

        printf("Secao - Dados (max 64 letras): ");
        fgets(registros[i].secao.dados, sizeof(registros[i].secao.dados), stdin);
        registros[i].secao.dados[strcspn(registros[i].secao.dados, "\n")] = '\0';

        printf("Secao - Pilha (max 64 letras): ");
        fgets(registros[i].secao.pilha, sizeof(registros[i].secao.pilha), stdin);
        registros[i].secao.pilha[strcspn(registros[i].secao.pilha, "\n")] = '\0';

        registros[i].secao.ponteiro = registros[i].secao.dados;

        printf("\n");
    }

    printf("\n=== LEITURA DOS REGISTROS ===\n\n");

    for (i = 0; i < 5; i++) {
        printf("Registro %d:\n", i + 1);
        printf("  Codigo: %s\n", registros[i].codigo);
        printf("  Duracao: %d\n", registros[i].duracao);
        printf("  Prioridade: %d\n", registros[i].prioridade);
        printf("  Secao - Dados: %s\n", registros[i].secao.dados);
        printf("  Secao - Pilha: %s\n", registros[i].secao.pilha);
        printf("  Secao - Ponteiro aponta para: %s\n", registros[i].secao.ponteiro);
        printf("\n");
    }
}

void exercicio2() {
    int A, B;

    printf("\n====== EXERCICIO 2: FUNCAO COM MODIFICACAO DE PARAMETRO ======\n\n");

    printf("Digite o valor de A: ");
    scanf("%d", &A);

    printf("Digite o valor de B: ");
    scanf("%d", &B);

    printf("\n=== ANTES DA FUNCAO ===\n");
    printf("A = %d\n", A);
    printf("B = %d\n", B);

    somarEmA(&A, B);

    printf("\n=== APOS A FUNCAO ===\n");
    printf("A = %d\n", A);
    printf("B = %d\n", B);
}

int main() {
    int opcao;

    while (1) {
        printf("\n====== MENU PRINCIPAL ======\n");
        printf("1 - Exercicio 1: Estruturas de Dados\n");
        printf("2 - Exercicio 2: Funcao com Parametro\n");
        printf("3 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                exercicio1();
                break;
            case 2:
                exercicio2();
                break;
            case 3:
                printf("\nPrograma finalizado.\n");
                return 0;
            default:
                printf("\nOpcao invalida!\n");
        }
    }

    return 0;
}
