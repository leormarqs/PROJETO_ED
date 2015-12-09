/* 
   TAD RESPONSÁVEL POR ARMAZENAR AS PALAVRAS DE CO-OCORRÊNCIA
   PARA CADA PALAVRA PESQUISADA EM UMA AVL
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "proximas.h"

//INICIALIZA UMA AVL
NO_PROX *inicializaPROX(){
    return NULL;
}

//CALCULA A ALTURA DE UM NODO
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

//CALCULA O BALANCEAMENTO DE UMA ARVORE
int balanceamento(NO_PROX *raiz){
  return (alturaPROX(raiz->esq) - alturaPROX(raiz->dir));
}

//IMPRIME A ARVORE DEMARCANDO OS NIVEIS DO NODO
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

//APLICA ROTAÇÃO A DIREITA EM UM NODO
NO_PROX *rotacao_direitaPROX(NO_PROX *raiz){
   NO_PROX *aux;

   aux = raiz->esq; 
   raiz->esq = aux->dir; 
   aux->dir = raiz; 

   raiz->FB = 0;
   raiz = aux; 

   return raiz;
}

//APLICA ROTAÇÃO A ESQUERDA EM UM NODO
NO_PROX *rotacao_esquerdaPROX(NO_PROX *raiz){
   NO_PROX *aux;

   aux = raiz->dir; 
   raiz->dir = aux->esq; 
   aux->esq = raiz; 

   raiz->FB = 0;
   raiz = aux; 

   return raiz;
} 

//APLICA ROTAÇÃO DUPLA DIREITA EM UM NODO
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

//APLICA ROTAÇÃO DUPLA ESQUERDA EM UM NODO
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

//VERIFICA NECESSIDADE DE ROTAÇÃO
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

//VERIFICA NECESSIDADE DE ROTAÇÃO
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

//INSERE UMA PALAVRA EM UMA AVL COM CHAVE PELA ORDEM ALFABETICA
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
      //CONTA A FREQUENCIA DA PALAVRA NO TEXTO DE ORIGEM
      raiz->inf.freqB = freq_palav(texto, palavra->inf.p); 
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
	//CASO A PALAVRA JÁ EXISTA, INCREMENTA A FREQUÊNCIA DE CO-OCORRÊNCIA
	raiz->inf.freqAB++;
	*ok = 0;
      }
    }
  }

  return raiz;
}

//INSERE UMA PALAVRA EM UMA AVL COM CHAVE PELA ESTATISTICA DE CO-OCORRENCIA
NO_PROX* insereSTAT(NO_PROX *raiz, PROX_PALAVRA info , int *ok){

  if (raiz == NULL){
    raiz = (NO_PROX*) malloc(sizeof(NO_PROX));
    if(raiz == NULL){
      printf("Memória Insuficiente!");
      *ok = 0;
    }
    else{  
      raiz->inf = info;
      raiz->esq = NULL;
      raiz->dir = NULL;
      raiz->FB = 0; 
      *ok = 1;
    }
  }
  else{
    if (info.stat < raiz->inf.stat){
      raiz->esq = insereSTAT(raiz->esq,info,ok);      
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
      raiz->dir = insereSTAT(raiz->dir,info,ok);
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
  }
  return raiz;
}

//CALCULA A ESTATITICA DE CO-OCORRENCIA DE CADA PALAVRA DE UMA ARVORE
NO_PROX *calcula_estatPROX(int freqA, NO_PROX *raiz){
  
  if(raiz != NULL){
    
    //PARA CADA NODO DA ÁRVORE, CALCULA A ESTATISTICA DE CO-OCORRENCIA
    raiz->inf.stat = (raiz->inf.freqAB / sqrt(freqA * raiz->inf.freqB));
    
    raiz->esq = calcula_estatPROX(freqA, raiz->esq);
    raiz->dir = calcula_estatPROX(freqA, raiz->dir);

  }
  return raiz;
}

//CONVERTE UMA ARVORE COM CHAVE PELA ORDEM ALFABETICA
//PARA UMA ARVORE COM CHAVE PELE ESTATISTICA
NO_PROX *organizaArvore(NO_PROX *raiz, NO_PROX *organiza){

  int ok;

  if(organiza != NULL){

    //INSERE A INFORMAÇÃO DO NO ATUAL EM
    //UMA ARVORE ORDENADA PELA ESTATITICA
    raiz = insereSTAT(raiz, organiza->inf, &ok);

    if(organiza->esq != NULL){
      raiz = organizaArvore(raiz, organiza->esq);
    }
    if(organiza->dir != NULL){
      raiz = organizaArvore(raiz, organiza->dir);
    }

    //DESTROI A ARVORE ANTERIOR
    free(organiza);
    organiza = NULL;

  }
  
  //RETORNA A NOVA ARVORE
  return raiz;
  
}


