#include "fila.h"
#include <stdio.h>
#include <string.h>

typedef struct { char id[24]; int qtd; } Venda;
int main(){
  Fila f; inicializar(&f);
  int estoque=0; long total_vendido=0; int atendidos=0;
  Venda top[3]={{"",0},{"",0},{"",0}};
  Venda nao_atendidos[1000]; int n_na=0;

  printf("Estoque inicial: "); scanf("%d",&estoque);
  printf("Comandos: ADD <id> <qtd> | START | REL | EXIT\n");

  char cmd[16];
  while(1){
    if(scanf("%15s", cmd)!=1) break;

    if(strcmp(cmd,"ADD")==0){
      Cliente c; scanf("%23s %d", c.id, &c.qtd);
      enfileirar(&f, c);
    } else if(strcmp(cmd,"START")==0){
      Cliente c;
      while(!vazia(&f) && estoque>0){
        desenfileirar(&f, &c);
        if(c.qtd <= estoque){
          estoque -= c.qtd; total_vendido += c.qtd; atendidos++;
          for(int i=0;i<3;i++){
            if(c.qtd > top[i].qtd){
              for(int j=2;j>i;j--) top[j]=top[j-1];
              strcpy(top[i].id, c.id); top[i].qtd=c.qtd; break;
            }
          }
        } else { 
          printf("Cliente %s pediu %d, disponivel %d. Aceita? (S/N): ",
                 c.id, c.qtd, estoque);
          char resp[8]; scanf("%7s", resp);
          if(estoque>0 && (resp[0]=='S'||resp[0]=='s')){
            total_vendido += estoque; c.qtd = estoque; estoque = 0; atendidos++;
            for(int i=0;i<3;i++){
              if(c.qtd > top[i].qtd){
                for(int j=2;j>i;j--) top[j]=top[j-1];
                strcpy(top[i].id, c.id); top[i].qtd=c.qtd; break;
              }
            }
          } else {
            if(n_na<1000){ strcpy(nao_atendidos[n_na].id,c.id); nao_atendidos[n_na].qtd=c.qtd; n_na++; }
          }
        }
      }
      if(estoque==0) printf("Estoque esgotado. Fim do processamento.\n");
    } else if(strcmp(cmd,"REL")==0){
      printf("TOTAL VENDIDO: %ld\nATENDIDOS: %d\nRESTANTE: %d\n", total_vendido, atendidos, estoque);
      printf("TOP-3 COMPRAS:\n");
      for(int i=0;i<3;i++) if(top[i].qtd>0) printf("%d) %s - %d\n", i+1, top[i].id, top[i].qtd);
      printf("NAO ATENDIDOS:\n");
      for(int i=0;i<n_na;i++) printf("- %s (%d)\n", nao_atendidos[i].id, nao_atendidos[i].qtd);
    } else if(strcmp(cmd,"EXIT")==0){
      break;
    } else {
      printf("Comando invalido\n");
    }
  }
  limpar(&f);
  return 0;
}
