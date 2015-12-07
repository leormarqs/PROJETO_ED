/* TAD_AVL - LEONARDO MARQUES RODRIGUES
PORTO ALEGRE 07/12/2015
COMPILADO EM SO UBUNTU 64bits */

#include <stdio.h>
#include <stdlib.h>
#include "abp.h"


int main(){
  int aux,tam = 0;
  NO *raiz;
  
  raiz = inicializa(); //Inicializa a ABP

  //Isere as informações
  aux = insere(&raiz, 8);
  aux = insere(&raiz, 4);
  aux = insere(&raiz, 9);
  aux = insere(&raiz, 2);
  aux = insere(&raiz, 6);
  aux = insere(&raiz, 1);
  
  printf("Programa para testar funções do TAD_ABP:\n");
  
  printf("\nImpressao Pre-Fixada a Esquerda\n\n");
  imprime(raiz);
  printf("\n\n");
  
  //Contagem da quantidade de nós na arvore
  tam = no_counter(raiz);
  printf("Quantidade de Nos presentes na árvore: %d\n\n", tam);
  
    //Imprime a arvore demarcando o nivel dos nos
  printf("\nImpressão demarcando o nivel dos nos:\n\n");
  imprime_nivel(raiz, 0);
  



}
