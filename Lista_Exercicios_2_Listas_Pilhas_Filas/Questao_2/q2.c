/*Questão 2 — Fila para Venda Digital de Ingressos 
Uma plataforma abre vendas às 10h e cria uma única fila de espera de clientes. Ao 
iniciar a venda, o sistema processa pedidos em ordem FIFO enquanto houver ingressos.
Considere as seguintes estruturas para Cliente e para a fila:
Operações:
1. void inicializar(Fila*);
2. void enfileirar(Fila*, Cliente); // enqueue
3. bool desenfileirar(Fila*, Cliente *out); // dequeue
4. bool vazia(Fila*);
5. void limpar(Fila*);
Aplicação (em main.c):
Parâmetro inicial: estoque_inicial informado pelo usuário no começo da execução.*/

#include "fila.h"
#include <stdlib.h>
#include <string.h>

static Cliente* novo(const Cliente *c){
  Cliente *n=(Cliente*)malloc(sizeof(Cliente));
  if(!n) return NULL; *n=*c; n->prox=NULL; return n;
}

void inicializar(Fila *f){ f->ini=f->fim=NULL; }

void enfileirar(Fila *f, Cliente c){
  Cliente *n=novo(&c); if(!n) return;
  if(!f->fim){ f->ini=f->fim=n; } else { f->fim->prox=n; f->fim=n; }
}

bool desenfileirar(Fila *f, Cliente *out){
  if(!f->ini) return false;
  Cliente *n=f->ini; if(out) *out=*n;
  f->ini=n->prox; if(!f->ini) f->fim=NULL;
  free(n); return true;
}

bool vazia(Fila *f){ return f->ini==NULL; }

void limpar(Fila *f){
  Cliente tmp;
  while(desenfileirar(f,&tmp)){}
}
