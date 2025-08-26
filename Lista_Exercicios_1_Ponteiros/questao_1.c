/*1. Troca de Valores: Crie uma função que receba dois ponteiros para inteiros 
como parâmetros e troque os valores das variáveis para as quais eles 
apontam. No main, declare duas variáveis, leia seus valores, chame a 
função e imprima os valores trocados.*/

#include <stdio.h>

void troca(int *J, int *G){
    int extra = *J;
    *J = *G;
    *G = extra;
}

int main (){
    int J=50, G= 10; 
    troca(&J, &G);
    printf("J = %d, G = %d\n", J, G);
    return 0;
}