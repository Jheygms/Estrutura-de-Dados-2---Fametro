/*6. Contagem de Vogais e Consoantes: Escreva uma função que receba uma
string (ponteiro para char) como parâmetro e retorne, através de ponteiros
passados como argumentos, o número de vogais e o número de consoantes
na string. Protótipo: void contarVogaisConsoantes(char *str, int *vogais, int
*consoantes);*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

void contarVogaisConsoantes(char *str, int *vogais, int *consoantes){
    *vogais = 0;
    *consoantes = 0;
    char c;
    int len = strlen(str);

    for (int i = 0; i < len; i++){
        c = tolower(str[i]);
        if ((c >= 'a' && c <= 'z')){
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
            (*vogais)++;
        } else {
            (*consoantes)++;
        }
        }
    }
}

int main (){
    char str[] = "Hello, Todos!";
    int vogais, consoantes;
    contarVogaisConsoantes(str, &vogais, &consoantes);
    printf("Vogais: %d, Consoantes: %d\n", vogais, consoantes);
    return 0;
}