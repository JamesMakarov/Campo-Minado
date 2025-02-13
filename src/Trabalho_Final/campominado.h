#ifndef CAMPOMINADO_H
#define CAMPOMINADO_H

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


#endif