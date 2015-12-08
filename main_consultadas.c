/* TAD_AVL - LEONARDO MARQUES RODRIGUES
PORTO ALEGRE 07/12/2015
COMPILADO EM SO UBUNTU 64bits */

#include <stdio.h>
#include <stdlib.h>
#include "proximas.h"


int main(){
  int aux, ok;
  NO_PROX *raiz;
  
  raiz = inicializaPROX(); //Inicializa a ABP

  //Isere as informações
  raiz = inserePROX(raiz, "teste1", &ok);
  imprime_nivelPROX(raiz,1);
  printf("\n\n\n");
  raiz = inserePROX(raiz,"teste2", &ok);
  imprime_nivelPROX(raiz,1);
  printf("\n\n\n");
  raiz = inserePROX(raiz, "teste3", &ok);
  imprime_nivelPROX(raiz,1);
  printf("\n\n\n");
  raiz = inserePROX(raiz,"teste4", &ok);
  imprime_nivelPROX(raiz,1);
  printf("\n\n\n");
  raiz = inserePROX(raiz, "teste5", &ok);
  imprime_nivelPROX(raiz,1);
  printf("\n\n\n");
  raiz = inserePROX(raiz, "teste6", &ok);
  imprime_nivelPROX(raiz,1);
  printf("\n\n\n");


  printf("Programa para testar funções do TAD_ABP:\n");
  
  printf("\nImpressao Pre-Fixada a Esquerda\n\n");
  imprime_nivelPROX(raiz,1);
  printf("\n\n");
  
}
