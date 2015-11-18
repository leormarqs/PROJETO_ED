//Constantes
#define TAM_PALAVRA 30
#define TAM_ARQUIVO 10

//Estrutura para a lista duplamente encadeada
typedef struct palavra{
    char p[TAM_PALAVRA];
}PALAVRA;

typedef struct nodo{
    struct nodo *next;
    struct nodo *prev;
    PALAVRA inf;
}NODO;


//---------------------------------------------------------------------------------- BLOCO LDE
NODO *LDE_inicializa();
NODO *LDE_novoNodo(char vetor[]);
NODO *LDE_insereNodo(NODO *lista, char vetor[]);
NODO *LDE_insereNodo(NODO *lista, char vetor[]);
void LDE_imprime(NODO *lista);


//---------------------------------------------------------------------------------- BLOCO ARQ
int ARQ_validaCaractere(char caractere);
NODO *ARQ_geraLista(NODO *lista, char arquivo[TAM_ARQUIVO]);
