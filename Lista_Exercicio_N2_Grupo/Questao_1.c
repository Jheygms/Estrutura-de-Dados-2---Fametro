#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOME 40
#define MAX_TEL  15
#define MAX_CEL  15
#define MAX_EMAIL 40

typedef struct {
    int dia;
    int mes;
} Data;

typedef struct {
    char nome[MAX_NOME + 1];
    char telefone[MAX_TEL + 1];
    char celular[MAX_CEL + 1];
    char email[MAX_EMAIL + 1];
    Data aniversario;
} Contato;

struct elemento {
    Contato info;
    struct elemento* prox;
};
typedef struct elemento Elemento;

void read_line(const char *prompt, char *buffer, size_t size) {
    if (prompt) printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
}

int read_int(const char *prompt, int min, int max) {
    char line[64];
    int val;
    while (1) {
        read_line(prompt, line, sizeof(line));
        if (sscanf(line, "%d", &val) == 1) {
            if ((min == max && min == -1) || (val >= min && val <= max)) return val;
            if (!(min == max && min == -1)) {
                printf("Valor fora do intervalo [%d - %d]. Tente novamente.\n", min, max);
            }
        } else {
            printf("Entrada inválida. Digite um número.\n");
        }
    }
}

int str_case_cmp(const char *a, const char *b) {
    while (*a && *b) {
        char ca = tolower((unsigned char)*a);
        char cb = tolower((unsigned char)*b);
        if (ca != cb) return (unsigned char)ca - (unsigned char)cb;
        a++; b++;
    }
    return (unsigned char)tolower((unsigned char)*a) - (unsigned char)tolower((unsigned char)*b);
}

Elemento* cria_agenda() {
    return NULL;
}

void insere_contato(Elemento **head, Contato c) {
    Elemento *novo = (Elemento*) malloc(sizeof(Elemento));
    if (!novo) {
        fprintf(stderr, "Erro de alocacao.\n");
        return;
    }
    novo->info = c;
    novo->prox = NULL;
    if (*head == NULL) {
        *head = novo;
    } else {
        Elemento *p = *head;
        while (p->prox) p = p->prox;
        p->prox = novo;
    }
}

void lista_contatos(Elemento *head) {
    if (!head) {
        printf("Agenda vazia.\n");
        return;
    }
    int idx = 1;
    for (Elemento *p = head; p != NULL; p = p->prox) {
        Contato *c = &p->info;
        printf("---- Contato %d ----\n", idx++);
        printf("Nome: %s\n", c->nome);
        printf("Telefone: %s\n", c->telefone);
        printf("Celular: %s\n", c->celular);
        printf("Email: %s\n", c->email);
        printf("Aniversario: %02d/%02d\n", c->aniversario.dia, c->aniversario.mes);
    }
}

Elemento* busca_contato(Elemento *head, const char *nome) {
    for (Elemento *p = head; p != NULL; p = p->prox) {
        if (str_case_cmp(p->info.nome, nome) == 0) return p;
    }
    return NULL;
}

void remove_contato(Elemento **head) {
    if (!*head) {
        printf("Agenda vazia. Nada a remover.\n");
        return;
    }
    char nome_busca[MAX_NOME + 1];
    read_line("Digite o nome do contato a remover: ", nome_busca, sizeof(nome_busca));
    if (nome_busca[0] == '\0') {
        printf("Nome vazio. Operacao cancelada.\n");
        return;
    }
    Elemento *p = *head;
    Elemento *ant = NULL;
    while (p) {
        if (str_case_cmp(p->info.nome, nome_busca) == 0) {
            if (ant == NULL) {
                *head = p->prox;
            } else {
                ant->prox = p->prox;
            }
            free(p);
            printf("Contato removido com sucesso.\n");
            return;
        }
        ant = p;
        p = p->prox;
    }
    printf("Contato '%s' nao encontrado.\n", nome_busca);
}

void atualiza_contato(Elemento *head) {
    if (!head) {
        printf("Agenda vazia.\n");
        return;
    }
    char nome_busca[MAX_NOME + 1];
    read_line("Digite o nome do contato a editar: ", nome_busca, sizeof(nome_busca));
    if (nome_busca[0] == '\0') {
        printf("Nome vazio. Operacao cancelada.\n");
        return;
    }
    Elemento *p = busca_contato(head, nome_busca);
    if (!p) {
        printf("Contato '%s' nao encontrado.\n", nome_busca);
        return;
    }
    Contato *c = &p->info;
    char buffer[128];
    printf("Deixe em branco para manter o valor atual.\n");
    printf("Nome atual: %s\n", c->nome);
    read_line("Novo nome: ", buffer, sizeof(buffer));
    if (buffer[0] != '\0') strncpy(c->nome, buffer, MAX_NOME), c->nome[MAX_NOME] = '\0';
    printf("Telefone atual: %s\n", c->telefone);
    read_line("Novo telefone: ", buffer, sizeof(buffer));
    if (buffer[0] != '\0') strncpy(c->telefone, buffer, MAX_TEL), c->telefone[MAX_TEL] = '\0';
    printf("Celular atual: %s\n", c->celular);
    read_line("Novo celular: ", buffer, sizeof(buffer));
    if (buffer[0] != '\0') strncpy(c->celular, buffer, MAX_CEL), c->celular[MAX_CEL] = '\0';
    printf("Email atual: %s\n", c->email);
    read_line("Novo email: ", buffer, sizeof(buffer));
    if (buffer[0] != '\0') strncpy(c->email, buffer, MAX_EMAIL), c->email[MAX_EMAIL] = '\0';
    printf("Aniversario atual: %02d/%02d\n", c->aniversario.dia, c->aniversario.mes);
    read_line("Novo dia (ou enter para manter): ", buffer, sizeof(buffer));
    if (buffer[0] != '\0') {
        int dia;
        if (sscanf(buffer, "%d", &dia) == 1 && dia >= 1 && dia <= 31) {
            c->aniversario.dia = dia;
        } else {
            printf("Dia invalido. Mantido o valor anterior.\n");
        }
    }
    read_line("Novo mes (ou enter para manter): ", buffer, sizeof(buffer));
    if (buffer[0] != '\0') {
        int mes;
        if (sscanf(buffer, "%d", &mes) == 1 && mes >= 1 && mes <= 12) {
            c->aniversario.mes = mes;
        } else {
            printf("Mes invalido. Mantido o valor anterior.\n");
        }
    }
    printf("Contato atualizado com sucesso.\n");
}

void busca_contato_menu(Elemento *head) {
    if (!head) {
        printf("Agenda vazia.\n");
        return;
    }
    char nome_busca[MAX_NOME + 1];
    read_line("Digite o nome do contato a buscar: ", nome_busca, sizeof(nome_busca));
    if (nome_busca[0] == '\0') {
        printf("Nome vazio. Operacao cancelada.\n");
        return;
    }
    Elemento *p = busca_contato(head, nome_busca);
    if (!p) {
        printf("Contato '%s' nao encontrado.\n", nome_busca);
        return;
    }
    Contato *c = &p->info;
    printf("---- Contato encontrado ----\n");
    printf("Nome: %s\n", c->nome);
    printf("Telefone: %s\n", c->telefone);
    printf("Celular: %s\n", c->celular);
    printf("Email: %s\n", c->email);
    printf("Aniversario: %02d/%02d\n", c->aniversario.dia, c->aniversario.mes);
}

void remove_duplicados(Elemento **head) {
    if (!*head) {
        printf("Agenda vazia.\n");
        return;
    }
    Elemento *i = *head;
    int removidos = 0;
    while (i) {
        Elemento *ant = i;
        Elemento *j = i->prox;
        while (j) {
            if (str_case_cmp(i->info.nome, j->info.nome) == 0) {
                ant->prox = j->prox;
                Elemento *tmp = j;
                j = j->prox;
                free(tmp);
                removidos++;
            } else {
                ant = j;
                j = j->prox;
            }
        }
        i = i->prox;
    }
    printf("Removidos %d contatos duplicados (por nome).\n", removidos);
}

void libera_agenda(Elemento **head) {
    Elemento *p = *head;
    while (p) {
        Elemento *tmp = p;
        p = p->prox;
        free(tmp);
    }
    *head = NULL;
}

Contato cria_contato_por_input() {
    Contato c;
    char buffer[128];
    read_line("Nome: ", buffer, sizeof(buffer));
    strncpy(c.nome, buffer, MAX_NOME); c.nome[MAX_NOME] = '\0';
    read_line("Telefone: ", buffer, sizeof(buffer));
    strncpy(c.telefone, buffer, MAX_TEL); c.telefone[MAX_TEL] = '\0';
    read_line("Celular: ", buffer, sizeof(buffer));
    strncpy(c.celular, buffer, MAX_CEL); c.celular[MAX_CEL] = '\0';
    read_line("Email: ", buffer, sizeof(buffer));
    strncpy(c.email, buffer, MAX_EMAIL); c.email[MAX_EMAIL] = '\0';
    c.aniversario.dia = read_int("Dia do aniversario (1-31): ", 1, 31);
    c.aniversario.mes = read_int("Mes do aniversario (1-12): ", 1, 12);
    return c;
}

int main(void) {
    Elemento *agenda = cria_agenda();
    int opcao;
    while (1) {
        printf("\n===== AGENDA TELEFONICA =====\n");
        printf("1. Inserir Contato\n");
        printf("2. Listar Contatos\n");
        printf("3. Buscar Contato\n");
        printf("4. Editar Contato\n");
        printf("5. Remover Contato\n");
        printf("6. Remover Duplicados\n");
        printf("7. Sair\n");
        opcao = read_int("Escolha uma opcao: ", 1, 7);
        switch (opcao) {
            case 1: {
                printf("-- Inserir novo contato --\n");
                Contato c = cria_contato_por_input();
                insere_contato(&agenda, c);
                printf("Contato inserido com sucesso.\n");
                break;
            }
            case 2:
                printf("-- Lista de contatos --\n");
                lista_contatos(agenda);
                break;
            case 3:
                printf("-- Buscar contato --\n");
                busca_contato_menu(agenda);
                break;
            case 4:
                printf("-- Editar contato --\n");
                atualiza_contato(agenda);
                break;
            case 5:
                printf("-- Remover contato --\n");
                remove_contato(&agenda);
                break;
            case 6:
                printf("-- Remover duplicados --\n");
                remove_duplicados(&agenda);
                break;
            case 7:
                printf("Saindo... liberando memoria.\n");
                libera_agenda(&agenda);
                return 0;
            default:
                printf("Opcao invalida.\n");
        }
    }
    return 0;
}
