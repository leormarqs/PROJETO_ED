//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fileread.h"

/*

   TAD RESPONSÁVEL PELA LEITURA DO CORPUS E DAS PALAVRAS A SEREM CONSULTADAS
   E RESPECTIVO ARMAZENAMENTO EM UMA LISTA SIMPLESMENTE ENCADEADA

*/



//---------------------------------------------------------------------- BLOCO LSE
NODO *LSE_inicializa(){
  return NULL;
}

//A função cria um novo nodo com a palavra fornecida e o retorna
NODO *LSE_novoNodo(char *vetor){
  NODO *novoNodo;
  
  novoNodo = LSE_inicializa();
  novoNodo = (NODO*)malloc(sizeof(NODO));
  
  novoNodo->next = NULL;
  strcpy(novoNodo->inf.p, vetor);
  
  return novoNodo;
}

//Insere a palvra fornecida em uma lista
NODO *LSE_insereNodo(NODO *lista, char *vetor){

  NODO *aux, *novoNodo;
  
  //Atribuição de um novo nodo.
  novoNodo = LSE_novoNodo(vetor);
  
  if(lista == NULL){
    lista = novoNodo;
  }else{
    
    //Faz a atribuição para poder percorrer a lista.
    aux = lista;
	
    //Percorre a lista até o último nodo para poder fazer a linkagem
    while(aux->next != NULL){
      aux = aux->next;
    }

    /* --- FINAL DA LISTA --- */
    aux->next = novoNodo;
  }

  return lista;
}


//Imprime lista
void LSE_imprime(NODO *lista){
  
  NODO *aux;
  aux = lista;
  
  while(aux != NULL){
    //puts(aux->inf.p);
    printf("%s\n",aux->inf.p);
    aux = aux->next;
  }
}

//--------------------------------------------------------------------- BLOCO ARQ

/* LÊ O ARQUIVO DE TEXTO DO ENDEREÇO FORNECIDO, SEPARA SUAS PALAVRAS DE ACORDO COM OS TOKENS, E ARMAZENA EM UMA LISTA */

NODO *ARQ_LE_TEXTO(NODO *lista, char *arquivo){
  
  FILE *ARQ;
  
  char tokens [] = {' ','!','"','#','$','%','&','\'','(',')',
		    '*','+','"',',','-','.','/','0','1','2',
		    '3','4','5','6','7','8','9',':',';','<',
		    '=','>','?','@','[','\\',']','^','_','`',
		    '{','|','}','~','\n','\t','\r'};
  
  char *palavra, buffer[1000];
  int i;
  
  
  //Abrindo arquivo
  ARQ = fopen(arquivo, "r");

  if(ARQ == NULL){
    printf("Arquivo inexistente");
  }
  else{
    while (fgets(buffer,1000,ARQ)){
      //considera qquer caractere não alfabético como separador
      palavra = strtok (buffer, tokens);
      while (palavra != NULL){
	
	for(i=0;palavra[i] != '\0'; i++){
	  palavra[i] = toupper(palavra[i]);
	}
	
	lista = LSE_insereNodo(lista, palavra);
	palavra = strtok (NULL, tokens);
	
      }
    }
    
    fclose(ARQ);
  }
  
  return lista;
  
}

//Conta a frequencia de uma palavra na lista dada
int freq_palav(NODO *lista, char *palavra){
  
  int contador = 0;
  NODO *auxLista;

  auxLista = lista;

  while(auxLista != NULL){

    if(!strcmp(auxLista->inf.p, palavra)){
      contador++;
    }
    auxLista = auxLista->next;
  }

  return contador;
}









  
