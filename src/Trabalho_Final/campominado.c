#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "campominado.h"

// Cria uma nova célula com valores padrões
Celula* CriarNova(int x, int y) {
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    if (!nova) {
        printf("Erro ao alocar memória para célula.\n");
        exit(1);
    }

    // Valores padrão
    nova->aberto = false;
    nova->bandeira = false;
    nova->bomba = false;
    nova->bombas = 0;
    nova->x = x;
    nova->y = y;

    // Ponteiros nulos
    nova->cima = nova->baixo = nova->esq = nova->dir = NULL;
    nova->dcesq = nova->dcdir = nova->dbesq = nova->dbdir = NULL;

    return nova;
}

// Inicializa o tabuleiro com uma matriz de células
void Inicializando_Tabuleiro(Tabuleiro *tabuleiro, int largura, int altura) {
    tabuleiro->largura = largura;
    tabuleiro->altura = altura;

    // Alocando memória para o grid (matriz de células)
    tabuleiro->grid = (Celula**)malloc(altura * sizeof(Celula*));
    if (!tabuleiro->grid) {
        printf("Erro ao alocar memória para o tabuleiro.\n");
        exit(1);
    }

    for (int i = 0; i < altura; i++) {
        tabuleiro->grid[i] = (Celula*)malloc(largura * sizeof(Celula));
        if (!tabuleiro->grid[i]) {
            printf("Erro ao alocar memória para linha do tabuleiro.\n");
            exit(1);
        }

        // Criando células
        for (int j = 0; j < largura; j++) {
            tabuleiro->grid[i][j] = *CriarNova(j, i);
        }
    }

    // Conecta as células vizinhas
    Conectar_Vizinhos(tabuleiro);
}

// Conecta as células vizinhas usando os ponteiros
void Conectar_Vizinhos(Tabuleiro *tabuleiro) {
    for (int i = 0; i < tabuleiro->altura; i++) {
        for (int j = 0; j < tabuleiro->largura; j++) {
            Celula *atual = &tabuleiro->grid[i][j];

            // Cima e baixo
            if (i > 0) atual->cima = &tabuleiro->grid[i-1][j];
            if (i < tabuleiro->altura - 1) atual->baixo = &tabuleiro->grid[i+1][j];

            // Esquerda e direita
            if (j > 0) atual->esq = &tabuleiro->grid[i][j-1];
            if (j < tabuleiro->largura - 1) atual->dir = &tabuleiro->grid[i][j+1];

            // Diagonais
            if (i > 0 && j > 0) atual->dcesq = &tabuleiro->grid[i-1][j-1];
            if (i > 0 && j < tabuleiro->largura - 1) atual->dcdir = &tabuleiro->grid[i-1][j+1];
            if (i < tabuleiro->altura - 1 && j > 0) atual->dbesq = &tabuleiro->grid[i+1][j-1];
            if (i < tabuleiro->altura - 1 && j < tabuleiro->largura - 1) atual->dbdir = &tabuleiro->grid[i+1][j+1];
        }
    }
}

// Libera memória do tabuleiro
void Liberar_Tabuleiro(Tabuleiro *tabuleiro) {
    for (int i = 0; i < tabuleiro->altura; i++) {
        free(tabuleiro->grid[i]);
    }
    free(tabuleiro->grid);
}
