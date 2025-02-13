#include <stdio.h>
#include "campominado.h"


int main() {
    Tabuleiro tabuleiro;
    
    // Cria um tabuleiro de 10x10
    Inicializando_Tabuleiro(&tabuleiro, 20, 20);
    printf("Tabuleiro criado com sucesso!\n");

    // Exemplo: Mostrando coordenadas de algumas células
    printf("Celula (0,0): x=%d, y=%d\n", tabuleiro.grid[0][0].x, tabuleiro.grid[0][0].y);
    printf("Celula (19,19): x=%d, y=%d\n", tabuleiro.grid[19][19].x, tabuleiro.grid[19][19].y);

    // Libera memória
    Liberar_Tabuleiro(&tabuleiro);
    return 0;
}
