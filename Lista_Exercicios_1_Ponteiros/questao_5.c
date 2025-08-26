/*5. Cópia de String: Implemente uma função que copie uma string para outra
usando ponteiros. O protótipo deve ser: void copiarString(char *origem, char
*destino);. Não utilize a função strcpy() da biblioteca padrão.*/

#include <stdio.h>

void copiarString(char *origem, char *destino) {
    while (*origem != '\0'){
        *destino = *origem;
        origem++;
        destino++;
    }
    *destino = '\0';
}

int main (){
    char origem[] = "Hello, Todos!";
    char destino[50];
    copiarString(origem, destino);
    printf("STRING COPIADA: %s\n", destino);
    return 0;
}
