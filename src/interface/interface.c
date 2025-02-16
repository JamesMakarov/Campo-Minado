#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "interface.h"
#include "../back/campominado.h"

void MenuPrincipal(Tabuleiro *tabuleiro) {
    short int opcao = 0;
    system("cls");
    printf("\033[0;33m"); // cor amarela no terminal
    printf("\n\n");
    printf("   ==================================\n");
    printf("             CAMPO MINADO            \n");
    printf("   ==================================\n");
    printf("\n");
    sleep(1);
    printf("           1 - Iniciar Jogo         \n");
    sleep(1);
    printf("           2 - Regras               \n");
    sleep(1);
    printf("           3 - Sair                 \n");
    printf("\n");
    printf("   Escolha uma opcao: ");
    printf("\033[0m"); // retorna para a cor original do terminal (branco)
    scanf("%hd", &opcao);
    opcoes(tabuleiro, opcao);
    
}

void Start(Tabuleiro *tabuleiro, int *altura, int *largura, int *num_bombas) {
    Dados_iniciais(altura, largura, num_bombas);
    Inicializando_Tabuleiro(tabuleiro, *largura, *altura);
    Distribuir_Bombas(tabuleiro, *num_bombas);
    Exibir_Tabuleiro(tabuleiro, *largura, *altura);
}

void opcoes(Tabuleiro *tabuleiro, short int opcao) {
    switch (opcao) {
        case 1:
            printf("Iniciando o jogo...\n");
            int altura, largura, num_bombas;
            Start(tabuleiro, &altura, &largura, &num_bombas);
            break;
        case 2:
            printf("Exibindo as regras...\n");
            if (Regras()) Start(tabuleiro, &altura, &largura, &num_bombas); // inicia jogo
            else MenuPrincipal(tabuleiro);
            break;
        case 3:
            printf("Saindo... Obrigado por jogar!\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
}

void Exibir_Tabuleiro(Tabuleiro *tabuleiro, int largura, int altura) {
    printf("\nTabuleiro:\n");

    for (int i = 0; i < tabuleiro->largura; i++) {
        for (int j = 0; j < tabuleiro->altura; j++) {
            Celula *celula = &tabuleiro->grid[i][j];

            if (celula->aberto) {
                if (celula->bomba) {
                    printf(" * ");  // Exibe bomba
                } else if (celula->bombas > 0) {
                    printf(" %d ", celula->bombas);  // Exibe número de bombas próximas
                } else {
                    printf("   ");  // Exibe célula vazia (sem bombas próximas)
                }
            } else if (celula->bandeira) {
                printf(" F ");  // Exibe bandeira
            } else {
                printf(" # ");  // Exibe célula fechada
            }
        }
        printf("\n");  // Quebra de linha após cada linha do tabuleiro
    }
    printf("\n");
}

bool Regras() {
    char pronto;
    system("clear"); /*Limpa a tela no Linux(para quando o Miguel GOAT for corrigir )*/
    system("cls");  /*Limpa a tela no Windows*/
    printf("\033[0;33m"); /*Aqui é pra cor continuar igual ao do menu.*/
    printf("\n\n");
    printf("   ==================================\n");
    printf("             REGRAS DO JOGO          \n");
    printf("   ==================================\n");
    printf("\n");
    printf("1 - Objetivo: Abrir todas as celulas seguras do tabuleiro sem escolher a coordenada de uma mina.\n\n");
    printf("2 - Tabuleiro: Consiste em uma grade com celulas ocultas, algumas contendo minas e outras vazias ou com numeros.\n\n");
    printf("3 - Numeros: Ao escolher a coordenada de uma celula vazia, um numero pode aparecer indicando quantas minas estao nas celulas adjacentes.\n\n");
    printf("4 - Marcacao de Minas: O jogador pode marcar celulas suspeitas com bandeiras para indicar possiveis minas.\n\n");
    printf("5 - Explosao: Se o jogador escolher a coordenada de uma celula com mina, o jogo termina imediatamente com derrota.\n\n");
    printf("6 - Abertura Automatica: Se uma celula sem mina e sem numeros for aberta, as celulas vizinhas tambem sao reveladas automaticamente ate encontrar numeros.\n\n");
    printf("7 - Vitoria: O jogo eh vencido quando todas as celulas seguras forem reveladas e todas as minas estiverem corretamente marcadas.\n\n");
    printf("\033[0m"); /*Retorna para a cor do terminal*/
    printf("Essas sao as regras, pronto? Digite qualquer coisa no terminal e aperte Enter.\n");
    getchar();
    scanf("%c", &pronto);
    if (pronto != '\n') {
        return true; 
    }
    return false;  
}
