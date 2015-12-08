#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "consultadas.h"


NO_CONS *inicializaCONS(){
  return NULL;
}

int alturaCONS(NO_CONS *raiz){
  int alt_esq, alt_dir, rtrn;

  if (raiz == NULL){
    rtrn = 0;
  }
  else{

    alt_esq = alturaCONS(raiz->esq);
    alt_dir = alturaCONS(raiz->dir);

    if (alt_esq > alt_dir){
      rtrn = (1 + alt_esq);
    }
    else{
      rtrn = (1 + alt_dir);
    }
  }

  return rtrn;
}

int balanceamentoCONS(NO_CONS *raiz){
  return (alturaCONS(raiz->esq) - alturaCONS(raiz->dir));
}

void imprime_nivelCONS(NO_CONS *raiz, int cont){
    int i;

    if(raiz != NULL){
        for(i=0;i <= cont;i++){
            printf("=");
        }
        printf(" %s / freq: %d \n", raiz->inf.palavra, raiz->inf.freqA);
	printf("\n");
	imprime_nivelPROX(raiz->viz,i);
	printf("\n");
        if(raiz->esq != NULL){
            imprime_nivelCONS(raiz->esq, cont+1);
        }
        if(raiz->dir != NULL){
            imprime_nivelCONS(raiz->dir, cont+1);
        }
    }
}

NO_CONS *rotacao_direitaCONS(NO_CONS *raiz){
   NO_CONS *aux;

   aux = raiz->esq;
   raiz->esq = aux->dir;
   aux->dir = raiz;

   raiz->FB = 0;
   raiz = aux;

   return raiz;
}

NO_CONS *rotacao_esquerdaCONS(NO_CONS *raiz){
   NO_CONS *aux;

   aux = raiz->dir;
   raiz->dir = aux->esq;
   aux->esq = raiz;

   raiz->FB = 0;
   raiz = aux;

   return raiz;
}

NO_CONS *rotacao_dupla_direitaCONS(NO_CONS *raiz){
  NO_CONS *aux, *aux1;

  aux = raiz->esq;
  aux1 = aux->dir;

  aux->dir = aux1->esq;
  aux1->esq = aux;

  raiz->esq = aux1->dir;
  aux1->dir = raiz;

  if (aux1->FB == 1){
    raiz->FB = -1;
  }
  else{
    raiz->FB = 0;
  }
  if (aux1->FB == -1){
    aux->FB = 1;
  }
  else{
    aux->FB = 0;
  }

  raiz = aux1;

  return raiz;
}

NO_CONS *rotacao_dupla_esquerdaCONS(NO_CONS *raiz){
   NO_CONS *aux, *aux1;

   aux = raiz->dir;
   aux1 = aux->esq;

   aux->esq = aux1->dir;
   aux1->dir = aux;

   raiz->dir = aux1->esq;
   aux1->esq = raiz;

   if (aux1->FB == -1){
     raiz->FB = 1;
   }
   else{
     raiz->FB = 0;
   }
   if (aux1->FB == 1){
     aux->FB = -1;
   }
   else{
     aux->FB = 0;
   }

   raiz = aux1;

   return raiz;
}

NO_CONS *caso1CONS(NO_CONS *raiz , int *ok){
  NO_CONS *aux;

  aux = raiz->esq;

  if (aux->FB == 1){
    raiz = rotacao_direitaCONS(raiz);
  }
  else{
    raiz = rotacao_dupla_direitaCONS(raiz);
  }

  raiz->FB = 0;
  *ok = 0;

  return raiz;
}

NO_CONS *caso2CONS(NO_CONS *raiz , int *ok){
  NO_CONS *aux;

  aux = raiz->dir;

  if (aux->FB == -1){
    raiz=rotacao_esquerdaCONS(raiz);
  }
  else{
    raiz=rotacao_dupla_esquerdaCONS(raiz);
  }

  raiz->FB = 0;
  *ok = 0;

  return raiz;
}

NO_CONS* insereCONS(NO_CONS *raiz, NODO *palavra, int *ok, NODO *texto){
  int aux;

  if (raiz == NULL){
    raiz = (NO_CONS*) malloc(sizeof(NO_CONS));
    if(raiz == NULL){
      printf("Memória Insuficiente!");
      *ok = 0;
    }
    else{      
      strcpy(raiz->inf.palavra,palavra->inf.p);
      raiz->inf.freqA = 1;

      raiz->esq = NULL;
      raiz->dir = NULL;
      raiz->FB = 0;

      raiz->viz = inicializaPROX();
      raiz->viz = inserePROX(raiz->viz, palavra->next, &aux, texto);

      *ok = 1;
    }
  }

  else{
    if (strcmp(palavra->inf.p,raiz->inf.palavra) < 0){
      raiz->esq = insereCONS(raiz->esq,palavra,ok,texto);
      if (*ok){
	switch(raiz->FB){
	case -1:
	  raiz->FB = 0;
	  *ok = 0;
	  break;
	case  0:
	  raiz->FB = 1;
	  break;
	case  1:
	  raiz=caso1CONS(raiz,ok);
	  break;
	}
      }
    }

    else{
      if(strcmp(palavra->inf.p,raiz->inf.palavra) > 0){
	raiz->dir = insereCONS(raiz->dir,palavra,ok,texto);
	if (*ok){
	  switch(raiz->FB){
	  case  1:
	    raiz->FB = 0;
	    *ok = 0;
	    break;
	  case  0:
	    raiz->FB = -1;
	    break;
	  case -1:
	    raiz = caso2CONS(raiz,ok);
	    break;
	  }
	}
      }

      else{
	raiz->inf.freqA++;
	raiz->viz = inserePROX(raiz->viz, palavra->next, &aux, texto);
	//INSERIR A PALAVRA VIZINHA NAS PRÓXIMAS
	*ok = 0;
      }
    }
  }

  return raiz;
}



//FUNÇÃO QUE APLICA A INSERÇÃO EM TODAS AS CONSULTADAS
//FUNÇÃO QUE PEGA UMA CONSULTADA E CONSULTA NO TEXTO, APÓS INSERE NA ESTRUTURA
NO_CONS *busca_palavras(NODO *texto, NODO *consultas, NO_CONS *busca)
{

  NODO *aux_texto, *aux_consultas = consultas;
  int ok=0;
  while(aux_consultas != NULL){
    aux_texto = texto;

    while(aux_texto != NULL){
      
      if(strcmp(aux_texto->inf.p,aux_consultas->inf.p)==0){
	busca = insereCONS(busca,aux_texto,&ok,texto);
	//printf("%s \n",aux_texto->inf.p);
      }
      aux_texto = aux_texto->next;
    }
    aux_consultas = aux_consultas->next;
  }

  return busca;

}


NO_CONS *calcula_estatCONS(NO_CONS *raiz){

  if(raiz != NULL){

    raiz->viz = calcula_estatPROX(raiz->inf.freqA, raiz->viz);

    raiz->esq = calcula_estatCONS(raiz->esq);
    raiz->dir = calcula_estatCONS(raiz-dir);

  }
}



NO_PROX *calcula_estatPROX(int freqA, NO_PROX *proximas){
  
  if(raiz != NULL){

    raiz->inf.stat = raiz->inf.freqAB / sqrt(freqA * raiz->inf.freqB);
    
    raiz->esq = calcula_estatPROX(freqA, raiz-esq);
    raiz->dir = calcula_estatPROX(freqA, raiz-dir);


  }





}
