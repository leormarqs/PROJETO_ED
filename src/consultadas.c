#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consultadas.h"

//INICIALIZA A AVL
NO_CONS *inicializaCONS(){
  return NULL;
}

//CALCULA A ALTURA
int alturaCONS(NO_CONS *raiz){
  int alt_esq, alt_dir, rtrn;

  if (raiz == NULL){
    rtrn = 0;
  }
  else{

    alt_esq = alturaCONS(raiz->esq);
    alt_dir = alturaCONS(raiz->dir);

    if (alt_esq > alt_dir){
      rtrn = (1 + alt_esq);
    }
    else{
      rtrn = (1 + alt_dir);
    }
  }

  return rtrn;
}

//CALCULA O BALANCEAMENTO
int balanceamentoCONS(NO_CONS *raiz){
  return (alturaCONS(raiz->esq) - alturaCONS(raiz->dir));
}

//IMPRIME A AVL MARCANDO O NIVEL
void imprime_nivelCONS(NO_CONS *raiz, int cont){
    int i;

    if(raiz != NULL){
        for(i=0;i <= cont;i++){
            printf("=");
        }
        printf(" %s / freq: %d \n", raiz->inf.palavra, raiz->inf.freqA);
	printf("\n");
	imprime_nivelPROX(raiz->viz,i);
	printf("\n");
        if(raiz->esq != NULL){
            imprime_nivelCONS(raiz->esq, cont+1);
        }
        if(raiz->dir != NULL){
            imprime_nivelCONS(raiz->dir, cont+1);
        }
    }
}

//APLICA ROTAÇÃO
NO_CONS *rotacao_direitaCONS(NO_CONS *raiz){
   NO_CONS *aux;

   aux = raiz->esq;
   raiz->esq = aux->dir;
   aux->dir = raiz;

   raiz->FB = 0;
   raiz = aux;

   return raiz;
}

//APLICA ROTAÇÃO
NO_CONS *rotacao_esquerdaCONS(NO_CONS *raiz){
   NO_CONS *aux;

   aux = raiz->dir;
   raiz->dir = aux->esq;
   aux->esq = raiz;

   raiz->FB = 0;
   raiz = aux;

   return raiz;
}

//APLICA ROTAÇÃO
NO_CONS *rotacao_dupla_direitaCONS(NO_CONS *raiz){
  NO_CONS *aux, *aux1;

  aux = raiz->esq;
  aux1 = aux->dir;

  aux->dir = aux1->esq;
  aux1->esq = aux;

  raiz->esq = aux1->dir;
  aux1->dir = raiz;

  if (aux1->FB == 1){
    raiz->FB = -1;
  }
  else{
    raiz->FB = 0;
  }
  if (aux1->FB == -1){
    aux->FB = 1;
  }
  else{
    aux->FB = 0;
  }

  raiz = aux1;

  return raiz;
}

//APLICA ROTAÇÃO
NO_CONS *rotacao_dupla_esquerdaCONS(NO_CONS *raiz){
   NO_CONS *aux, *aux1;

   aux = raiz->dir;
   aux1 = aux->esq;

   aux->esq = aux1->dir;
   aux1->dir = aux;

   raiz->dir = aux1->esq;
   aux1->esq = raiz;

   if (aux1->FB == -1){
     raiz->FB = 1;
   }
   else{
     raiz->FB = 0;
   }
   if (aux1->FB == 1){
     aux->FB = -1;
   }
   else{
     aux->FB = 0;
   }

   raiz = aux1;

   return raiz;
}

//VERIFICA NECESSIDADE DE ROTAÇÃO
NO_CONS *caso1CONS(NO_CONS *raiz , int *ok){
  NO_CONS *aux;

  aux = raiz->esq;

  if (aux->FB == 1){
    raiz = rotacao_direitaCONS(raiz);
  }
  else{
    raiz = rotacao_dupla_direitaCONS(raiz);
  }

  raiz->FB = 0;
  *ok = 0;

  return raiz;
}

//APLICA ROTAÇÃO
NO_CONS *caso2CONS(NO_CONS *raiz , int *ok){
  NO_CONS *aux;

  aux = raiz->dir;

  if (aux->FB == -1){
    raiz=rotacao_esquerdaCONS(raiz);
  }
  else{
    raiz=rotacao_dupla_esquerdaCONS(raiz);
  }

  raiz->FB = 0;
  *ok = 0;

  return raiz;
}

//INSERE NA AVL ORDENANDO ALFABETICAMENTE
NO_CONS* insereCONS(NO_CONS *raiz, NODO *palavra, int *ok, NODO *texto){
  int aux;

  if (raiz == NULL){
    raiz = (NO_CONS*) malloc(sizeof(NO_CONS));
    if(raiz == NULL){
      printf("Memória Insuficiente!");
      *ok = 0;
    }
    else{
      //CASO PALAVRA AINDA NÃO CONSTE NA AVL
      strcpy(raiz->inf.palavra,palavra->inf.p);
      raiz->inf.freqA = 1;

      raiz->esq = NULL;
      raiz->dir = NULL;
      raiz->FB = 0;

      //INSERIR A PROXIMA PALAVRA DO TEXTO NA AVL DE CO-OCORRENCIAS
      raiz->viz = inicializaPROX();
      raiz->viz = inserePROX(raiz->viz, palavra->next, &aux, texto);

      *ok = 1;
    }
  }

  else{
    if (strcmp(palavra->inf.p,raiz->inf.palavra) < 0){
      raiz->esq = insereCONS(raiz->esq,palavra,ok,texto);
      if (*ok){
	switch(raiz->FB){
	case -1:
	  raiz->FB = 0;
	  *ok = 0;
	  break;
	case  0:
	  raiz->FB = 1;
	  break;
	case  1:
	  raiz=caso1CONS(raiz,ok);
	  break;
	}
      }
    }

    else{
      if(strcmp(palavra->inf.p,raiz->inf.palavra) > 0){
	raiz->dir = insereCONS(raiz->dir,palavra,ok,texto);
	if (*ok){
	  switch(raiz->FB){
	  case  1:
	    raiz->FB = 0;
	    *ok = 0;
	    break;
	  case  0:
	    raiz->FB = -1;
	    break;
	  case -1:
	    raiz = caso2CONS(raiz,ok);
	    break;
	  }
	}
      }

      else{
	//CASO A PALAVRA JA EXISTA, INCREMENTA SUA FREQUENCIA
	raiz->inf.freqA++;
	//INSERIR A PROXIMA PALAVRA DO TEXTO NA AVL DE CO-OCORRENCIAS
	raiz->viz = inserePROX(raiz->viz, palavra->next, &aux, texto);
	
	*ok = 0;
      }
    }
  }

  return raiz;
}

//LE PALAVRAS A SEREM CONSULTADAS, E INSERE NA AVL DE PALAVRAS A SEREM CONSULTADAS
NO_CONS *busca_palavras(NODO *texto, NODO *consultas, NO_CONS *busca)
{

  NODO *aux_texto, *aux_consultas = consultas;
  int ok=0;
  //PERCORRE A LISTA DE PALAVRAS A SEREM CONSULTADAS
  while(aux_consultas != NULL){
    aux_texto = texto;

    //PERCORRE O CORPUS
    while(aux_texto != NULL){

      //QUANDO ENCONTRADA A PALAVRA A SER CONSULTADA, INSERE NA AVL
      if(strcmp(aux_texto->inf.p,aux_consultas->inf.p)==0){
	busca = insereCONS(busca,aux_texto,&ok,texto);
      }
      aux_texto = aux_texto->next;
    }
    aux_consultas = aux_consultas->next;
  }

  //RETORNA A AVL DE PALAVRAS A SEREM CONSULTADAS
  return busca;

}

//CALCULA AS ESTÁTISTICA DE CO-OCORRENCIA DE UMA AVL DE PALAVRAS CONSULTADAS
NO_CONS *calcula_estatCONS(NO_CONS *raiz){
  NO_PROX *aux;
  if(raiz != NULL){

    //PARA CADA NODO DA AVL DE PALAVRAS CONSULTADAS, CALCULA
    //AS ESTATISTICAS DE CO-OCORRENCIA DE TODAS AS PALAVRAS QUE CO-OCORREM COM ESTA PALAVRA
    raiz->viz = calcula_estatPROX(raiz->inf.freqA, raiz->viz);

    //ORDENA AS PALAVRAS DE CO-OCORRENCIA PELA ESTATISTICA
    aux = inicializaPROX();
    aux = organizaArvore(aux, raiz->viz);
    raiz->viz = aux;
 
    raiz->esq = calcula_estatCONS(raiz->esq);
    raiz->dir = calcula_estatCONS(raiz->dir);

  }
  return raiz;
}

//ABRE ARQUIVO DE SAIDA E GRAVA AS SAIDAS
void grava_arquivo(NO_CONS *raiz, int k, char *arquivo){
  FILE *ARQ;
  
  //Abrindo arquivo
  ARQ = fopen(arquivo, "w");
  
  if(ARQ == NULL){
    printf("Arquivo inexistente");
  }
  else{
    imprimeCONS(raiz, k, ARQ);
    
    fclose(ARQ);
    
  }
}

//CONSULTA A ARVORE DE CONSULTADAS, E GRAVA PARA CADA PALAVRA CONSULTADA,
//AS K PALAVRAS COM MAIOR ESTATISTICA DE CO-OCORRENCIA
void imprimeCONS(NO_CONS *raiz, int k, FILE *ARQ){
  int cont;
  
  if(raiz != NULL){
    
    imprimeCONS(raiz->esq, k, ARQ);
    
    fprintf(ARQ,"\nConsulta: %s\n", raiz->inf.palavra);
    cont = 0;
    imprimeSUG(raiz->viz, &cont, k, ARQ);
    
    imprimeCONS(raiz->dir, k, ARQ);
  }
}

//CONSULTA A ARVORE DE CO-OCORRENCIAS E GRAVA AS K PALAVRAS
//COM MAIOR ESTATISTICA NO ARQUIVO FORNECIDO
void imprimeSUG(NO_PROX *raiz, int *cont,int k, FILE *ARQ){

  if(raiz != NULL ){
    if((*cont) < k){
      *cont = *cont + 1;
      imprimeSUG(raiz->dir, cont, k, ARQ);
      
      fprintf(ARQ, "\tSugerida: %s \t\t\t (%.6f)\n",raiz->inf.palav, raiz->inf.stat);
      
      imprimeSUG(raiz->esq, cont, k, ARQ);
    }
  }
}

//GRAVA OS TEMPOS DE EXECUÇÃO NO ARQUIVO DE SAIDA
void grava_tempos(clock_t tempo[], char *arquivo){
  FILE *ARQ;

  //Abrindo arquivo
  ARQ = fopen(arquivo, "a");

  if(ARQ == NULL){
    printf("Arquivo inexistente");
  }
  else{
    
    fprintf(ARQ,"\n\nTempo total de execução do programa: %ld ms\n",tempo[0]);
    fprintf(ARQ,"Tempo de leitura do corpus: %ld ms\n",tempo[1]);
    fprintf(ARQ,"Tempo de cálculo das medidas estatísticas: %ld ms\n",tempo[2]);
    fprintf(ARQ,"Tempo de consulta na estrutura de dados de saída: %ld ms\n",tempo[3]);

    fclose(ARQ);
    
  }
}
