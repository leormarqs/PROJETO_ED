#include <stdio.h>
#include "sugestao_lib.h"
#include <string.h>
#include <ctype.h>
#define TAM_PALAVRA 30
#define TAM_ARQUIVO 10
#define CRC_IMPROPRIOS 12
/*
    LEGENDA GERAL

        LDE: Lista Duplamente encadeada
        ARQ: Arquivos
        SRC: Pesquisa

    LEGENDA CONSTANTES

        TAM_PALAVRA: Tamanho máximo que uma palavra do texto pode ter
        TAM_ARQUIVO: Tamanho máximo que o nome do arquivo deve ter
        CRC_IMPROPRIOS: Tamanho do vetor que armazena caracteres impróprios para formação de palavras
*/



//---------------------------------------------------------------------------------- BLOCO LDE
NODO *LDE_inicializa(){
    return NULL;
}


//A função cria um novo nodo e o retorna
NODO *LDE_novoNodo(char *vetor){
    NODO *novoNodo;

    novoNodo = LDE_inicializa();
    novoNodo = (NODO*)malloc(sizeof(NODO));

    novoNodo->next = NULL;
    novoNodo->prev = NULL;
    strcpy(novoNodo->inf.p, vetor);

    return novoNodo;
}

NODO *LDE_insereNodo(NODO *lista, char *vetor){

    NODO *aux, *novoNodo;

    //Atribuição de um novo nodo.
    novoNodo = LDE_novoNodo(vetor);

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
        novoNodo->prev = aux;
        aux->next = novoNodo;
    }

    return lista;
}


//Imprime lista
void LDE_imprime(NODO *lista){

    while(lista != NULL){
        printf("\n%s", lista->inf.p);
        lista = lista->next;
    }
}





//---------------------------------------------------------------------------------- BLOCO ARQ

/*
    CARACTERE

    Função verifica se o caractere é próprio para formar uma palavra ou não.
    Retorna:
        1 para pŕoprio
        0 para impróprio
*/
int ARQ_validaCaractere(char caractere){
    char vetor[CRC_IMPROPRIOS] = {'.','!',',','?',' ',':',';','/', '\n','"','-' ,EOF };
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
            }
	    else{

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
                if(palavra[0] != ' '){
                    //Armazenando nodo
                    lista = LDE_insereNodo(lista, palavra);

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

//---------------------------------------------------------------------------------- BLOCO SRC

