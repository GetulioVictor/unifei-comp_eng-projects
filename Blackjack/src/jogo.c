#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jogo.h"

/*Função que gera a matriz que armazena o valor e naipe de cada carta*/
void GeraMatriz(int matriz[4][10], int quantidadeNaipes, int quantidadeValores) {
  int i, j;
  for(i = 0; i < quantidadeNaipes; i++) {
    for(j = 0; j < quantidadeValores; j++) {
      matriz[i][j] = j + 1;
    }
  }
}

/* //visualizar se os valores foram alocados corretamente
void ImprimirMatriz(int matriz[4][10]) {
  int i, j;
  for(i = 0; i < 4; i++) {
    for(j = 0; j < 10; j++) {
   
   printf("%d ", matriz[i][j]);
    }
    printf("\n");
  }
} */

/*-----Funções de Alocação de Memória-----*/

//Aloca memória e cria o baralho (lista de cartas)
Carta *CriarBaralho() { 
  Carta *baralho = (Carta*) malloc (sizeof(Carta));
  if(baralho != NULL)
    baralho = NULL;
  
  return baralho;
}

//Cria uma carta e atribui um valor e naipe para ela
Carta *CriarCarta(int valor, int naipe) {
  Carta *novaCarta = (Carta*) malloc(sizeof(Carta));
  novaCarta->naipe = naipe; //recebe o naipe predefinido na matriz
  novaCarta->valor = valor; //recebe o valor predefinido na matriz
  novaCarta->prox = NULL;
  return novaCarta;
}

//Cria os jogadores (Lista de Jogadores)
Jogador *CriarJogadores() {
  Jogador *novoJogador = (Jogador*) malloc (sizeof(Jogador));
  if(novoJogador != NULL)
    novoJogador = NULL;
  
  return novoJogador;
}

//Cria um jogador
Jogador *CriarJogador(Carta *mao, int total, int numCartas) {
  Jogador *novoJogador = (Jogador*) malloc(sizeof(Jogador));
  novoJogador->total = total; //novoJogador recebe o total de cartas(valor) 
  novoJogador->numCartas = numCartas; //número de cartas
  novoJogador->mao = mao;   //mão do jogador
  return novoJogador;
}

//Cria a mão do jogador
Carta *CriaMao(int naipe, int valor) {
  Carta *mao = (Carta*) malloc(sizeof(Carta));
  mao->valor = valor; 
  mao->naipe = naipe;
  mao->prox = NULL;
  
  return mao;
}

/*-----Embaralhar-----*/
Carta *GerarBaralhoEmbaralhado() {
  Carta *novoBaralho = CriarBaralho();
  int matriz[4][10];
  GeraMatriz(matriz, 4, 10); //chamamos a matriz com os valores pre-definidos
  srand((unsigned)time(NULL)); //função que gera valores aleatórios

  int numeroDeCartas = 0;
  while(numeroDeCartas < 40) {
    int naipe = rand() % 4; //gera um naipe aleatório
    int valor = (rand() % 10); //gera o valor das cartas aleatoriamente
    if(matriz[naipe][valor] > 0) {
      novoBaralho = InserirNoTopo(novoBaralho, valor, naipe); //insere as cartas novamente no baralho
      numeroDeCartas++; //aumenta a quantidade de cartas no baralho
      matriz[naipe][valor] = 0; //atribui o valor 0 às cartas de valor x e naipe y já usados
    }
  }
  return novoBaralho;
}

/*-----Comprar Carta-----*/
//Retira a carta do baralho e retorna ela

/*
anterior    aux (atual)
primeiro -> segundo -> terceiro -> null

            anterior    aux(atual)
primeiro -> segundo -> terceiro -> null

                      anterior    aux(atual)
primeiro -> segundo -> terceiro -> null
*/

Carta *ComprarCarta(Carta *baralho, int *valorCarta, int *naipeCarta) {
  if(baralho == NULL) { //baralho vazio retorna vazio
    return NULL;
  }
  Carta *anterior = baralho; //início do baralho/lista
  Carta *auxiliar = anterior->prox; //auxiliar armazena para onde o anterior aponta
  while(auxiliar->prox != NULL) { //enquanto o próximo elemento não apontar para NULL
    anterior = auxiliar; //anterior recebe/aponta para auxiliar
    auxiliar = auxiliar->prox; //o auxiliar recebe o próximo elemento (nó seguinte)
  }
  anterior->prox = NULL; //novo ultimo elemento aponta para NULL
  *valorCarta = auxiliar->valor;
  *naipeCarta = auxiliar->naipe;
  free(auxiliar);
  return baralho; //passar o valor e o naipe 
}

/*-----Inserir Jogadores na Partida-----*/
Jogador *IncluirJogador(Jogador *jogadores, Carta *mao) {
  Jogador *aux;
  Jogador *novoJogador = CriarJogador(mao, mao->valor, 1);
  if(jogadores == NULL) //rodada sem jogadores
      return novoJogador; //novo jogador vira a lista de jogadores
  else {
    aux = jogadores; 
    while(aux->prox != NULL) { //percorre toda a lista de jogadores
        aux = aux->prox;

    }
    aux->prox = novoJogador; //insere um novo jogador na lista de jogadores
  } 
  return jogadores;
}

/*-----Inserir as cartas no baralho-----*/
Carta *InserirNoTopo(Carta *baralho, int valor, int naipe) {
  Carta *aux; //criamos o auxiliar para não perder a referência do início do baralho
  Carta *novaCarta = CriarCarta(valor, naipe);
  if(baralho == NULL) //se o baralho estiver vazio
      return novaCarta; //Primeira carta do baralho
  else {
    aux = baralho; 
    while(aux->prox != NULL) { //percorre todas as cartas do baralho
        aux = aux->prox;

    }
    aux->prox = novaCarta; //recebe nova carta
  } 
  return baralho;
}

/*-----Imprimir Baralho----*/
/* 
//Visualizar se as cartas foram colocadas adequadamente no baralho
void ImprimirBaralho(Carta *baralho) {
  Carta *aux = baralho; // *aux recebe o endereço do início da baralho
  char naipes[4][10] = {"Copas", "Ouro", "Espada", "Paus"}; //Posição (linhas) 0,1,2,3 respectivamente
  while(aux != NULL ) {
    printf(" %d de %s\n", aux->valor, naipes[aux->naipe]); //valor e naipe
    aux = aux->prox; //passa para o próximo elemento
  }
}
*/

/*-----Iniciar Jogo-----*/
/*
Cria a sessão de jogo, para isso é preciso embaralhar as cartas, criar a lista de jogadores, 
*/
SessaoDeJogo *IniciarJogo(int numeroDeJogadores) {
    Carta *baralho = GerarBaralhoEmbaralhado();
    Jogador *jogadores = CriarJogadores();
    int i;
    for(i = 0; i < numeroDeJogadores; i++) {
      int valor, naipe;
      baralho = ComprarCarta(baralho, &valor, &naipe);  //removo a carta do topo par adicionar a carta na mao do jogador
      Carta *carta = CriarCarta(valor, naipe);
      jogadores = IncluirJogador(jogadores, carta); //inclui o jogador na lista de jogadores, i.e, na rodada.
    }
    SessaoDeJogo *sessao = (SessaoDeJogo *) malloc(sizeof(SessaoDeJogo));
    sessao->baralho = baralho;
    sessao->jogadores = jogadores;
    sessao->numeroDeJogadores = numeroDeJogadores;
    sessao->jogadorDaRodada = 0;
    
    return sessao;
}

/*-----Funções de Liberação de Memória-----*/

/* Temos a opção de liberar a memória na seguinte ordem:  1° Mão - 2° Jogadores 3° Cartas 4° Baralho 5° Sessão. Porém optamos por liberar as cartas, os jogadores e a sessão de jogo. Pois a mão do jogador pode constituir todas as cartas presentes no jogo (isso se não houver alguma condição que impeça isso), ao liberar somente as cartas consequentemente deixamos o baralho e a mão do jogador vazios, isto é, a memória atribuida para o baralho e a mão do jogador é liberada.
Liberar cartas = liberar mao do jogador = liberar baralho
*/

int Libera_Cartas(Carta *cartas) {
  if(cartas == NULL) {
    return 0;
  }

  Carta *aux;
  while(cartas != NULL) {
    aux = cartas;
    cartas = cartas->prox;
    free(aux);
  }
  free(cartas);
  return 1;
}

//libera a lista de jogadores
int Libera_Jogadores(Jogador *player) {
  if(player == NULL) {
      return 0;
  }
  int resultado;
  Jogador *aux;
  while(player != NULL) {
      aux = player;
      Libera_Cartas(aux->mao);
      player = player->prox;
      free(aux);
  }
  free(player);
  return 1;
}

int Libera_Sessao_de_Jogo(SessaoDeJogo *sessao) {
  if (sessao == NULL) {
    return 0;
  }
  Libera_Jogadores(sessao->jogadores);
  Libera_Cartas(sessao->baralho);
 
  free(sessao);
  return 1; 
}
