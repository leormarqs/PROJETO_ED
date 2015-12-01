#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "sugestao_lib.h"

//Constantes


int main(int argc, char *argv[]){
  setlocale(LC_ALL,"");

  NODO *texto, *consultas;

  //Gera a lista
  texto = LSE_inicializa();
  texto = ARQ_LE_TEXTO(texto, argv[1]);

  consultas = LSE_inicializa();
  consultas = ARQ_LE_TEXTO(consultas, argv[2]);

  LSE_imprime(consultas);


  return 0;
}
