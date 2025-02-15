#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "back/campominado.h"
#include "interface/interface.h"


int main() {
    Tabuleiro tabuleiro;

    MenuPrincipal(&tabuleiro); // 1

    Liberar_Tabuleiro(&tabuleiro);
    return EXIT_SUCCESS;
}
