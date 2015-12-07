/* TAD_AVL - LEONARDO MARQUES RODRIGUES
PORTO ALEGRE 07/12/2015
COMPILADO EM SO UBUNTU 64bits */

#include <stdio.h>
#include <stdlib.h>
#include "abp.h"

NO *inicializa(){
    return NULL;
}

//A função recebe um valor, e cria um nodo
NO *novoNODO(int num){
    NO *aux;
    aux = (NO*)malloc(sizeof(NO));
    aux->info.num = num;
    aux->alt = 0;
    aux->dir = NULL;
    aux->esq = NULL;

    return aux;
}


int insere(NO **raiz, int num){
  int rtrn;
  NO *aux;

  if(*raiz == NULL){
    *raiz = novoNODO(num);
    rtrn = 1;
  }else{
    
    aux = *raiz;

    //Necessita inserção à esquerda
    if(num < aux->info.num){
      rtrn = insere(&(aux->esq), num);
      if(rtrn){
	if(balanceamento(aux) > 1){
	  if(num < (*raiz)->esq->info.num){
	    *raiz = rotacaoDIR(*raiz);
	  }
	  else{
	    *raiz = rotacaoDuplaDIR(*raiz);
	  }
	}
      }
    }

    //Necessita inserção à direita
    else{
      if(num > aux->info.num){
	rtrn = insere(&(aux->esq), num);
	if(rtrn){
	  if(balanceamento(aux) > 1){
	    if((*raiz)->dir->info.num < num){
	      *raiz = rotacaoESQ(*raiz);
	    }
	    else{
	      *raiz = rotacaoDuplaESQ(*raiz);
	    }
	  }
	}
      }
      else{
	printf("Valor Duplicado!!");
	rtrn = 0;
      }
    }
  }

  aux->alt = maior(alturaNO(aux->esq),
		      alturaNO(aux->dir)) + 1;
  
  return rtrn;
}

void imprime(NO *raiz){

    //Condição de parada
    if(raiz != NULL){
        printf("%d\n", raiz->info.num);

        imprime(raiz->esq);
        imprime(raiz->dir);

    }
}


int no_counter(NO* raiz){

    //Condição de parada
    if(raiz != NULL){
        return 1 + no_counter(raiz->esq) + no_counter(raiz->dir);

    }
}

void imprime_nivel(NO *raiz, int cont){
    int i;

    //Condição de parada
    if(raiz != NULL){
        for(i=0;i <= cont;i++){
            printf("=");
        }
        printf("%d\n", raiz->info.num);
        if(raiz->esq != NULL){
            imprime_nivel(raiz->esq, cont+1);
        }
        if(raiz->dir != NULL){
            imprime_nivel(raiz->dir, cont+1);
        }
    }
}


int alturaNO(NO *no){
  int rtrn;

  if(no ==NULL){
    rtrn = -1;
  }
  else
    rtrn =  no->alt;
 
 return rtrn;

}

int balanceamento(NO *no){
  int rtrn;

  rtrn = labs(alturaNO(no->esq) - alturaNO(no->dir));

  return rtrn;
}

int maior(int x, int y){
  int rtrn;

  if(x > y)
    rtrn = x;
  else
    rtrn = y;

  return rtrn;

}


NO *rotacaoDIR(NO *raiz){ //LL
  NO *aux;
  
  aux = raiz->esq;
  raiz->esq = aux->dir;
  aux->dir = raiz;

  raiz->alt = maior(alturaNO(raiz->esq), alturaNO(raiz->dir)) +1;
  aux->alt = maior(alturaNO(aux->esq), raiz->alt) +1;

  raiz = aux;

  return raiz;

}

NO *rotacaoESQ(NO *raiz){ //RR
  NO *aux;
  
  aux = raiz->dir;
  raiz->dir = aux->esq;
  aux->esq = raiz;

  raiz->alt = maior(alturaNO(raiz->esq), alturaNO(raiz->dir)) +1;
  aux->alt = maior(alturaNO(aux->dir), raiz->alt) +1;

  raiz = aux;

  return raiz;

}

NO *rotacaoDuplaDIR(NO *raiz){ //LR
  
  raiz = rotacaoESQ(raiz->esq);
  raiz = rotacaoDIR(raiz);

  return raiz;
}


NO *rotacaoDuplaESQ(NO *raiz){ //RL
  
  raiz = rotacaoDIR(raiz->dir);
  raiz = rotacaoESQ(raiz);

  return raiz;
}
