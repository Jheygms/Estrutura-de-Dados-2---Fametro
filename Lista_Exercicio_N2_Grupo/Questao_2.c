#include <stdio.h>
#include <stdlib.h>

// 1. Função que recebe um valor n e cria dinamicamente um vetor de n elementos e retorna um ponteiro.
int* cria_vetor(int n) {
   
    if (n <= 0) {
        return NULL; 
    }
    
    // int* vetor = (int*) malloc(n * sizeof(int));
    
    int* vetor = (int*) calloc(n, sizeof(int));

    if (vetor == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }
    return vetor;
}

// 2. Função que recebe um ponteiro para um vetor e um valor n e imprima os n elementos desse vetor.
void imprime_vetor(int* vetor, int n) {
    if (vetor == NULL || n <= 0) {
        printf("Vetor vazio ou tamanho inválido.\n");
        return;
    }
    printf("Elementos do vetor:\n");
    for (int i = 0; i < n; i++) {
        printf("Elemento[%d]: %d\n", i, vetor[i]);
    }
}

// 3. Função que receba um ponteiro para um vetor e libere esta área de memória.
void libera_vetor(int* vetor) {
    if (vetor != NULL) {
       
        free(vetor);
    }
}

int main() {
    int n;
    int* meu_vetor = NULL;

    
    printf("Digite o número de elementos (n) do vetor: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Tamanho inválido. Encerrando o programa.\n");
        return 1;
    }

   
    meu_vetor = cria_vetor(n);

    // Se a alocação falhar (já tratada na função, mas boa prática)
    if (meu_vetor == NULL) {
        return 1;
    }
    
    
    printf("Digite os %d elementos do vetor:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Elemento[%d]: ", i);
        if (scanf("%d", &meu_vetor[i]) != 1) {
            printf("Entrada inválida. Preenchimento interrompido.\n");
            break; // Sai do loop em caso de erro na leitura
        }
    }
    
    
    imprime_vetor(meu_vetor, n);

   
    libera_vetor(meu_vetor);
    printf("Memória do vetor liberada com sucesso.\n");

    return 0;
}
