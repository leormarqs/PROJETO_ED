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
}NODO;

/* //TAD Para armazenar dados de sugestão */
/* typedef struct estatisticaPalavra{ */
/*     char sugestao[TAM_PALAVRA]; */
/*     float freq; */
/* }ESTATISTICA; */


/* typedef struct proxima_palavra{ */
/*     char palav[TAM_PALAVRA]; */
/*     int  freqAB; */
/*     int  freqB; */
/* }PROXIMA_PALAVRA; */

/* typedef struct proximas{ */
/*     PROXIMA_PALAVRA inf; */
/*     struct proximas *next; */
/* }PROXIMAS; //PROVAVELMENTE MUDE PARA UMA ARVORE */


/* typedef struct palavra_consultada{ */
/*     char palav[TAM_PALAVRA]; */
/*     int  freqA; */
/* }PALAVRA_CONSULTADA; */

/* typedef struct consultadas{ */
/*     PALAVRA_CONSULTADA inf; */
/*     PROXIMAS *vizinhas; //provavelmente mude para uma arvore */
/*     struct consultadas *next; */
/* }CONSULTADAS; */



/*
LEITURA DO TEXTO - OK

PROX. PASSOS:

LEITURA DAS CONSULTAS
PROCURA DAS PALAVRAS CONSULTADAS, COM CONTAGEM DA PALAVRA + OCORRENCIA MÚTUA
CALCULO DAS FREQUENCIAS RELATIVAS


GERAR ARQUIVO COM SAIDAS - ?



*/


//---------------------------------------------------------------------------------- BLOCO LSE
extern NODO *LSE_inicializa();
extern NODO *LSE_novoNodo(char *);
extern NODO *LSE_insereNodo(NODO *, char *);
extern NODO *LSE_insereNodo(NODO *, char *);
//int existe(NODO *, NODO *)
extern void  LSE_imprime(NODO *);


//---------------------------------------------------------------------------------- BLOCO ARQ
extern NODO *ARQ_LE_TEXTO(NODO *, char *);
