#ifndef INTERFACE_H
#define INTERFACE_H
#include "..\back\campominado.h"
#include <time.h>

void MenuPrincipal();
void Exibir_Tabuleiro(Tabuleiro *tabuleiro, int largura, int altura);  // Alterado para receber int
void opcoes(Tabuleiro *tabuleiro, short int opcao);
void Pegar_Jogada(Tabuleiro *tabuleiro, int *x, int *y, char *acao);
void Mostrar_Resultado(bool venceu);
void Start(Tabuleiro *tabuleiro, int *altura, int *largura, int *num_bombas);
bool Regras();
void Reiniciar_Jogo(Tabuleiro *tabuleiro, int *altura, int *largura, int *num_bombas);
void MenuPosJogo(Tabuleiro *tabuleiro, int *altura, int *largura, int *num_bombas, double tempo_decorrido);
void IniciarTemporizador(time_t *inicio);
int CalcularTempoDecorrido(time_t inicio);

#endif
