//Bibliotecas
#include <stdio.h>
#include "sugestao_lib.h"
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

//Constantes
#define TAM_PALAVRA 20
#define TAM_ARQUIVO 10
#define CRC_IMPROPRIOS 11
#define PALAVRAS_SUGERIDAS 5

/*
    LEGENDA GERAL

        TRT: Tratamento de palavras
        LSE: Lista Simplesmente encadeada
        ARQ: Arquivos

        SRC: Pesquisa
             qtd -> quantidade
             seq -> sequência



    LEGENDA CONSTANTES

        TAM_PALAVRA: Tamanho máximo que uma palavra do texto pode ter
        TAM_ARQUIVO: Tamanho máximo que o nome do arquivo deve ter
        CRC_IMPROPRIOS: Tamanho do vetor que armazena caracteres impróprios para formação de palavras
*/


//---------------------------------------------------------------------------------- BLOCO TRT
void TRT_limpaPalavra(char *palavra){
    int i;

    for(i = 0; palavra[i] != '\0'; i++){
        palavra[i] = '\0';
    }
}

//---------------------------------------------------------------------------------- BLOCO LDE
NODO *LSE_inicializa(){
    return NULL;
}


//A função cria um novo nodo e o retorna
NODO *LSE_novoNodo(char vetor[]){
    NODO *novoNodo;

    novoNodo = LSE_inicializa();
    novoNodo = (NODO*)malloc(sizeof(NODO));

    novoNodo->next = NULL;
    strcpy(novoNodo->inf.p, vetor);

    return novoNodo;
}

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
void LDE_imprime(NODO *lista){

    NODO *aux;
    aux = lista;

    while(aux != NULL){
        puts(aux->inf.p);
        aux = aux->next;
    }
}





//---------------------------------------------------------------------------------- BLOCO ARQ

/*
    VALIDA CARACTERE

    Função verifica se o caractere é próprio para formar uma palavra ou não.
    Retorna:
        1 para pŕoprio
        0 para impróprio
*/
int ARQ_validaCaractere(char caractere){
    char vetor[CRC_IMPROPRIOS] = {'.','!',',','?',' ',':',';','/','\n','"','-'};
    int i;
    int result = 1;


    for(i=0; i<CRC_IMPROPRIOS; i++){
        if(caractere == vetor[i]){
            result = 0;
        }
    }

    return result;
}
/*
    GERA LISTA

            A função lê um arquivo de texto caractere por caractere. Usando uma função auxiliar é
        feita uma classificação dos caracteres em válido(1) e inválido(0). Para todo caractere válido
        a função principal armazena em um vetor palavra[] uma sequência de caracteres válidos até encontrar um caractere
        inválido, definindo então uma palavra.
            Após a definição de palavra em um vetor, uma função auxiliar é usada para armazenar a palavra em um nodo
        e encadear duplamente em uma lista.

            Exemplo:
                Frase: "Isso é um teste. Teste."

                    Caractere 'I':
                        caractere válido
                            palavra[contador] = caractere;
                            contador++

                    Caractere 's':
                        caractere válido
                            palavra[contador] = caractere;
                            contador++

                            [...]

                    Caractere 'o':
                        caractere válido
                            palavra[contador] = caractere;
                            contador++

                    Caractere ' ':
                        caractere inválido
                            Cria e encadeia nodo com a palavra
                            altera casas do vetor palavra para ' '
                            zera contador

                    Processo é realizado até o final do arquivo.

*/

NODO *ARQ_geraLista(NODO *lista, char arquivo[TAM_ARQUIVO]){

    FILE *ARQ;
    int caractere; //variável para armazenar os caracteres
    char palavra[TAM_PALAVRA]; //Vetor para armazenar palavra
    int validaCaractere; //Recebe 0 para caractere inválido e 1 para caractere válido
    int i = 0; //Contador para armazenar a palavra dentro do vetor

    //Abrindo arquivo
    ARQ = fopen(arquivo, "r");

    if(ARQ == NULL){
        printf("Arquivo inexistente");
    }else{
        //Percorre o arquivo armazenando os caracteres
        while((caractere=fgetc(ARQ)) != EOF){

            //Valida o caractere
            validaCaractere = ARQ_validaCaractere(caractere);

            if(validaCaractere == 1){
                //Armazena os caracteres até formar a palavra
                palavra[i] = toupper(caractere);
                i += 1;
            }else{

                /*
                    Condição para impedir que uma sequência de caracteres inválidos crie u novo nodo.s

                    Exemplo:
                        Passagem x    : Caractere Inválido -> Armazena a palavra agrupada até então e zera vetor palavra
                        Passagem x + 1: Caractere Inválido -> Armazena uma palavra vazia

                    Esse problema geralmente acontece após alguma pontuação, já que o próximo
                    caractere provavelmente será do tipo ' '.

                    Exemplo:
                        "arvore". -> condição impede de armazenar o ponto final

                */
                if(palavra[0] != '\0'){
                    //Armazenando nodo
                    lista = LSE_insereNodo(lista, palavra);

                    //Zerando vetor palavra
                    for(i = 0; palavra[i] != '\0'; i++){
                        palavra[i] = '\0';
                    }

                    //Zerando contador
                    i = 0;
                }

            }
        }

    }

    fclose(ARQ);
    return lista;

}


/*
    GERA ARQUIVO DE SAÍDA COM SUGESTÕES

    A função recebe um vetor com as frequências mais altas de sugestão e gera
    um arquivos com todas sugestões.
*/
void ARQ_geraArqSaida(ESTATISTICA *vetor, char *palavraProcurada, clock_t tempoExecucao){

    char url[TAM_ARQUIVO] = "saida.txt";
    int i;

    FILE *arq;

    arq = fopen(url, "w");

    if(arq == NULL){
        printf("Falha na criacao do arquivo");
    }else{

        //Cabecário do arquivo
        fprintf(arq, "\tTOP 5 PALAVRAS SUGERIDAS PARA %s\n\n\n", palavraProcurada);

        //Corpo
        for(i = PALAVRAS_SUGERIDAS; i >= 1; i--){
            fprintf(arq, "PALAVRA %d: %s\t\t FREQUENCIA: %f\n", i, vetor[i].sugestao, vetor[i].freq);
        }

        //Rodapé
        fprintf(arq, "TEMPO DE EXECUCAO %f", tempoExecucao);
    }

}

//---------------------------------------------------------------------------------- BLOCO SRC


//Varifica quantas palavras específicas estão no texto
int SRC_qtdPalavras(NODO *lista, char palavra[TAM_PALAVRA]){

    int contador = 0;
    NODO *auxLista;

    auxLista = lista;


    while(auxLista != NULL){

        if(strcmp(auxLista->inf.p, palavra) == 0){
            contador += 1;
        }
        auxLista = auxLista->next;
    }

    return contador;
}

/*
    VERIFICA A OCORRÊNCIA DE DUAS PALAVRAS EM SEQUÊNCIA

    A função percorre a lista até encontrar a palavraPesquisada. Quando esta é encontrada,
    feita uma verificação se a próxima palavra da lista é igual a palavraLado, caso se confirme, então
     verificado quantas vezes isso se repete ao longo da lista.
*/
int SRC_qtdSeqPalavras(NODO *lista, char *palavraPesquisada, char *palavraLado){
    NODO *aux;
    int contador = 0;
    aux = lista;

    while(aux != NULL){
        //Verifica se encontrou a palavra pesquisada
        if(strcmp(aux->inf.p, palavraPesquisada) == 0){

            aux = aux->next;

            //Verifica se a sequência de palavras acontece
            if(strcmp(aux->inf.p, palavraLado) == 0){
                contador += 1;
            }
        }else{

            aux = aux->next;
        }
    }
    return contador;
}
/*
    ARMAZENAMENTO EM VETOR

    A função posiciona as 5 melhores frequência em um vetor com tamanho pré-definido.
*/
void SRC_insereRanking(ESTATISTICA *vetor, char *sugestao, float freq){

    int i, j, k;
        //i: Percorre a lista em busca de alguma frequência menor que a informada
        //j e k: Organizam a lista com o bubble sort

    float freqAux;
    char sugestaoAux[TAM_PALAVRA];

    //Verifica se a frequência da nova palavra é maior que alguém de dentro do vetor.
    for(i = 0; i < PALAVRAS_SUGERIDAS; i++){

        //Caso encontre uma substituição apropriada, efetua a subst e reorganiza a lista com o bubble sort
        if(freq > vetor[i].freq){
            vetor[i].freq = freq;
            strcpy(vetor[i].sugestao, sugestao);


            //Algoritmo Buble Sort
            for(j = 0; j < PALAVRAS_SUGERIDAS; j++){
                for(k = 0; k < PALAVRAS_SUGERIDAS; k++){

                    if(vetor[j].freq < vetor[k].freq){

                        //Armazenando menores em variáveis auxiliares
                        strcpy(sugestaoAux, vetor[j].sugestao);
                        freqAux = vetor[j].freq;

                        //Passando maior para o começo
                        strcpy(vetor[j].sugestao, vetor[k].sugestao);
                        vetor[j].freq = vetor[k].freq;

                        //Armazenando auxiliares
                        strcpy(vetor[k].sugestao, sugestaoAux);
                        vetor[k].freq = freqAux;

                        //Limpando Palavra
                        TRT_limpaPalavra(sugestaoAux);

                    }
                }
            }

            //Iguala o incrementador i à PALAVRAS_SUGERIDAS para não haver mais substituições
            i = PALAVRAS_SUGERIDAS;
        }
    }
}




void SRC_topFrequencias(NODO *lista, char *palavraPesquisada){
    NODO *aux;
    int qtdAB, qtdA, qtdB;

    float freq;

    aux = lista;

    /*
        O cálculo realizado sobre o total de palavras pesquisadas no texto deve ser realizado apenas uma vez,
        logo deve ficar fora do laço para evitar que a cada volta, com a diminuição a lista,
        também diminua o total de palavras.

        Exemplo:
            Definindo-se uma frase como parâmetro:
                A jarra, a jarra e o lápis são objetos.

                Iteração 0:
                    Total de palavras no texto:    9
                    Total de palavras pesquisadas: 2

                Iteração 1:
                    Total de palavras no texto:    8
                    Total de palavras pesquisadas: 1

                Apartir desse ponto, uma alteração aconteceria em futuros cálculos de frequência.

    */
    qtdA = SRC_qtdPalavras(aux, palavraPesquisada) + 1;

    while(aux != NULL){

        //Verifica se encontrou a palavra pesquisada
        if(strcmp(aux->inf.p, palavraPesquisada) == 0){

            //Avança a lista para efetuar comparativos com a palavra que acompanha a palavra pesquisada.
            aux = aux->next;

            //Soma-se um, pois assumimos que cada vez que a palavra pesquisada é encontrada, então
            //teremos no mínimo uma ocorrência de repetição que não será computada
            qtdAB = SRC_qtdSeqPalavras(aux, palavraPesquisada, aux->inf.p) + 1;

            //Quantidade de vezes que a palavra acompanhante está na lista
            qtdB = SRC_qtdPalavras(aux, aux->inf.p);


            //Calcula a frequência
            freq = qtdAB / sqrt(qtdA * qtdB);

            //Saídas
            printf("PALAVRA: %s\n", palavraPesquisada);
            printf("SUGEST : %s\n", aux->inf.p);
            printf("QTD A  : %d\n", qtdA);
            printf("QTD B  : %d\n", qtdB);
            printf("QTD AB : %d\n", qtdAB);
            printf("FREQ   : %f\n\n", freq);


        }else{
            aux = aux->next;
        }

    }
}

