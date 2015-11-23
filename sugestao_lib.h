//Constantes
#define TAM_PALAVRA 20
#define TAM_ARQUIVO 10

//TAD para encadear todas palavras do texto
typedef struct palavra{
    char p[TAM_PALAVRA];
}PALAVRA;

typedef struct nodo{
    struct nodo *next;
    PALAVRA inf;
}NODO;

//TAD Para armazenar dados de sugestão
typedef struct estatisticaPalavra{
    char sugestao[TAM_PALAVRA];
    float freq;
}ESTATISTICA;



//---------------------------------------------------------------------------------- BLOCO LSE
NODO *LDE_inicializa();
NODO *LDE_novoNodo(char vetor[]);
NODO *LDE_insereNodo(NODO *lista, char vetor[]);
NODO *LDE_insereNodo(NODO *lista, char vetor[]);
void LDE_imprime(NODO *lista);


//---------------------------------------------------------------------------------- BLOCO ARQ
int ARQ_validaCaractere(char caractere);
NODO *ARQ_geraLista(NODO *lista, char arquivo[TAM_ARQUIVO]);
