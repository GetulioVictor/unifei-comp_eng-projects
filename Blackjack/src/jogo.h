#ifndef _Jogo_21_
#define _Jogo_21_

/*Colocamos todos os structs no arquivo .h pois estava gerando conflito com certas coisas na main.c
Além disso, colocamos os protótipos das funções que serão chamadas no main.c, outras funções essenciais estão no arquivo de implementação. */

/*Struct que armazena as variáveis correspondentes a informação de uma carta, sendo elas o seu valor e o seu naipe. Além disso armazena um struct carta *prox, que apontará para a próxima carta do baralho*/
typedef struct carta{
  int valor;
  int naipe;
  struct carta *prox;
}Carta;  
//elemento

/*No struct jogador armazenamos as informações dos jogadores que são relevantes para a rodada. Sendo ela a sua mão (as suas cartas), o total de cartas (no caso o valor dessas cartas combinadas), o número de cartas presentes em sua mão, e um struct jogador *prox que irá apontar para o próximo jogador*/

typedef struct jogador {
  struct carta *mao; 
  int total;
  int numCartas;
  struct jogador *prox;
}Jogador;

/*Nesse struct estão armazenadas as informações essenciais para que o jogo possa funcionar adequadamente. Esse struct armazena um struct carta *baralho (isto é o baralho propriamente dito), um struct jogador *jogadores (armazena a lista de jogadores da partida), o número de jogadores na partida, e o jogador da rodada que corresponde ao vencedor da rodada*/

typedef struct sessaoDeJogo {
  struct carta *baralho;
  struct jogador *jogadores; //lista de jogadores
  int numeroDeJogadores; 
  int jogadorDaRodada; 
}SessaoDeJogo;


void GeraMatriz(int matriz[4][10], int quantidadeNaipes, int quantidadeValores);

Carta* CriarBaralho();
Carta *CriarCarta(int valor, int naipe);
Jogador *CriarJogadores();
Jogador *CriarJogador(Carta *mao, int total, int numCartas);
Carta *CriaMao(int naipe, int valor);

Carta *GerarBaralhoEmbaralhado();
Jogador *IncluirJogador(Jogador *jogadores, Carta *mao);
Carta *InserirNoTopo(Carta *baralho, int valor, int naipe);
Carta *ComprarCarta(Carta *baralho, int *valorCarta, int *naipeCarta);

int Libera_Cartas(Carta *cartas);
int Libera_Jogadores(Jogador *player);
int Libera_Sessao_de_Jogo(SessaoDeJogo *Jogo);


void ImprimirBaralho(Carta *baralho);
void ImprimirMatriz(int matriz[4][10]);

SessaoDeJogo *IniciarJogo(int numeroDeJogadores);

#endif
