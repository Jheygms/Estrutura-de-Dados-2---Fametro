#ifndef PRODUTO_H
#define PRODUTO_H
#include <stdbool.h>

typedef struct Produto {
  char codigo[16];
  char nome[64];
  int qtd;
  float preco;
  struct Produto *prox;
} Produto;

Produto* inserir_inicio(Produto *L, Produto p);
Produto* inserir_ordenado_por_codigo(Produto *L, Produto p); // se existir: atualiza qtd/preco
Produto* remover_por_codigo(Produto *L, const char *codigo);
Produto* ajustar_quantidade(Produto *L, const char *codigo, int delta_qtd); // sem ficar negativa
Produto* buscar(Produto *L, const char *codigo);
void     listar(Produto *L);
Produto* limpar(Produto *L);

void relatorio(Produto *L);

#endif
