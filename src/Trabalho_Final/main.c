#include <stdio.h>
#include "campominado.h"


int main() {
    Tabuleiro tabuleiro;
    
    // Cria um tabuleiro de 10x10
    Inicializando_Tabuleiro(&tabuleiro, 10, 10);
    printf("Tabuleiro criado com sucesso!\n");

    // Exemplo: Mostrando coordenadas de algumas células
    printf("Celula (0,0): x=%d, y=%d\n", tabuleiro.grid[0][0].x, tabuleiro.grid[0][0].y);
    printf("Celula (9,9): x=%d, y=%d\n", tabuleiro.grid[9][9].x, tabuleiro.grid[9][9].y);

    // Libera memória
    Liberar_Tabuleiro(&tabuleiro);
    return 0;
}
