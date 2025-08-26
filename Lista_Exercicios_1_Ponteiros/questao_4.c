/*4. Dobro do Valor: Escreva uma função chamada dobrar que receba um
ponteiro para um número inteiro como argumento e modifique o valor da
variável original para que seja o dobro do seu valor. Crie uma função main
para testar a sua função.*/

#include <stdio.h>
void dobrar(int *num)
{
    *num = *num * 2;
}

int main (){
    int valor = 30;
    dobrar(&valor);
    printf("Valor dobrado: %d\n", valor);

    return 0;
}