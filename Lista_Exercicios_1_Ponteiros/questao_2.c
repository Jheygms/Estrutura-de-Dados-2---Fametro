/*2. Maior e Menor: Escreva uma função que receba um array de inteiros e seu 
tamanho, e através de ponteiros, retorne o maior e o menor elemento do 
array. A função deve ter o seguinte protótipo: void encontrarMaiorMenor(int 
*array, int tamanho, int *maior, int *menor);*/

#include <stdio.h>

    void encontrarMaiorMenor(int *array, int tamanho, int *maior, int *menor){

        *maior = array[0];
        *menor = array[0];

        for(int i = 1, j = tamanho; i < j; i++){
            if (array[i] > *maior){
                *maior = array[i];
            }
        }
    }
    
    int main() {
    int numeros[] = {7, 2, 9, 4, 1, 5};
    int tamanho = 6;
    int maior, menor;

    encontrarMaiorMenor(numeros, tamanho, &maior, &menor);

    printf("Maior: %d, Menor: %d\n", maior, menor);
    return 0;
}