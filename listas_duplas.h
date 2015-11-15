/*TAD PARA LISTAS DUPLAMENTE ENCADEADAS
Leonardo Marques Rodrigues - 14/09/2015 */

typedef struct info {

  char nome[20];

}INFO;

typedef struct ele {

  INFO info;
  struct ele *ant;
  struct ele *prox;

}ELMT_S;

ELMT_S* inicializa_lista(void);

void imprime(ELMT_S*);

void imprime_inversa(ELMT_S*);

ELMT_S* insere_inicio(ELMT_S*, char*);

ELMT_S* insere_fim(ELMT_S*, char*);

ELMT_S* remove(ELMT_S*, char*);

ELMT_S* destroi(ELMT_S*);
