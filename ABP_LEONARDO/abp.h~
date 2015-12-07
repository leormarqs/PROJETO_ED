/* TAD_AVL - LEONARDO MARQUES RODRIGUES
PORTO ALEGRE 07/12/2015
COMPILADO EM SO UBUNTU 64bits */

typedef struct info{
  int num;
}INF;

typedef struct nodo{
  struct nodo *esq;
  struct nodo *dir;
  int alt;
  INF info;
}NO;

NO *inicializa();
NO *novoNODO(int);
int insere(NO **, int);
void imprime(NO *);
int no_counter(NO *);
void arvore_grau(NO *, int *);
void imprime_nivel(NO *, int);

int alturaNO(NO *);
int balanceamento(NO *);
int maior(int,int);

NO *rotacaoDIR(NO *);
NO *rotacaoESQ(NO *);

NO *rotacaoDuplaDIR(NO *);
NO *rotacaoDuplaESQ(NO *);
