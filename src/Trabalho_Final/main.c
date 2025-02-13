#include <stdio.h>
#include <stdlib.h>
#include "campominado.h"


int main() {
    Tabuleiro tabuleiro;

    int largura, altura;
    int num_bombas = 0;
    int num_min_bombas = 7;
    int num_max_bombas = 0;
    
    
    printf("Por favor, insira a largura desejada: (Min = 5, Max = 40)\n");
    scanf("%d", &largura);

    while (largura > 40) {
        printf("Por favor, insira a largura desejada, agora respeitando os limites (Min = 5, Max = 40)\n");
    scanf("%d", &largura);
    }

    printf("Por favor, insira a altura desejada: (Min = 5, Max = 26)\n");
    scanf("%d", &altura);

    while (altura > 26) {
        printf("Por favor, insira a altura desejada, agora respeitando os limites (Min = 5, Max = 26)\n");
    scanf("%d", &altura);
    }

    num_max_bombas = ((largura+1)*(altura+1))/5;

    printf("Digite a quantidade desejada de bombas (Min = %d, Max = %d)\n", num_min_bombas, num_max_bombas);
    scanf("%d", &num_bombas);

    while (num_bombas < num_min_bombas || num_bombas > num_max_bombas) {
        printf("Digite a quantidade desejada de bombas, respeitando os limites (Min = %d, Max = %d)\n", num_min_bombas, num_max_bombas);
        scanf("%d", &num_bombas);
    }

    Inicializando_Tabuleiro(&tabuleiro, largura, altura);
    printf("Tabuleiro criado com sucesso!\n");
    Distribuir_Bombas(&tabuleiro, num_bombas);

    
    printf("Celula (0,0): x=%d, y=%d\n", tabuleiro.grid[0][0].x, tabuleiro.grid[0][0].y);
    printf("Celula (19,19): x=%d, y=%d\n", tabuleiro.grid[largura-1][altura-1].x, tabuleiro.grid[largura-1][altura-1].y);

    // Libera memória
    Liberar_Tabuleiro(&tabuleiro);
    return EXIT_SUCCESS;
}
