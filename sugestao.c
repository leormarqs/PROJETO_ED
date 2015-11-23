#include <stdio.h>
#include "sugestao_lib.h"
#include <string.h>
#include <math.h>
#include <time.h>


//Constantes
#define TAM_PALAVRA 20
#define PALAVRAS_SUGERIDAS 5

int main(/*char *entrada, char *consultar, char *saida, int num_pesquisa */){

    NODO *texto, *lista, *aux;
    ESTATISTICA sugeridas[PALAVRAS_SUGERIDAS];
    int i;
    char buscasPalavra[TAM_PALAVRA];
    char palavraPesquisada[TAM_PALAVRA];
    int qtdA, qtdB, qtdAB;
    float freq;
    clock_t tempoInicial, tempoFinal;

    //Gera a lista
    texto = LSE_inicializa();
    texto = ARQ_geraLista(lista, "teste.txt");


    //Gera a lista de palavras a consultar
    lista = LSE_incializa();
    texto = ARQ_geraLista(texto, "consultar.txt");
    //---------------------------------------------------------------------------------------------
    //Marca o tempo antes da função ser executada
    tempoInicial = clock();

    SRC_topFrequencias(lista, "A");

    //Marca o tempo após a função ser executada
    tempoFinal = clock();

    //Gera arquivo de saída
    //ARQ_geraArqSaida(sugeridas, "A", tempoFinal - tempoInicial);













    //--------------------------------------------------------------------------------------------
    printf("--------------------- TESTES INDIVIDUAIS ------------------------\n\n");
    //Teste arquivo professora
    qtdA = SRC_qtdPalavras(lista, "A");
    qtdB = SRC_qtdPalavras(lista, "SUA");
    qtdAB = SRC_qtdSeqPalavras(lista, "A", "SUA");

    printf("A : %d\n", qtdA);
    printf("B : %d\n", qtdB);
    printf("AB: %d\n", qtdAB);
    freq = qtdAB / sqrt(qtdA * qtdB);
    printf("F : %f", freq);

    qtdA = SRC_qtdPalavras(lista, "A");
    qtdB = SRC_qtdPalavras(lista, "LUA");
    qtdAB = SRC_qtdSeqPalavras(lista, "A", "LUA");
    printf("\n\nA : %d\n", qtdA);
    printf("B : %d\n", qtdB);
    printf("AB: %d\n", qtdAB);
    freq = qtdAB / sqrt(qtdA * qtdB);
    printf("F : %f", freq);

    qtdA = SRC_qtdPalavras(lista, "DA");
    qtdB = SRC_qtdPalavras(lista, "TERRA");
    qtdAB = SRC_qtdSeqPalavras(lista, "DA", "TERRA");
    printf("\n\nA : %d\n", qtdA);
    printf("B : %d\n", qtdB);
    printf("AB: %d\n", qtdAB);
    freq = qtdAB / sqrt(qtdA * qtdB);
    printf("F : %f", freq);

    qtdA = SRC_qtdPalavras(lista, "DA");
    qtdB = SRC_qtdPalavras(lista, "GRAVIDADE");
    qtdAB = SRC_qtdSeqPalavras(lista, "DA", "GRAVIDADE");
    printf("\n\nA : %d\n", qtdA);
    printf("B : %d\n", qtdB);
    printf("AB: %d\n", qtdAB);
    freq = qtdAB / sqrt(qtdA * qtdB);
    printf("F : %f", freq);
}
