#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "consultadas.h"

int main(int argc, char *argv[]){
  setlocale(LC_ALL,"");

  NODO *texto, *consultas;
  NO_CONS *busca;

  //Gera a lista
  texto = LSE_inicializa();
  texto = ARQ_LE_TEXTO(texto, argv[1]);
  //LSE_imprime(texto);

  printf("\n\n");


  consultas = LSE_inicializa();
  consultas = ARQ_LE_TEXTO(consultas, argv[2]);
  
  //FUNÇÃO QUE APLICA A INSERÇÃO EM TODAS AS CONSULTADAS
  //FUNÇÃO QUE PEGA UMA CONSULTADA E CONSULTA NO TEXTO, APÓS INSERE NA ESTRUTURA

  busca = inicializaCONS();
  busca = busca_palavras(texto,consultas,busca);

  imprime_nivelCONS(busca,0);

  return 0;
}
