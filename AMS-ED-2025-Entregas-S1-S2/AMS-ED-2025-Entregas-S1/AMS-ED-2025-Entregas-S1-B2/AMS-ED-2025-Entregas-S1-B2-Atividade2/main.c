/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: B1-Atividade 5                          */
/*             Objetivo: <<  troca da estrutura de lista ligada para pilha  >>      */
/*                                                                                  */
/*                                  Autor: Joaquim diglio                           */
/*                                                                   Data:01/04/2025*/
/*----------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 4

typedef struct {
    double dados[MAX];
    int topo;
} Pilha;

Pilha* criar_pilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = -1;
    return p;
}

int vazia(Pilha* p) {
    return p->topo == -1;
}

int cheia(Pilha* p) {
    return p->topo == MAX - 1;
}

void push(Pilha* p, double dado) {
    if (!cheia(p)) {
        p->dados[++(p->topo)] = dado;
    } else {
        printf("Pilha cheia!\n");
    }
}

double pop(Pilha* p) {
    if (!vazia(p)) {
        return p->dados[(p->topo)--];
    } else {
        printf("Pilha vazia!\n");
        return -1;
    }
}

double top(Pilha* p) {
    if (!vazia(p)) {
        return p->dados[p->topo];
    } else {
        printf("Pilha vazia!\n");
        return -1;
    }
}

void processar_rpn(Pilha* p, char* entrada) {
    char* token = strtok(entrada, " ");
    
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(p, atof(token));
        } else {
            double b = pop(p);
            double a = pop(p);
            double resultado;

            switch (token[0]) {
                case '+':
                    resultado = a + b;
                    break;
                case '-':
                    resultado = a - b;
                    break;
                case '*':
                    resultado = a * b;
                    break;
                case '/':
                    if (b == 0) {
                        printf("Erro: Divisão por zero!\n");
                        return;
                    }
                    resultado = a / b;
                    break;
                default:
                    printf("Operador inválido: %s\n", token);
                    return;
            }
            push(p, resultado);
        }
        token = strtok(NULL, " ");
    }
}

void converter_para_algébrica(char* entrada) {
    char* token = strtok(entrada, " ");
    char formula[1000] = "";
    int op_count = 0;

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            strcat(formula, token);
            strcat(formula, " ");
        } else {
            char operador[2] = { token[0], '\0' };
            strcat(formula, "(");
            strcat(formula, operador);
            strcat(formula, " ");
            op_count++;
        }
        token = strtok(NULL, " ");
    }
    
    printf("Fórmula Algébrica: %s\n", formula);
}

int main() {
    Pilha* p = criar_pilha();
    char entrada[100];

    printf("Digite a fórmula em RPN (exemplo: 3 4 + 5 *): ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = 0;

    processar_rpn(p, entrada);

    printf("Resultado: %.2f\n", top(p));

    converter_para_algébrica(entrada);

    free(p);
    return 0;
}
