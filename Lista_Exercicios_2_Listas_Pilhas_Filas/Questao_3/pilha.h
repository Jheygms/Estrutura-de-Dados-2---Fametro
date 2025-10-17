#ifndef PILHA_H
#define PILHA_H
#include <stdbool.h>

typedef struct Frame {
  char func[48];
  int sp;
  struct Frame *baixo;
} Frame;

typedef struct {
  Frame *topo;
} Pilha;

void pilha_init(Pilha *p);
bool push(Pilha *p, const char *func, int sp);
bool pop(Pilha *p, Frame *out);
bool peek(Pilha *p, Frame *out);
bool vazia(Pilha *p);
void limpar(Pilha *p);

#endif
