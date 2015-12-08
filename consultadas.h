#include "proximas.h"

//CONSTANTES
#define TAM_PALAVRA 20


typedef struct p_cons{
    char palavra[TAM_PALAVRA];
    int  freqA;
}P_CONS;

typedef struct cons{
  struct cons *esq;
  struct cons *dir;
  int FB;

  P_CONS inf;

  NO_PROX *viz;

}NO_CONS;



NO_CONS *inicializaCONS();

int alturaCONS(NO_CONS *);

int balanceamentoCONS(NO_CONS *);

void imprime_nivelCONS(NO_CONS *, int );

NO_CONS *rotacao_direitaCONS(NO_CONS *);

NO_CONS *rotacao_esquerdaCONS(NO_CONS *);

NO_CONS *rotacao_dupla_direitaCONS(NO_CONS *);

NO_CONS *rotacao_dupla_esquerdaCONS(NO_CONS *);

NO_CONS *caso1CONS(NO_CONS *, int *);

NO_CONS *caso2CONS(NO_CONS *, int *);

NO_CONS* insereCONS(NO_CONS *,NODO * , int *, NODO *);

NO_CONS *busca_palavras(NODO *, NODO *, NO_CONS *);

NO_CONS *calcula_estatCONS(NO_CONS *);

NO_PROX *calcula_estatPROX(int, NO_PROX *);



