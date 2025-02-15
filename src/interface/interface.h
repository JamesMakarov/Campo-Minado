#ifndef INTERFACE_H
#define INTERFAFE_H
#include "..\back\campominado.h"

void MenuPrincipal();
void Exibir_Tabuleiro(Tabuleiro *tabuleiro);
void Pegar_Jogada(int *x, int *y, char *acao);
void Mostrar_Resultado(bool venceu);
void Regras();

#endif