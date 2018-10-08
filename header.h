#ifndef LISTA_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


#define LISTA_H
#define MAX_NOME 100
#define MAX_DATA 11

// |ESTRUTURAS|

// Estrutura dos jogadores
typedef struct jogadores{
	char nome[MAX_NOME];			//nome do jogador
	int score;						//pontuação do jogador
	int npartidas;					//numero de partidas
	int prox;						
}jogador;

// Estrutura das partidas
typedef struct partidas{
	char nome1[MAX_NOME];			//jogadores da partida
	char nome2[MAX_NOME];
	int pontuacao1;					//pontuação dos jogadores
	int pontuacao2;
	int id;							//identificador da partida
	int prox;
}partida;

//estrutura dos torneios
typedef struct torneios{
	char nome[MAX_NOME];			//nome do torneio
	char local[MAX_NOME];			//local do torneio
	char data[MAX_DATA];			//data do torneio	
	struct partidas* p;				//ponteiro para as partidas do torneio
	int prox;
}torneio;

//estrutuda dos cabeçalhos
typedef struct cabecalhos{
	int pos_cabeca;					//posicao do inicio da lista
	int pos_topo;					//primeira posicao nao usada no fim do arquivo
	int pos_livre;					//posicao do inicio da lista de nos livres
}cabecalho;	

//le_cabecalho
cabecalho* le_cabecalho(FILE * arq);

//escreve_cabecalho
void escreve_cabecalho(FILE* arq, cabecalho* cab);

//cria_lista_vazia
void cria_lista_vazia(FILE* arq);

// Entrada: handle do arquivo binario (modo r) e a respectiva posição do jogador
// Retorno: estrutura de jogador
// Pré-condições: nenhum
// Pós-condições: retorna estrutura do jogador procurado
jogador* le_jogador(FILE* arq, int pos);
void escreve_jogador(FILE* arq, jogador* x, int pos);	//escreve jogador no arquivo
void insere_jogador_binario(FILE* arq, jogador* j);		//insere jogador no arquivo		
void insere_jogador(FILE *f);							//insere jogador novo no arquivo
void imprimir_jogadores(FILE* f);						//imprime a lista de jogadores na tela

// Entrada: handle do arquivo binario (modo r) e a respectiva posição da partida
// Retorno: estrutura de partida
// Pré-condições: nenhum
// Pós-condições: retorna estrutura da partida procurada
partida* le_partida(FILE* arq, int pos);
void escreve_partida(FILE* arq, partida* x, int pos);	//escreve partida no arquivo
void insere_partida_binario(FILE* arq, partida* p);		//insere partida no arquivo
void insere_partida(FILE *f);							//insere partida nova no arquivo
void imprimir_partidas(FILE* f);						//imprime a lista de partidas na tela

// Entrada: handle do arquivo binario (modo r) e a respectiva posição do torneio
// Retorno: estrutura de torneio
// Pré-condições: nenhum
// Pós-condições: retorna estrutura do torneio procurado
torneio* le_torneio(FILE* arq, int pos);
void escreve_torneio(FILE* arq, torneio* x, int pos);	//escreve torneio no arquivo
void insere_torneio_binario(FILE* arq, torneio* t);		//insere torneio no arquivo	
void insere_torneio(FILE *f);							//insere torneio novo no arquivo
void imprimir_torneios(FILE* f);						//imprime a lista de torenios na tela

// Entrada: handle do arquivo binario (modo r)
// Retorno: 1 ou 0
// Pré-condições: nenhum
// Pós-condições: jogador é removido do arquivo
void remove_jogador(FILE* arq);

// Entrada: handle do arquivo binario (modo r)
// Retorno: 1 se partida não foi removida ou 0 se foi removida
// Pré-condições: nenhum
// Pós-condições: partida é removida do arquivo
void remove_partida(FILE* arq);

// Entrada: handle do arquivo binario (modo r)
// Retorno: 1 se torneio não foi removido ou 0 se foi removido
// Pré-condições: nenhum
// Pós-condições: torneio é removido do arquivo
void remove_torneio(FILE* arq);

// |FUNÇÕES AUXILIARES|

int power(int x, int y); 					//eleva x a y

int strtodig(char* s, int l);				//transforma uma string em um numero

// Entrada: handle do arquivo binario (modo w) e o nome do arquivo texto
// Retorno: codigo de erro
// Pré-condições: arquivo deve estar aberto e deve ser um arquivo de lista
// Pós-condições: as informacoes do arquivo texto sao carregadas no arquivo binario
int inicializa(FILE *jogad,FILE *partid,FILE *tornei, char* txt);

#endif