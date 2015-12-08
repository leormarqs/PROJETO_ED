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

  clock_t inicioTotal, finalTotal;
  clock_t inicioLeitura, finalLeitura;
  clock_t inicioEst, finalEst;
  clock_t inicioCons, finalCons;

  clock_t tempo[4];

  inicioTotal = clock();
  inicioLeitura = clock();

  texto = LSE_inicializa();
  texto = ARQ_LE_TEXTO(texto, argv[1]);
  
  consultas = LSE_inicializa();
  consultas = ARQ_LE_TEXTO(consultas, argv[2]);

  finalLeitura = clock();
  
  inicioEst = clock();
  
  busca = inicializaCONS();
  busca = busca_palavras(texto,consultas,busca);

  busca = calcula_estatCONS(busca);

  finalEst = clock();
  inicioCons = clock();
  
  grava_arquivo(busca, atoi(argv[4]), argv[3]);

  finalCons = clock();
  finalTotal = clock();

  tempo[0] = 1000 * (finalTotal - inicioTotal) / (CLOCKS_PER_SEC);
  tempo[1] = 1000 * (finalLeitura -inicioLeitura) / (CLOCKS_PER_SEC);
  tempo[2] = 1000 * (finalEst - inicioEst) / (CLOCKS_PER_SEC);
  tempo[3] = 1000 * (finalCons - inicioCons) / (CLOCKS_PER_SEC);

  grava_tempos(tempo, argv[3]);

  printf("\n\nTempo total de execução do programa: %ld ms\n",tempo[0]);
  printf("Tempo de leitura do corpus: %ld ms\n",tempo[1]);
  printf("Tempo de cálculo das medidas estatísticas: %ld ms\n",tempo[2]);
  printf("Tempo de consulta na estrutura de dados de saída: %ld ms\n",tempo[3]);


  
  return 0;
}



/* funcao: arvore contador */
/* int controlador */

/* se(contador >= controlador) */
/*   para */
/* se nao */
/*   recursao arvore contado ++   */

