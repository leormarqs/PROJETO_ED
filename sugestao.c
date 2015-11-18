#include <stdio.h>
#include "sugestao_lib.h"
#include "sugestao_func.c"
#include <string.h>
#define TAM_PALAVRA 30
int main(){

    NODO *lista;
    lista = LDE_inicializa();
    int t;

    char teste[TAM_PALAVRA];

    //Gera a lista
    lista = ARQ_geraLista(lista, "teste.txt");

    //Imprime
    LDE_imprime(lista);
}
