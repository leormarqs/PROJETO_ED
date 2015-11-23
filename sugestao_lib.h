//Constantes
#define TAM_PALAVRA 20
#define TAM_ARQUIVO 10

//TAD para encadear todas palavras do texto
typedef struct palavra{
    char p[TAM_PALAVRA];
}PALAVRA;

typedef struct nodo{
    PALAVRA inf;
    struct nodo *next;
}TEXTO;

//TAD Para armazenar dados de sugestão
typedef struct estatisticaPalavra{
    char sugestao[TAM_PALAVRA];
    float freq;
}ESTATISTICA;


typedef struct proxima_palavra{
    char palav[TAM_PALAVRA];
    int  freqAB;
    int  freqB;
}PROXIMA_PALAVRA;

typedef struct proximas{
    PROXIMA_PALAVRA inf;
    struct proximas *next;
}PROXIMAS; //PROVAVELMENTE MUDE PARA UMA ARVORE


typedef struct palavra_consultada{
    char palav[TAM_PALAVRA];
    int  freqA;
}PALAVRA_CONSULTADA;

typedef struct consultadas{
    PALAVRA_CONSULTADA inf;
    PROXIMAS *vizinhas; //provavelmente mude para uma arvore
    struct consultadas *next;
}CONSULTADAS;



/*
LEITURA DO TEXTO - OK

PROX. PASSOS:

LEITURA DAS CONSULTAS
PROCURA DAS PALAVRAS CONSULTADAS, COM CONTAGEM DA PALAVRA + OCORRENCIA MÚTUA
CALCULO DAS FREQUENCIAS RELATIVAS


GERAR ARQUIVO COM SAIDAS - ?










*/











//---------------------------------------------------------------------------------- BLOCO LSE
NODO *LDE_inicializa();
NODO *LDE_novoNodo(char *vetor);
NODO *LDE_insereNodo(NODO *lista, char *vetor);
NODO *LDE_insereNodo(NODO *lista, char *vetor);
void LDE_imprime(NODO *lista);


//---------------------------------------------------------------------------------- BLOCO ARQ
int ARQ_validaCaractere(char caractere);
NODO *ARQ_geraLista(NODO *lista, char *arquivo);
