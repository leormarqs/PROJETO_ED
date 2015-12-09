#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "consultadas.h"

int main(int argc, char *argv[]){
  setlocale(LC_ALL,"");

  //DECLARA AS ESTRUTURAS USADAS
  NODO *texto, *consultas;
  NO_CONS *busca;

  //DECLARA AS VARIAVEIS DE TEMPO USADAS
  clock_t inicioTotal, finalTotal;
  clock_t inicioLeitura, finalLeitura;
  clock_t inicioEst, finalEst;
  clock_t inicioCons, finalCons;

  clock_t tempo[4];

  printf("\nSUGESTÃO DE PALAVRAS DE CO-OCORRÊNCIA\n");
  printf("TRABALHO PRÁTICO FINAL - ESTRUTURA DE DADOS\n");
  printf("LEONARDO RODRIGUES     - 00213751\n");
  printf("MARCOS VINICIOS        - 00261600\n");

  if(argc != 5){

    printf("\nNÚMERO DE ARGUMENTOS INVÁLIDOS\n");

  }
  else{
  
    //INICIA TEMPO TOTAL E TEMPO DE LEITURA
    inicioTotal = clock();
    inicioLeitura = clock();
    
    //LE O CORPUS
    printf("\nLENDO CORPUS PARA O CÁLCULO\n");
    texto = LSE_inicializa();
    texto = ARQ_LE_TEXTO(texto, argv[1]);
    
    //LE AS PALAVRAS A SEREM CONSULTADAS
    printf("\nLENDO PALAVRAS A SEREM CONSULTADAS\n");
    consultas = LSE_inicializa();
    consultas = ARQ_LE_TEXTO(consultas, argv[2]);
    
    //FINALIZA O TEMPO DE LEITURA
    finalLeitura = clock();
    //INICIA O TEMPO DE CÁLCULO DAS ESTATÍSTICAS
    inicioEst = clock();
    
    //CALCULA AS FREQUENCIAS DAS PALAVRAS CONSULTADAS E
    //SUAS RESPECTIVAS FREQUENCIAS DE CO-OCORRENCIA
    printf("\nCALCULANDO AS MEDIDAS ESTATÍSTICAS\n");
    busca = inicializaCONS();
    busca = busca_palavras(texto,consultas,busca);
    
    //CALCULA AS ESTATÍSTICAS DE CO-OCORRENCIA PARA CADA PALAVRA CONSULTADA
    busca = calcula_estatCONS(busca);
    
    //ENCERRA TEMPO DE ESTATISTICA
    finalEst = clock();
    //INICIA TEMPO DE CONSULTA E ESCRITA DE ARQUIVO
    inicioCons = clock();
    
    //CONSULTA A ESTRUTURA DE PALAVRAS DE SAIDA E SUAS CO-OCORRENCIAS,
    //E GRAVA A QUANTIDADE DE SUGESTÕES SOLICITADAS NO ARQUIVO DE SAIDA SOLICITADO
    printf("\nBUSCANDO SUGESTÕES E GRAVANDO EM ARQUIVO\n");
    grava_arquivo(busca, atoi(argv[4]), argv[3]);
    
    //ENCERRA TEMPO DE ESCRITA E TEMPO TOTAL
    finalCons = clock();
    finalTotal = clock();
    
    //CALCULA OS TEMPOS PARA CADA ETAPA
    tempo[0] = 1000 * (finalTotal - inicioTotal) / (CLOCKS_PER_SEC);
    tempo[1] = 1000 * (finalLeitura -inicioLeitura) / (CLOCKS_PER_SEC);
    tempo[2] = 1000 * (finalEst - inicioEst) / (CLOCKS_PER_SEC);
    tempo[3] = 1000 * (finalCons - inicioCons) / (CLOCKS_PER_SEC);
    
    //GRAVA OS TEMPOS DE CADA ETAPA NO ARQUIVO DE SAIDA
    grava_tempos(tempo, argv[3]);
    
    printf("\n\nTEMPO DE CADA ETAPA DE EXECUÇÃO DO PROGRAMA:\n\n");
    printf("Tempo total de execução do programa: %ld ms\n",tempo[0]);
    printf("Tempo de leitura do corpus: %ld ms\n",tempo[1]);
    printf("Tempo de cálculo das medidas estatísticas: %ld ms\n",tempo[2]);
    printf("Tempo de consulta na estrutura de dados de saída: %ld ms\n",tempo[3]);
    
  }

  printf("\n\nPROGRAMA ENCERRADO.\n\n");
  
  return 0;

}

