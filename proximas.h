#include "fileread.h"

//CONSTANTES
#define TAM_PALAVRA 20

typedef struct prox_palavra{
  char palav[TAM_PALAVRA];
  int  freqAB;
  int  freqB;
  double stat;
}PROX_PALAVRA;

typedef struct prox{
  struct prox *esq;
  struct prox *dir;
  int FB;
  PROX_PALAVRA inf;
}NO_PROX;




NO_PROX *inicializaPROX();

int alturaPROX(NO_PROX *);

int balanceamentoPROX(NO_PROX *);

void imprime_nivelPROX(NO_PROX *, int );

NO_PROX *rotacao_direitaPROX(NO_PROX *);

NO_PROX *rotacao_esquerdaPROX(NO_PROX *);

NO_PROX *rotacao_dupla_direitaPROX(NO_PROX *);

NO_PROX *rotacao_dupla_esquerdaPROX(NO_PROX *);

NO_PROX *caso1PROX(NO_PROX *, int *);

NO_PROX *caso2PROX(NO_PROX *, int *);

NO_PROX* inserePROX(NO_PROX *,NODO * , int *, NODO *);
