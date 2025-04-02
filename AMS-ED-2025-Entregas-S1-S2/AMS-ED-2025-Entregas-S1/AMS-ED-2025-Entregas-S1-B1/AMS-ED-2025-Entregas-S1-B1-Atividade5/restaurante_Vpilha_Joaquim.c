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

typedef enum {
    PENDENTE,
    EM_PREPARO,
    PRONTO,
    ENTREGUE
} StatusPedido;

typedef struct Pedido {
    int numero_pedido;
    char nome_cliente[100];
    char descricao_prato[100];
    int quantidade;
    StatusPedido status;
    struct Pedido* abaixo;
} Pedido;

Pedido* criar_pilha() {
    return NULL;
}

Pedido* criar_pedido(int numero, const char* nome_cliente, const char* descricao, int quantidade, StatusPedido status) {
    Pedido* novo_pedido = (Pedido*) malloc(sizeof(Pedido));
    if (novo_pedido == NULL) {
        printf("Erro ao alocar memória para novo pedido!\n");
        return NULL;
    }
    
    novo_pedido->numero_pedido = numero;
    strcpy(novo_pedido->nome_cliente, nome_cliente);
    strcpy(novo_pedido->descricao_prato, descricao);
    novo_pedido->quantidade = quantidade;
    novo_pedido->status = status;
    novo_pedido->abaixo = NULL;

    return novo_pedido;
}

void empilhar_pedido(Pedido** pilha, int numero, const char* nome_cliente, const char* descricao, int quantidade, StatusPedido status) {
    Pedido* novo_pedido = criar_pedido(numero, nome_cliente, descricao, quantidade, status);
    if (novo_pedido == NULL) return;

    novo_pedido->abaixo = *pilha;
    *pilha = novo_pedido;
}

Pedido* obter_pedido(Pedido* pilha, int numero) {
    Pedido* temp = pilha;
    while (temp != NULL) {
        if (temp->numero_pedido == numero) {
            return temp;
        }
        temp = temp->abaixo;
    }
    return NULL;
}

int atualizar_status(Pedido* pilha, int numero, StatusPedido novo_status) {
    Pedido* pedido = obter_pedido(pilha, numero);
    if (pedido != NULL) {
        pedido->status = novo_status;
        return 1;
    }
    return 0;
}

int desempilhar_pedido(Pedido** pilha, int numero) {
    Pedido* temp = *pilha;
    if (temp != NULL && temp->numero_pedido == numero) {
        *pilha = temp->abaixo;
        free(temp);
        return 1;
    }
    return 0;
}

void liberar_pilha(Pedido* pilha) {
    Pedido* temp;
    while (pilha != NULL) {
        temp = pilha;
        pilha = pilha->abaixo;
        free(temp);
    }
}

StatusPedido ler_status() {
    int status;
    printf("Digite o status do pedido (0 - PENDENTE, 1 - EM_PREPARO, 2 - PRONTO, 3 - ENTREGUE): ");
    scanf("%d", &status);
    if (status >= 0 && status <= 3) {
        return (StatusPedido)status;
    }
    printf("Status inválido! Considerando como PENDENTE.\n");
    return PENDENTE;
}

int main() {
    Pedido* pilha_pedidos = criar_pilha();
    int numero, quantidade;
    char nome_cliente[100], descricao_prato[100];
    StatusPedido status;
    int opcao;

    while (1) {
        printf("Menu:\n");
        printf("1. Inserir novo pedido\n");
        printf("2. Atualizar status do pedido\n");
        printf("3. Deletar pedido\n");
        printf("4. Exibir pedido\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o número do pedido: ");
                scanf("%d", &numero);
                printf("Digite o nome do cliente: ");
                getchar();  // Para consumir o caractere de nova linha remanescente
                fgets(nome_cliente, sizeof(nome_cliente), stdin);
                nome_cliente[strcspn(nome_cliente, "\n")] = '\0';  // Remove a nova linha do final
                printf("Digite a descrição do prato: ");
                fgets(descricao_prato, sizeof(descricao_prato), stdin);
                descricao_prato[strcspn(descricao_prato, "\n")] = '\0';  // Remove a nova linha do final
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);
                status = ler_status();
                empilhar_pedido(&pilha_pedidos, numero, nome_cliente, descricao_prato, quantidade, status);
                break;

            case 2:
                printf("Digite o número do pedido para atualizar o status: ");
                scanf("%d", &numero);
                status = ler_status();
                if (atualizar_status(pilha_pedidos, numero, status)) {
                    printf("Status do pedido %d atualizado com sucesso!\n", numero);
                } else {
                    printf("Pedido não encontrado!\n");
                }
                break;

            case 3:
                printf("Digite o número do pedido para deletar: ");
                scanf("%d", &numero);
                if (desempilhar_pedido(&pilha_pedidos, numero)) {
                    printf("Pedido %d deletado com sucesso!\n", numero);
                } else {
                    printf("Pedido não encontrado!\n");
                }
                break;

            case 4:
                printf("Digite o número do pedido para exibir: ");
                scanf("%d", &numero);
                Pedido* pedido = obter_pedido(pilha_pedidos, numero);
                if (pedido != NULL) {
                    printf("Pedido %d: %s - %s - %d - Status: %d\n", pedido->numero_pedido, pedido->nome_cliente, pedido->descricao_prato, pedido->quantidade, pedido->status);
                } else {
                    printf("Pedido não encontrado!\n");
                }
                break;

            case 5:
                liberar_pilha(pilha_pedidos);
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
}
