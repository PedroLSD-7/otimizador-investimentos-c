//por questoes de analize de conhecimento sobre a estrutura do codigo, ele foi feito sem comentarios
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_COD 4
#define TAM_DESC 20
#define MAX_ACOES 100
#define MAX_LINHA 100
#define LINHAS 3
#define COLUNAS 3

typedef struct {
    char cod[TAM_COD];
    char nome[TAM_DESC];
    float preco;
    float retorno;
    float lucro;
    float razao;
} Acao;

void preencher_matriz(int matriz[LINHAS][COLUNAS], int valor) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            matriz[i][j] = valor++;
        }
    }
}

int soma_matriz_recursiva(int matriz[LINHAS][COLUNAS], int i, int j) {
    if (i >= LINHAS) return 0;
    if (j >= COLUNAS) return soma_matriz_recursiva(matriz, i + 1, 0);
    return matriz[i][j] + soma_matriz_recursiva(matriz, i, j + 1);
}

int ler_arquivo(const char* nome_arquivo, Acao* lista) {
    FILE* arq = fopen(nome_arquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return -1;
    }

    int qtd = 0;
    char linha[MAX_LINHA];

    while (fgets(linha, sizeof(linha), arq) && qtd < MAX_ACOES) {
        if (sscanf(linha, "%3s %f %f %19[^\n]", 
                lista[qtd].cod, 
                &lista[qtd].preco, 
                &lista[qtd].retorno, 
                lista[qtd].nome) == 4) {
            lista[qtd].lucro = lista[qtd].preco * lista[qtd].retorno / 100.0;
            lista[qtd].razao = lista[qtd].lucro / lista[qtd].preco;
            qtd++;
        }
    }

    fclose(arq);
    return qtd;
}

void ordenar(Acao* lista, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (lista[j].razao > lista[i].razao) {
                Acao temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }
}

void melhorCombinacao(Acao* acoes, int n, float dinheiro) {
    ordenar(acoes, n);

    float total = 0, lucroTotal = 0, somaRetornos = 0;

    printf("\nMELHOR COMBINACAO DE INVESTIMENTO\n");
    printf("COD  PRECO     RETORNO    NOME\n");

    for (int i = 0; i < n && dinheiro > 0; i++) {
        if (acoes[i].preco <= dinheiro) {
            printf("%-3s  %-8.2f  %-6.2f%%    %s\n", 
                acoes[i].cod, 
                acoes[i].preco, 
                acoes[i].retorno, 
                acoes[i].nome);
            dinheiro -= acoes[i].preco;
            total += acoes[i].preco;
            lucroTotal += acoes[i].lucro;
            somaRetornos += acoes[i].retorno;
        }
    }

    printf("\nTOTAL INVESTIDO: R$ %.2f\n", total);
    printf("LUCRO ESPERADO: R$ %.2f\n", lucroTotal);
    printf("SOMA DAS PORCENTAGENS DE RETORNO: %.2f%%\n", somaRetornos);
}

const char* selecionar_arquivo(float dinheiro) {
    if (dinheiro < 250) {
        return NULL;
    } else if (dinheiro <= 1000) {
        return "iniciante.txt";
    } else if (dinheiro <= 38000) {
        return "moderado.txt";
    } else if (dinheiro <= 65000) {
        return "dificil.txt";
    } else {
        return "expert.txt";
    }
}

int main() {
    int matriz[LINHAS][COLUNAS];
    preencher_matriz(matriz, 1);
    int soma_oculta = soma_matriz_recursiva(matriz, 0, 0);
    (void)soma_oculta;

    float dinheiro;
    Acao lista[MAX_ACOES];

    printf("Qual o valor de investimento? ");
    if (scanf("%f", &dinheiro) != 1) {
        printf("Valor inválido!\n");
        return 1;
    }

    const char* nome_arquivo = selecionar_arquivo(dinheiro);
    if (nome_arquivo == NULL) {
        printf("Dinheiro insuficiente para investir\n");
        return 0;
    }

    int qtd = ler_arquivo(nome_arquivo, lista);
    if (qtd <= 0) {
        printf("Nao foi possivel ler as acoes do arquivo %s\n", nome_arquivo);
        printf("Certifique-se que o arquivo está na mesma pasta do programa.\n");
        return 1;
    }

    printf("\nACOES DISPONIVEIS\n");
    printf("COD  PRECO     RETORNO    NOME\n");
    for (int i = 0; i < qtd; i++) {
        printf("%-3s  %-8.2f  %-6.2f%%    %s\n", 
            lista[i].cod, 
            lista[i].preco, 
            lista[i].retorno, 
            lista[i].nome);
    }

    melhorCombinacao(lista, qtd, dinheiro);

    return 0;
}