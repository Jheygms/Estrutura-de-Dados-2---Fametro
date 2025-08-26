/*7. Inversão de String: Crie uma função que receba uma string e a inverta "inplace", ou seja, 
modificando a própria string original, utilizando ponteiros.
Por exemplo, "brasil" deve se tornar "lisarb"*/

#include <stdio.h>
#include <string.h>

void inverterString(char *str) {
    int inicio = 0;
    int fim = strlen(str) - 1;
    char temp;

    while (inicio < fim) {
        temp = *(str + inicio);
        *(str + inicio) = *(str + fim);
        *(str + fim) = temp;
        inicio++;
        fim--;
    }
}
int main(){
    char str[]="brasil";
    inverterString(str);
    printf("Sttring invertida: %s\n", str);
    return 0;
}