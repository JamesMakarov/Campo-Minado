#ifndef CAMPOMINADO_H
#define CAMPOMINADO_H
#include <stdbool.h>

typedef struct Celula {

    bool aberto, bandeira, bomba;
    short int bombas, cobertos; 
    int x ,y;
    struct Celula *cima, *baixo, *esq, *dir, *dcesq, *dcdir, *dbesq, *dbdir;

} Celula;

typedef struct Tabuleiro {

    int largura, altura;
    Celula **grid;

} Tabuleiro;

Celula* CriarNova(int x, int y);
void Inicializando_Tabuleiro(Tabuleiro *tabuleiro, int largura, int altura);
void Conectar_Vizinhos(Tabuleiro *tabuleiro);
void Liberar_Tabuleiro(Tabuleiro *tabuleiro);
void Distribuir_Bombas(Tabuleiro *tabuleiro, int num_bombas);
void Bombas_Perto_Celula(Tabuleiro *tabuleiro, int bombas);
void Revelar_celulas(Tabuleiro *tabuleiro, int x, int y);


#endif