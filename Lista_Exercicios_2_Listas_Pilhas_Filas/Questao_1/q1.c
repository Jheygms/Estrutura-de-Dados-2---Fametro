/*Questão 1 — Lista ligada para Controle de Estoque 
Uma loja mantém um catálogo de produtos com entradas, saídas e ajustes ao longo 
do dia. Implemente uma lista simplesmente encadeada para gerenciar o estoque.
Considere a seguinte estrutura para Produto (você pode realizar modificações somente 
para adicionar novos atributos).
Operações (todas com malloc/free):
1. Produto* inserir_inicio(Produto *L, Produto p);
2. Produto* inserir_ordenado_por_codigo(Produto *L, Produto p); (se o código já 
existir, atualizar qtd e preco)
3. Produto* remover_por_codigo(Produto *L, const char *codigo);
4. Produto* ajustar_quantidade(Produto *L, const char *codigo, int delta_qtd); (não 
permitir qtd negativa)
5. Produto* buscar(Produto *L, const char *codigo);
6. void listar(Produto *L);
7. Produto* limpar(Produto *L);
Aplicação (em main.c): menu textual com comandos*/

#include "produto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Produto* novo(const Produto *p){
  Produto *n = (Produto*)malloc(sizeof(Produto));
  if(!n) return NULL;
  *n = *p;
  n->prox = NULL;
  return n;
}

Produto* inserir_inicio(Produto *L, Produto p){
  Produto *n = novo(&p);
  if(!n) return L;
  n->prox = L;
  return n;
}

static int cmp_codigo(const char *a, const char *b){
  return strcmp(a,b);
}

Produto* inserir_ordenado_por_codigo(Produto *L, Produto p){
  for(Produto *cur=L; cur; cur=cur->prox){
    if(strcmp(cur->codigo, p.codigo)==0){
      cur->qtd   = p.qtd;
      cur->preco = p.preco;
      strncpy(cur->nome, p.nome, sizeof(cur->nome)-1);
      cur->nome[sizeof(cur->nome)-1]='\0';
      return L;
    }
  }
  Produto *n = novo(&p);
  if(!n) return L;
  if(!L || cmp_codigo(p.codigo, L->codigo) < 0){
    n->prox = L;
    return n;
  }
  Produto *ant=L, *cur=L->prox;
  while(cur && cmp_codigo(p.codigo, cur->codigo) > 0){
    ant=cur; cur=cur->prox;
  }
  ant->prox = n; n->prox = cur;
  return L;
}

Produto* remover_por_codigo(Produto *L, const char *codigo){
  Produto *ant=NULL, *cur=L;
  while(cur){
    if(strcmp(cur->codigo,codigo)==0){
      if(ant) ant->prox = cur->prox; else L = cur->prox;
      free(cur);
      return L;
    }
    ant=cur; cur=cur->prox;
  }
  return L;
}

Produto* ajustar_quantidade(Produto *L, const char *codigo, int delta_qtd){
  for(Produto *cur=L; cur; cur=cur->prox){
    if(strcmp(cur->codigo,codigo)==0){
      int nova = cur->qtd + delta_qtd;
      if(nova < 0) nova = 0;
      cur->qtd = nova;
      return L;
    }
  }
  return L;
}

Produto* buscar(Produto *L, const char *codigo){
  for(Produto *cur=L; cur; cur=cur->prox)
    if(strcmp(cur->codigo,codigo)==0) return cur;
  return NULL;
}

void listar(Produto *L){
  for(Produto *cur=L; cur; cur=cur->prox)
    printf("%s | \"%s\" | qtd=%d | preco=%.2f\n",
           cur->codigo, cur->nome, cur->qtd, cur->preco);
}

Produto* limpar(Produto *L){
  while(L){
    Produto *tmp=L; L=L->prox; free(tmp);
  }
  return NULL;
}

void relatorio(Produto *L){
  int distintos=0; double total=0.0;
  Produto *maior=NULL; double maior_valor=0.0;
  for(Produto *cur=L; cur; cur=cur->prox){
    distintos++;
    double val = (double)cur->qtd * (double)cur->preco;
    total += val;
    if(!maior || val>maior_valor){ maior=cur; maior_valor=val; }
  }
  printf("DISTINTOS: %d\nTOTAL ESTOQUE: %.2f\n", distintos, total);
  if(maior)
    printf("MAIOR IMOBILIZADO: %s \"%s\" qtd=%d preco=%.2f (%.2f)\n",
      maior->codigo, maior->nome, maior->qtd, maior->preco, maior_valor);
}

