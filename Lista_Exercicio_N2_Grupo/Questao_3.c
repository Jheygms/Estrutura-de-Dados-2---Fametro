/* AVALIADOR RPN - Solução para Desafio de Estágio
 Este programa avalia uma expressão matemática em Notação Polonesa Reversa (RPN)
  passada como argumento de linha de comando.
  Ele utiliza uma pilha dinâmica (lista ligada) para realizar os cálculos.*/

#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>   
#include <ctype.h>    

//Estrutura da pilha 
typedef struct Node {
    double value;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

//funções da pilha
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "Erro: Falha na alocacao de memoria para a pilha.\n");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    return stack;
}

int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

void push(Stack* stack, double value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Erro: Falha na alocacao de memoria para o no da pilha.\n");
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

double pop(Stack* stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Erro critico: Tentativa de pop() em pilha vazia.\n");
        exit(EXIT_FAILURE);
    }

    Node* temp = stack->top;
    double value = temp->value;
    stack->top = temp->next;
    free(temp); 
    return value;
}

void freeStack(Stack* stack) {
    while (!isEmpty(stack)) {
        Node* temp = stack->top;
        stack->top = temp->next;
        free(temp);
    }
    free(stack); 
}

//avaliador
double evaluateRPN(char* expression) {
    Stack* stack = createStack();

    const char* delim = " ";
    
    char* token = strtok(expression, delim);

    while (token != NULL) {
        if (strlen(token) == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) {
            char operator = token[0];

            if (isEmpty(stack)) {
                fprintf(stderr, "Erro: Expressao malformada (operandos insuficientes para o operador '%c').\n", operator);
                freeStack(stack);
                exit(EXIT_FAILURE);
            }
            double op2 = pop(stack);

            if (isEmpty(stack)) {
                fprintf(stderr, "Erro: Expressao malformada (operandos insuficientes para o operador '%c').\n", operator);
                freeStack(stack);
                exit(EXIT_FAILURE);
            }
            double op1 = pop(stack);

            double result = 0.0;
            switch (operator) {
                case '+':
                    result = op1 + op2;
                    break;
                case '-':
                    result = op1 - op2; 
                    break;
                case '*':
                    result = op1 * op2;
                    break;
                case '/':
                    if (op2 == 0.0) {
                        fprintf(stderr, "Erro: Tentativa de divisao por zero.\n");
                        freeStack(stack);
                        exit(EXIT_FAILURE);
                    }
                    result = op1 / op2;
                    break;
            }
            push(stack, result);

        } else {
            double value = atof(token);
            push(stack, value);
        }

        token = strtok(NULL, delim);
    }

    double finalResult = pop(stack);

    if (!isEmpty(stack)) {
        fprintf(stderr, "Erro: Expressao malformada (operandos em excesso).\n");
        freeStack(stack);
        exit(EXIT_FAILURE);
    }

    freeStack(stack);

    return finalResult;
}

//programa principal 
int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s \"<expressao RPN>\"\n", argv[0]);
        fprintf(stderr, "Exemplo: %s \"10 5 +\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    char* expressionCopy = (char*)malloc(strlen(argv[1]) + 1);
    if (expressionCopy == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memoria para a expressao.\n");
        return EXIT_FAILURE;
    }
    strcpy(expressionCopy, argv[1]);

    double result = evaluateRPN(expressionCopy);

    printf("Resultado: %.2f\n", result);

    free(expressionCopy);

    return EXIT_SUCCESS; 
}