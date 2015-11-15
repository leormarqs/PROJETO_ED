/*TAD PRODUTO PARA LISTAS DUPLAMENTE ENCADEADAS
COMPILADO EM SO UBUNTU 14.04 64bits

Leonardo Marques Rodrigues - 14/09/2015 */

#include <stdio.h>
#include <stdlib.h>
#include "listas_duplas.h"
#include <string.h>


ELEMENTO* inicializa_lista(void)
{
  return NULL;
}

void imprime(ELEMENTO *primeiro){
  ELEMENTO *aux;

  if (primeiro == NULL){ //Verifica se a Lista está vazia.
    printf("\nLista Vazia\n");
  }
  else
    
    printf("\nLista armazenada:\n");
    
    for (aux = primeiro; aux != NULL; aux = aux->prox){//Imprime todos os elementos da Lista
      printf("%s\n", aux->info.nome);
    }
}

void imprime_inversa(ELEMENTO *primeiro){
  ELEMENTO *aux;
  
  if (primeiro==NULL){
    printf("\nLista Vazia\n");
  }
  else{
    aux = primeiro;
    
    while (aux->prox != NULL){ //Percorre a lista até o final
      aux=aux->prox;
    }
  
    printf("\nLista inversa:\n");
    while (aux != NULL){
      printf("%s\n", aux->info.nome);
      aux=aux->ant;
    }
  }
}

ELEMENTO* insere_inicio(ELEMENTO *primeiro, char *novo){
  ELEMENTO *aux;
  
  aux = (ELEMENTO*) malloc(sizeof(ELEMENTO));
  aux->info.nome = novo;
  aux->ant = NULL;
  aux->prox = primeiro;
  
  if (primeiro != NULL){
    primeiro->ant = aux;
  }

  primeiro = aux;
  
  free(aux);
  aux = NULL;
  
  return primeiro;
}

ELEMENTO* insere_fim(ELEMENTO *primeiro, char *novo){
  ELEMENTO *ptaux, *aux;
  
  aux=malloc(sizeof(ELEMENTO));
  aux->info.nome = novo;
  aux->ant = NULL;
  aux->prox = NULL;
  
  if (primeiro == NULL){ //Verifica se a Lista está vazia.
    primeiro = aux;
  }
  else{
    for (ptaux = primeiro; ptaux->prox != NULL; ptaux = ptaux->prox); //PERCORRE LISTA ATÉ O FINAL
    ptaux->prox = aux;
    aux->ant = ptaux;
    aux->prox = NULL;
  }

  free(aux);
  aux = NULL;
  
  return primeiro;
}

ELEMENTO* remove(ELEMENTO *primeiro, char nome[]){
  ELEMENTO *aux = primeiro; //ponteiro auxiliar para percorrer a lista
  
  if(primeiro == NULL){
    printf("\nLista Vazia\n");
  }
  else {
      while (aux != NULL && !strcmp(aux->info.nome, nome)){ //procura o elemento na lista
          aux = aux->prox;
      }
      if (aux != NULL){ //verifica se achou
	  if (aux == primeiro){ //vai remover o primeiro elemento
	      
	      if(aux->prox == NULL){ //Caso o primeiro elemento da lista seja o único.
		  primeiro = NULL;
	      }
	      else{
		  primeiro = aux->prox;
		  primeiro->ant = NULL;
	      }
	  }
	  else{
	      if(aux->prox == NULL){ //vai remover o último
		  aux->ant->prox = NULL;
	      }
	      else{ //vai remover do meio
		  aux->ant->prox = aux->prox;
		  aux->prox->ant = aux->ant;
	      }
	  }
      }
  }
  
  free(aux);
  aux = NULL;
  
  return primeiro;
}

ELEMENTO* destroi(ELEMENTO *primeiro){
    ELEMENTO *aux; //ponteiro auxiliar para percorrer a lista
    
    while (primeiro != NULL){
        aux = primeiro;
        primeiro = primeiro->prox;
        free(aux);
    }
    
    free(primeiro);
    primeiro = NULL;
    aux = NULL;

    return primeiro;
}
