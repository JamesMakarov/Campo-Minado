#ifndef INTERFACE_H
#define INTERFACE_H
#include "..\back\campominado.h"

void MenuPrincipal();
void Exibir_Tabuleiro(Tabuleiro *tabuleiro, int largura, int altura);  // Alterado para receber int
void opcoes(Tabuleiro *tabuleiro, short int opcao);
void Pegar_Jogada(int *x, int *y, char *acao);
void Mostrar_Resultado(bool venceu);
bool Regras();

#endif
