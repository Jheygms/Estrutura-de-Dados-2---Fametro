/*8. Calculadora Básica: Crie uma função que receba dois números de ponto
flutuante e ponteiros para outras quatro variáveis de ponto flutuante. A
função deve calcular a soma, subtração, multiplicação e divisão dos dois
primeiros números e armazenar os resultados nas variáveis apontadas pelos
ponteiros*/

#include <stdio.h>
void calculadora(float a, float b, float *soma, float *subtracao, float *multiplicacao, float *divisao){
    *soma = a + b;
    *subtracao = (a - b);
    *multiplicacao = (a * b);
    if (b != 0){
        *divisao = a / b;
    } else{ 
        *divisao = 0;
    }
    }

int main (){
    float a = 10.0, b = 2.0;
    float soma, subtracao, multiplicacao, divisao;
    calculadora(a, b, &soma, &subtracao, &multiplicacao, &divisao);
    printf("Soma: %.2f\n", soma);
    printf("Subtracao: %.2f\n", subtracao);
    printf("Multiplicacao: %.2f\n", multiplicacao);
    if (b != 0){
        printf("Divisao: %.2f\n", divisao);
    } else {
        printf("Divisao por zero nao pode, tente novamente!\n");

        return 1;
    }
}
