//Constantes
#define TAM_PALAVRA 20

//TAD para encadear todas palavras do texto
typedef struct word{
    char p[TAM_PALAVRA];
}WORD;

typedef struct nodo{
    WORD inf;
    struct nodo *next;
}NODO;

/* //TAD Para armazenar dados de sugestão */
/* typedef struct estatisticaPalavra{ */
/*     char sugestao[TAM_PALAVRA]; */
/*     float freq; */
/* }ESTATISTICA; */


/*
LEITURA DO TEXTO - OK

PROX. PASSOS:

PROCURA DAS PALAVRAS CONSULTADAS, COM CONTAGEM DA PALAVRA + OCORRENCIA MÚTUA
CALCULO DAS FREQUENCIAS RELATIVAS


GERAR ARQUIVO COM SAIDAS - ?



*/


//---------------------------------------------------------------------- BLOCO LSE
NODO *LSE_inicializa();

NODO *LSE_novoNodo(char *);

NODO *LSE_insereNodo(NODO *, char *);

NODO *LSE_insereNodo(NODO *, char *);

void  LSE_imprime(NODO *);

//---------------------------------------------------------------------- BLOCO ARQ
NODO *ARQ_LE_TEXTO(NODO *, char *);

int freq_palav(NODO *, char *);
