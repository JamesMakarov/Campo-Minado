#include <stdio.h>
#include <stdlib.h>
#include "back/campominado.h"
#include "interface/interface.h"


int main() {
    Tabuleiro tabuleiro;

    int largura, altura;
    int num_bombas = 0;

    Dados_iniciais (&largura, &altura, &num_bombas);
    Inicializando_Tabuleiro(&tabuleiro, largura, altura);
    printf("Tabuleiro criado com sucesso!\n");
    Distribuir_Bombas(&tabuleiro, num_bombas);

    // essa parte tá só testando se tá dando certo
    printf("Celula (0,0): x=%d, y=%d\n", tabuleiro.grid[0][0].x, tabuleiro.grid[0][0].y);
    printf("Celula (19,19): x=%d, y=%d\n", tabuleiro.grid[altura-1][largura-1].x, tabuleiro.grid[altura-1][largura-1].y);

    // Libera memória
    Liberar_Tabuleiro(&tabuleiro);
    return EXIT_SUCCESS;
}
