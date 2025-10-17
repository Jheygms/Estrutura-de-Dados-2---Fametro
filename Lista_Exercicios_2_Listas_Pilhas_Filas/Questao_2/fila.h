#ifndef FILA_H
#define FILA_H
#include <stdbool.h>

typedef struct Cliente {
  char id[24];
  int qtd;
  struct Cliente *prox;
} Cliente;

typedef struct {
  Cliente *ini, *fim;
} Fila;

void inicializar(Fila *f);
void enfileirar(Fila *f, Cliente c);
bool desenfileirar(Fila *f, Cliente *out);
bool vazia(Fila *f);
void limpar(Fila *f);

#endif
