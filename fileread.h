//Constantes
#define TAM_PALAVRA 20

/*

   TAD RESPONSÁVEL PELA LEITURA DO CORPUS E DAS PALAVRAS A SEREM CONSULTADAS
   E RESPECTIVO ARMAZENAMENTO EM UMA LISTA SIMPLESMENTE ENCADEADA

*/

//Informação de cada NODO
typedef struct word{
    char p[TAM_PALAVRA];
}WORD;

//Estrutura de um nodo
typedef struct nodo{
    WORD inf;
    struct nodo *next;
}NODO;



//---------------------------------------------------------------------- BLOCO LSE

//Inicializa uma lista
NODO *LSE_inicializa();

//Cria um novo nodo
NODO *LSE_novoNodo(char *);

//Insere uma palavra em uma lista
NODO *LSE_insereNodo(NODO *, char *);

//Imprime uma lista
void  LSE_imprime(NODO *);

//---------------------------------------------------------------------- BLOCO ARQ

//Le um arquivo, separa as palavras e grava em uma arquivo
NODO *ARQ_LE_TEXTO(NODO *, char *);

//Conta a frequencia de uma palavra em uma lista
int freq_palav(NODO *, char *);
