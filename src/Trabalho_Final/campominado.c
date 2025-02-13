#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "campominado.h"

Celula* CriarNova(Info info) {
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    if (!nova) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    nova->dados = info;
    nova->cima = NULL;
    nova->baixo = NULL;
    nova->esq = NULL;
    nova->dir = NULL;
    nova->dbdir = NULL;
    nova->dbesq = NULL;
    nova->dcdir = NULL;
    nova->dcesq = NULL;

    return nova;
}

