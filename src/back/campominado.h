#ifndef CAMPOMINADO_H
#define CAMPOMINADO_H
#include <stdbool.h>

typedef struct Celula {

    bool aberto, bandeira, bomba, dica_aplicada;
    short int bombas, cobertos; 
    int x ,y;
    struct Celula *cima, *baixo, *esq, *dir, *dcesq, *dcdir, *dbesq, *dbdir;

} Celula;

typedef struct Tabuleiro {

    int largura, altura;
    Celula **grid;

} Tabuleiro;

Celula* CriarNova(int x, int y);
void Inicializando_Tabuleiro(Tabuleiro *tabuleiro, int altura, int largura, int num_bombas);
void Conectar_Vizinhos(Tabuleiro *tabuleiro);
void Liberar_Tabuleiro(Tabuleiro *tabuleiro);
void Distribuir_Bombas(Tabuleiro *tabuleiro, int num_bombas);
void Bombas_Perto_Celula(Tabuleiro *tabuleiro);
void Revelar_celulas(Tabuleiro *tabuleiro, int x, int y);
void Dica(Tabuleiro *tabuleiro);
void bandeira(Tabuleiro *tabuleiro, int x, int y);
void colocarBandeira(Tabuleiro *tabuleiro, int x, int y);
int cobertos_perto(Tabuleiro *tabuleiro , int x, int y);
int bandeiras_perto(Tabuleiro *tabuleiro , int x, int y);
bool Jogador_venceu(Tabuleiro *tabuleiro, int bombas_totais);
void Mostrar_tabuleiro (Tabuleiro *tabuleiro);
void Dados_iniciais (int *altura, int *largura, int *num_bombas);
bool Jogador_perdeu(Tabuleiro *tabuleiro, int x, int y);
int ContarBandeiras(Tabuleiro *tabuleiro);

#endif