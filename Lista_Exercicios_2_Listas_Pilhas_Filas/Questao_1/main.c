#include "produto.h"
#include <stdio.h>
#include <string.h>

int main(){
  Produto *L=NULL;
  char cmd[16];
  printf("Comandos: ADD/UPD/DEL/FIND/LIST/REL/EXIT\n");
  while(1){
    if(scanf("%15s", cmd)!=1) break;

    if(strcmp(cmd,"ADD")==0){
      Produto p; char nome[128];
      if(scanf("%15s", p.codigo)!=1) continue;
      if(scanf(" \"%63[^\"]\"", nome)!=1) continue;
      strncpy(p.nome, nome, sizeof(p.nome)-1); p.nome[sizeof(p.nome)-1]='\0';
      scanf("%d %f", &p.qtd, &p.preco);
      L = inserir_ordenado_por_codigo(L, p);
    } else if(strcmp(cmd,"UPD")==0){
      char cod[16]; int delta; scanf("%15s %d", cod, &delta);
      L = ajustar_quantidade(L, cod, delta);
    } else if(strcmp(cmd,"DEL")==0){
      char cod[16]; scanf("%15s", cod);
      L = remover_por_codigo(L, cod);
    } else if(strcmp(cmd,"FIND")==0){
      char cod[16]; scanf("%15s", cod);
      Produto *x = buscar(L, cod);
      if(x) printf("%s \"%s\" qtd=%d preco=%.2f\n", x->codigo, x->nome, x->qtd, x->preco);
      else  printf("Nao encontrado\n");
    } else if(strcmp(cmd,"LIST")==0){
      listar(L);
    } else if(strcmp(cmd,"REL")==0){
      relatorio(L);
    } else if(strcmp(cmd,"EXIT")==0){
      break;
    } else {
      printf("Comando invalido\n");
    }
  }
  L = limpar(L);
  return 0;
}
