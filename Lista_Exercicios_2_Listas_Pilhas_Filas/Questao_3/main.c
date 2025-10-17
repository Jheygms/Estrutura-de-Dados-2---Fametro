#include "pilha.h"
#include <stdio.h>
#include <string.h>

int main(){
  Pilha P; pilha_init(&P);
  char cmd[16];
  printf("Comandos: CALL <nomeFunc> <sp> | RET | PEEK | TRACE | EXIT\n");
  while(1){
    if(scanf("%15s", cmd)!=1) break;

    if(strcmp(cmd,"CALL")==0){
      char nome[48]; int sp; scanf("%47s %d", nome, &sp);
      push(&P, nome, sp);
    } else if(strcmp(cmd,"RET")==0){
      Frame f;
      if(!pop(&P,&f)) printf("Pilha vazia (RET invalido)\n");
    } else if(strcmp(cmd,"PEEK")==0){
      Frame f;
      if(peek(&P,&f)) printf("Topo: %s sp=%d\n", f.func, f.sp);
      else printf("Pilha vazia\n");
    } else if(strcmp(cmd,"TRACE")==0){
      int nivel=0; Frame *cur=P.topo;
      while(cur){
        printf("#%d %s sp=%d\n", nivel, cur->func, cur->sp);
        cur = cur->baixo; nivel++;
      }
    } else if(strcmp(cmd,"EXIT")==0){
      break;
    } else {
      printf("Comando invalido\n");
    }
  }
  limpar(&P);
  return 0;
}
