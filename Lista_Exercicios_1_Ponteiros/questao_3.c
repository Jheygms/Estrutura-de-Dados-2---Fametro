/*3. Endereços de Memória: Declare uma variável inteira e um ponteiro para
inteiro. Atribua o endereço da variável ao ponteiro. Imprima o valor da
variável, o endereço da variável, o valor do ponteiro (que deve ser o mesmo
endereço da variável) e o valor apontado pelo ponteiro.*/

#include <stdio.h>
int main (){
    int var = 42;
    int *ptr = &var;

    printf("Valor da variavel: %d\n", var);
    printf("Endereco da variavel: %p\n", (void*)&var);
    printf("Valor do ponteiro: %p\n", (void*)ptr);
    printf("Valor apontado pelo ponteiro: %d\n", *ptr);

    return 0;
}