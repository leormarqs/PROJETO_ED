#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proximas.h"


NO_PROX *inicializaPROX(){
    return NULL;
}

int alturaPROX(NO_PROX *raiz){
  int alt_esq, alt_dir, rtrn;

  if (raiz == NULL){
    rtrn = 0;
  }
  else{
    
    alt_esq = alturaPROX(raiz->esq);
    alt_dir = alturaPROX(raiz->dir);
    
    if (alt_esq > alt_dir){
      rtrn = (1 + alt_esq);
    }
    else{
      rtrn = (1 + alt_dir);
    }
  }

  return rtrn;
}

int balanceamento(NO_PROX *raiz){
  return (alturaPROX(raiz->esq) - alturaPROX(raiz->dir));
}

void imprime_nivelPROX(NO_PROX *raiz, int cont){
    int i;
    
    //Condição de parada
    if(raiz != NULL){
        for(i=0;i <= cont;i++){
            printf("=");
        }
        printf(" %s / freq AB: %d, freqB: %d, Estatística: %f\n", raiz->inf.palav, raiz->inf.freqAB,raiz->inf.freqB,raiz->inf.stat);
        if(raiz->esq != NULL){
            imprime_nivelPROX(raiz->esq, cont+1);
        }
        if(raiz->dir != NULL){
            imprime_nivelPROX(raiz->dir, cont+1);
        }
    }
}

NO_PROX *rotacao_direitaPROX(NO_PROX *raiz){
   NO_PROX *aux;

   aux = raiz->esq; 
   raiz->esq = aux->dir; 
   aux->dir = raiz; 

   raiz->FB = 0;
   raiz = aux; 

   return raiz;
}

NO_PROX *rotacao_esquerdaPROX(NO_PROX *raiz){
   NO_PROX *aux;

   aux = raiz->dir; 
   raiz->dir = aux->esq; 
   aux->esq = raiz; 

   raiz->FB = 0;
   raiz = aux; 

   return raiz;
} 

NO_PROX *rotacao_dupla_direitaPROX(NO_PROX *raiz){
  NO_PROX *aux, *aux1;
  
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

NO_PROX *rotacao_dupla_esquerdaPROX(NO_PROX *raiz){
   NO_PROX *aux, *aux1;

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

NO_PROX *caso1PROX(NO_PROX *raiz , int *ok){
  NO_PROX *aux; 

  aux = raiz->esq;

  if (aux->FB == 1){    
    raiz = rotacao_direitaPROX(raiz);
  }
  else{
    raiz = rotacao_dupla_direitaPROX(raiz);
  }
	
  raiz->FB = 0;
  *ok = 0;
  
  return raiz;
}

NO_PROX *caso2PROX(NO_PROX *raiz , int *ok){
  NO_PROX *aux; 
  
  aux = raiz->dir;

  if (aux->FB == -1){
    raiz=rotacao_esquerdaPROX(raiz);
  }
  else{
    raiz=rotacao_dupla_esquerdaPROX(raiz);
  }
  
  raiz->FB = 0;
  *ok = 0;

  return raiz;
}

NO_PROX* inserePROX(NO_PROX *raiz, NODO *palavra, int *ok, NODO *texto){

  if (raiz == NULL){
    raiz = (NO_PROX*) malloc(sizeof(NO_PROX));
    if(raiz == NULL){
      printf("Memória Insuficiente!");
      *ok = 0;
    }
    else{  
      strcpy(raiz->inf.palav,palavra->inf.p);
      raiz->inf.freqAB = 1;
      raiz->inf.freqB = freq_palav(texto, palavra->inf.p); 
      //CONTA A FREQUENCIA DA PALAVRA NO TEXTO DE ORIGEM
      raiz->inf.stat = 0;
      
      raiz->esq = NULL;
      raiz->dir = NULL;
      raiz->FB = 0; 
      
      *ok = 1;
    }
  }
  else{
    if (strcmp(palavra->inf.p,raiz->inf.palav) < 0){
      raiz->esq = inserePROX(raiz->esq,palavra,ok,texto);      
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
	    raiz=caso1PROX(raiz,ok);
	    break;
	}
      }
    }

    else{
      if(strcmp(palavra->inf.p,raiz->inf.palav) > 0){
	raiz->dir = inserePROX(raiz->dir,palavra,ok,texto);
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
	      raiz = caso2PROX(raiz,ok);
	      break;
	  }
	}
      }

      else{
	raiz->inf.freqAB++;
	*ok = 0;
      }
    }
  }

  return raiz;
}

