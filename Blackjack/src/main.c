#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "jogo.h"

typedef struct Usuario{
  char nome[30]; //nome[30]
  int pontuacao;
  Jogador *jogador; //um jogador da sessao
}Usuario;


int Salvar_Dados(Usuario *usuarios, int quantidadeJogadores, FILE *file) { //receber pontuacao
  int i=0;
  if(usuarios == NULL) {
    return 0;
  }
  file = fopen("info.txt" , "w+");
  if (file == NULL) {
    printf("\nErro ao abrir o arquivo");
    exit(1);
  }
  for(i = 0; i < quantidadeJogadores; i++) {
    fprintf(file, "Jogador %d: %s\n" , i + 1, usuarios[i].nome);
    fprintf(file, "Pontuação jogador %d: %d\n\n" , i + 1, usuarios[i].pontuacao);
  }

  fclose(file);
  return 1;
}

Usuario *CriarUsuario(char *nome) {
  Usuario *novoUsuario = (Usuario*) malloc(sizeof(Usuario));
  char* novoNome = (char*) malloc(sizeof(strlen(nome) + 1));
  strcpy(novoNome, nome);
  strcpy(novoUsuario->nome, novoNome);
  
  novoUsuario->pontuacao = 0;
  novoUsuario->jogador = NULL;
  
  return novoUsuario;
}

int main(void) {
   //Inicia o jogo com 2 jogadores
  
  Usuario *usuarios;
  FILE *fi;
  int numeroDeJogadores, ok, opcao, i, valor, naipe, vencedor;
  bool encerrar = false, perdeu = false;
  char nome[30];
  char nomeVencedor[30];
  int totalVencedor = 0;
  char nome1[30], c;
  int points;
  SessaoDeJogo *sessao = NULL;

  do{
    //Menu de opções
    printf("\n----Opções----\n");
    printf("\n1 - Iniciar jogo");
    printf("\n2 - Exibir Regras"); 
    printf("\n3 - Exibir pontuação dos jogadores"); //somente se já foi finalizado um jogo
    printf("\n4 - Encerrar o jogo"); //Para de jogar

    printf("\nOpção: ");
    scanf(" %d" , &opcao);
    system("clear");
    
    switch(opcao) {
        case 1:
  
        printf("\nDigite o número de jogadores: ");
        scanf("%d" , &numeroDeJogadores);

        sessao = IniciarJogo(numeroDeJogadores);

		    usuarios = (Usuario*)malloc(sizeof(Usuario) * numeroDeJogadores);
        Jogador *jogadores = sessao->jogadores;
        for(i = 0; i < numeroDeJogadores;i++) {
            printf("\nDigite o nome do jogador %d: ", i + 1);
            scanf(" %[^\n]s" , nome);
            Usuario *novoUsuario;  
            novoUsuario = CriarUsuario(nome);
            novoUsuario->jogador = jogadores;
      			usuarios[i] = *novoUsuario;
            jogadores = jogadores->prox;
          }

          //escreve as informações em arquivo
          //Salvar_Dados(usuarios, nome, numeroDeJogadores, fi);
        for(i = 0; i < numeroDeJogadores; i++) {
          
          encerrar = false;
          perdeu = false;

          while(true) {
            //Menu de opções
            printf("\nVez do Jogador %d, Usuário %s", i + 1, usuarios[i].nome);
            printf("\n----Opções----\n");
            printf("\n1 - Comprar Carta");
            printf("\n2 - Parar");
            printf("\n3 - Exibir Regras"); 
            printf("\nOpção: ");
            scanf(" %d" , &opcao);
            system("clear");
            switch(opcao) {
              case 1:
                  sessao->baralho = ComprarCarta(sessao->baralho, &valor, &naipe);
                  usuarios[i].jogador->mao = InserirNoTopo(usuarios[i].jogador->mao, valor, naipe);
                  usuarios[i].jogador->total += valor;
                  usuarios[i].jogador->numCartas += 1;
                  if(usuarios[i].jogador->total > 21) {
                    printf("\nUsuário %s eliminado! Atingiu %d pontos.\n", usuarios[i].nome, usuarios[i].jogador->total);
                    perdeu = true;
                  }
                  else if(usuarios[i].jogador->total == 21) {
                    printf("\nParabéns %s! Você ganhou! Sua pontuação foi %d.\n", usuarios[i].nome, usuarios[i].jogador->total);

                  }
                  else {
                    printf("Usuário %s\nTotal: %d\n", usuarios[i].nome, usuarios[i].jogador->total);
                  }
                break;
              case 2:
                break;
              case 3:
                //Regras
                printf("\n----- Regras ------\n");
                printf("\nO total de cartas em uma mão não pode exceder o valor 21\n");
                printf("\nSe nenhum jogador atingir o valor 21 não há vencedores\n");
                printf("\nNa 1ª rodada o jogador recebe uma carta de valor aleatório\n");
                printf("\nGanha o jogador que atingir a soma dos valores, presentes em cada carta, igual a 21\n");
          
                break;
              case 4:
                encerrar = true;
                opcao = 4;
                break;
            }
            if(usuarios[i].jogador->total == 21) {
              vencedor = i;
              break;
            }
            else if(opcao == 2 || encerrar || perdeu) {
              break;
            }
          }
          if(usuarios[i].jogador->total == 21) {
            vencedor = i;
            break;
          }
          if(encerrar) {
            break;
          }
        }
        for(i = 0; i < numeroDeJogadores; i++) {
          if(usuarios[i].jogador->total <= 21 && usuarios[i].jogador->total > totalVencedor){
            strcpy(nomeVencedor, usuarios[i].nome);
            totalVencedor = usuarios[i].jogador->total;
          }
        }
        if(totalVencedor == 0) {
          printf("\nNão houve vencedor! Todos ultrapassaram 21.\n");
        }
        else if(totalVencedor < 21) {
          printf("\nParabéns usuário %s! Você ganhou a partida com o total %d!", nomeVencedor, totalVencedor);
        }
        for(i = 0; i < numeroDeJogadores; i++) {
          if(usuarios[i].jogador->total == totalVencedor){
            usuarios[i].pontuacao += 1;
          }
        }
        Salvar_Dados(usuarios, numeroDeJogadores, fi);
        
        break;

        case 2: 
        //Regras

        printf("\n----- Regras ------\n");
        printf("\nO total de cartas em uma mão não pode exceder o valor 21\n");
        printf("\nSe nenhum jogador atingir o valor 21 não há vencedores\n");
        printf("\nNa 1ª rodada o jogador recebe uma carta de valor aleatório\n");
        printf("\nGanha o jogador que atingir a soma dos valores, presentes em cada carta, igual a 21\n");

        break;
        case 3:
        
          fi = fopen("info.txt" , "r");  
          if(fi == NULL) {
            printf("\nErro");
            exit(1);
            break;
          }
        c = fgetc(fi);
        do
        {    
            //faz a leitura do caracter no arquivo apontado por fi
            printf("%c" , c);    
            c = fgetc(fi);
            //exibe o caracter lido na tela
            
        }while (c != EOF);

        fclose(fi);
        break;

        case 4:
          //Não acontece nada, e sai do laço while, pois opção igual a 4.
        break;

    }
    if(opcao == 4) {
      ok = Libera_Sessao_de_Jogo(sessao);
          if(ok == 1) {
            printf("\nEncerrando...");
          }
          else{
            printf("\nErro ao encerrar o jogo!");
          }
    }
  }while(opcao!=4);

  
  return 0;
}
