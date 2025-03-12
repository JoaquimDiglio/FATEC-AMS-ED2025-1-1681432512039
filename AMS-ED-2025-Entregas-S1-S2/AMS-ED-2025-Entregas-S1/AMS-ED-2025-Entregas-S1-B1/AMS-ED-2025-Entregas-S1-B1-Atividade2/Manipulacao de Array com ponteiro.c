#include <stdio.h>
#include <string.h> 

#define MAX_CANDIDATOS 50
#define NUM_NOTAS_PE 4
#define NUM_NOTAS_AC 5
#define NUM_NOTAS_PP 10
#define NUM_NOTAS_EB 3

//calcular a soma das notas, excluindo a maior e a menor
int soma_excluindo_extremos(int* notas, int tamanho) {
    int maior = notas[0], menor = notas[0];
    int soma = 0;

    //maior e a menor nota
    for (int i = 0; i < tamanho; i++) {
        if (notas[i] > maior) maior = notas[i];
        if (notas[i] < menor) menor = notas[i];
        soma += notas[i];
    }

    //soma sem a maior e a menor nota
    return soma - maior - menor;
}

// Função para calcular a nota final
float calcular_nota_final(int* notas_PE, int* notas_AC, int* notas_PP, int* notas_EB) {
    // soma
    float PE_soma = soma_excluindo_extremos(notas_PE, NUM_NOTAS_PE);
    float AC_soma = soma_excluindo_extremos(notas_AC, NUM_NOTAS_AC);
    float PP_soma = soma_excluindo_extremos(notas_PP, NUM_NOTAS_PP);
    float EB_soma = soma_excluindo_extremos(notas_EB, NUM_NOTAS_EB);

    // Calcula a Nota Final
    return (PE_soma * 0.3) + (AC_soma * 0.1) + (PP_soma * 0.4) + (EB_soma * 0.2);
}

// Função para classificar 
void classificar_candidatos(char nome[MAX_CANDIDATOS][100], float nota_final[MAX_CANDIDATOS], int candidatos) {
    for (int i = 0; i < candidatos - 1; i++) {
        for (int j = i + 1; j < candidatos; j++) {
            if (nota_final[i] < nota_final[j]) {
                // Troca as notas
                float temp_nota = nota_final[i];
                nota_final[i] = nota_final[j];
                nota_final[j] = temp_nota;
                
                
                char temp_nome[100];
                strcpy(temp_nome, nome[i]);
                strcpy(nome[i], nome[j]);
                strcpy(nome[j], temp_nome);
            }
        }
    }
}

int main() {
    int candidatos = 0;

    // Arrays
    int notas_PE[MAX_CANDIDATOS][NUM_NOTAS_PE];
    int notas_AC[MAX_CANDIDATOS][NUM_NOTAS_AC];
    int notas_PP[MAX_CANDIDATOS][NUM_NOTAS_PP];
    int notas_EB[MAX_CANDIDATOS][NUM_NOTAS_EB];
    float nota_final[MAX_CANDIDATOS];
    char nome[MAX_CANDIDATOS][100];

    // dados dos alunos
    while (candidatos < MAX_CANDIDATOS) {
        printf("Digite o nome do candidato %d: ", candidatos + 1);
        fgets(nome[candidatos], sizeof(nome[candidatos]), stdin);
        nome[candidatos][strcspn(nome[candidatos], "\n")] = '\0';  

        if (strcmp(nome[candidatos], "fim") == 0) {
            break;
        }

        // notas para cada prova
        printf("Digite as notas da Prova Escrita (PE) (4 notas):\n");
        for (int i = 0; i < NUM_NOTAS_PE; i++) {
            printf("Nota %d: ", i + 1);
            scanf("%d", &notas_PE[candidatos][i]);
        }

        printf("Digite as notas da Análise Curricular (AC) (5 notas):\n");
        for (int i = 0; i < NUM_NOTAS_AC; i++) {
            printf("Nota %d: ", i + 1);
            scanf("%d", &notas_AC[candidatos][i]);
        }

        printf("Digite as notas da Prova Prática (PP) (10 notas):\n");
        for (int i = 0; i < NUM_NOTAS_PP; i++) {
            printf("Nota %d: ", i + 1);
            scanf("%d", &notas_PP[candidatos][i]);
        }

        printf("Digite as notas da Entrevista em Banca Avaliadora (EB) (3 notas):\n");
        for (int i = 0; i < NUM_NOTAS_EB; i++) {
            printf("Nota %d: ", i + 1);
            scanf("%d", &notas_EB[candidatos][i]);
        }

        // Calcula a nf do candidato
        nota_final[candidatos] = calcular_nota_final(
            notas_PE[candidatos],
            notas_AC[candidatos],
            notas_PP[candidatos],
            notas_EB[candidatos]
        );

        candidatos++;

        // Pergunta se qr continuar adicionando gente
        char resposta;
        printf("Deseja adicionar outro candidato? (s para sim / qualquer outra tecla para não): ");
        getchar();
        scanf("%c", &resposta);

        if (resposta != 's' && resposta != 'S') {
            break;  // Sai do loop se a resposta não for 's'
        }
    }

    classificar_candidatos(nome, nota_final, candidatos);

    //5 melhores alunos
    printf("\nRanking dos 5 melhores candidatos:\n");
    for (int i = 0; i < (candidatos < 5 ? candidatos : 5); i++) {
        printf("%d. %s - Nota Final: %.2f\n", i + 1, nome[i], nota_final[i]);
    }

    return 0;
}
