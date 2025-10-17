#include "pilha.h"
#include <stdlib.h>
#include <string.h>

void pilha_init(Pilha *p){ p->topo=NULL; }

bool push(Pilha *p, const char *func, int sp){
  Frame *n=(Frame*)malloc(sizeof(Frame));
  if(!n) return false;
  strncpy(n->func, func, sizeof(n->func)-1); n->func[sizeof(n->func)-1]='\0';
  n->sp=sp; n->baixo=p->topo; p->topo=n; return true;
}

bool pop(Pilha *p, Frame *out){
  if(!p->topo) return false;
  Frame *n=p->topo; if(out) *out=*n; p->topo=n->baixo; free(n); return true;
}

bool peek(Pilha *p, Frame *out){
  if(!p->topo) return false; if(out) *out=*p->topo; return true;
}

bool vazia(Pilha *p){ return p->topo==NULL; }

void limpar(Pilha *p){
  Frame x; while(pop(p,&x)){}
}
