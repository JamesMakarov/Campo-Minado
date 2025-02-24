#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h> 
#include <ctype.h> 
#include <conio.h>
#include <time.h>
#include "interface.h"
#include "../back/campominado.h"

void MenuPrincipal(Tabuleiro *tabuleiro) {
    short int opcao = 0;
    system("clear"); /*Limpa a tela no Linux(para quando o Miguel GOAT for corrigir )*/
    system("cls");  /*Limpa a tela no Windows*/
    printf("\033[0;33m"); // cor amarela no terminal
    printf("\n\n");
    printf("   ==================================\n");
    printf("             CAMPO MINADO            \n");
    printf("   ==================================\n");
    printf("\n");
    
    printf("           1 - Iniciar Jogo         \n");
    
    printf("           2 - Regras               \n");
   
    printf("           3 - Sair                 \n");
    printf("\n");
    printf("   Escolha uma opcao: ");
    printf("\033[0m"); // retorna para a cor original do terminal (branco)
    scanf("%hd", &opcao);
    opcoes(tabuleiro, opcao);
    
}

void Start(Tabuleiro *tabuleiro, int *altura, int *largura, int *num_bombas) {
    Dados_iniciais(altura, largura, num_bombas);
    Inicializando_Tabuleiro(tabuleiro, *altura, *largura, *num_bombas);
    Bombas_Perto_Celula(tabuleiro);

    // Inicia o temporizador
    time_t start_time = time(NULL);

    int x, y;
    char acao;
    bool jogo_ativo = true;

    while (jogo_ativo) {
        Exibir_Tabuleiro(tabuleiro, *largura, *altura);
        Pegar_Jogada(tabuleiro, &x, &y, &acao);

        if (acao == 'A') {
            if (x < 0 || x >= tabuleiro->largura || y < 0 || y >= tabuleiro->altura) {
                printf("Coordenada invalida! Tente novamente.\n");
                continue;
            }

            Revelar_celulas(tabuleiro, y, x);
            if (Jogador_perdeu(tabuleiro, y, x)) {
                printf("Você acertou uma mina! Fim de jogo.\n");
                Mostrar_tabuleiro(tabuleiro);
                Exibir_Tabuleiro(tabuleiro, *largura, *altura);
                jogo_ativo = false;

                // Calcula o tempo decorrido
                time_t end_time = time(NULL);
                double elapsed_time = difftime(end_time, start_time);

                // Chama o menu pós-jogo e passa o tempo decorrido
                MenuPosJogo(tabuleiro, altura, largura, num_bombas, elapsed_time);
            } else if (Jogador_venceu(tabuleiro, *num_bombas)) {
                printf("Parabens! Voce venceu!\n");
                Mostrar_tabuleiro(tabuleiro);
                Exibir_Tabuleiro(tabuleiro, *largura, *altura);
                jogo_ativo = false;

                // Calcula o tempo decorrido
                time_t end_time = time(NULL);
                double elapsed_time = difftime(end_time, start_time);

                // Chama o menu pós-jogo e passa o tempo decorrido
                MenuPosJogo(tabuleiro, altura, largura, num_bombas, elapsed_time);
            }
        } else if (acao == '#') {
            if (x < 0 || x >= tabuleiro->largura || y < 0 || y >= tabuleiro->altura) {
                printf("Coordenada invalida! Tente novamente.\n");
                continue;
            }
            bandeira(tabuleiro, x, y);  // Marcar bandeira
        } else if (acao == '!') {
            if (x < 0 || x >= tabuleiro->largura || y < 0 || y >= tabuleiro->altura) {
                printf("Coordenada invalida! Tente novamente.\n");
                continue;
            }
            bandeira(tabuleiro, x, y);  // Desmarcar bandeira
        } else {
            printf("Acao invalida! Tente novamente.\n");
        }
    }
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
    int bandeiras_marcadas = ContarBandeiras(tabuleiro);
    /*Para exibir números das colunas (alinhados verticalmente)*/
    printf("\033[0;33m");
    printf("Bandeiras marcadas: %d\n", bandeiras_marcadas);
    printf("     ");  /*Espaço para alinhar com as letras das linhas*/
    for (int i = 0; i < tabuleiro->altura; i++) { 
        int var = (i + 1)/10;
        if (var != 0) printf(" %d   ", var);
        
        else printf("     ");
    }
    printf("\n");
    printf("     ");
    for (int j = 0; j < tabuleiro->altura; j++) {
        printf("%2d   ", (j + 1) %10);  /*Números das colunas com 2 digitos*/
    }
    printf("\n");
    printf("\033[0m");

    // Exibe o tabuleiro com letras das linhas
    for (int i = 0; i < tabuleiro->largura; i++) {
        printf("\n");
        
        printf("\033[0;33m");
        printf("%2c  ", 'A' + i);  // Letras das linhas (A, B, C, ...)
        printf("\033[0m");
        for (int j = 0; j < tabuleiro->altura; j++) {
            Celula *celula = &tabuleiro->grid[j][i];

            if (celula->aberto) {
                if (celula->bomba) {
                    printf(" \033[43m\033[31m @ \033[0m ");  // Exibe bomba
                } else if (celula->bombas > 0) {
                    
                    printf(" \033[47m\033[36m %d ", celula->bombas);  // Exibe número de bombas próximas
                    printf("\033[0m ");
                } else {
                    printf("     ");  // Exibe célula vazia (sem bombas próximas)
                }
            } else if (celula->bandeira) {
                printf("  !  ");  // Exibe bandeira
            } else {
                printf(" \033[47m\033[32m   \033[0m ");  // Exibe célula fechada
            }
        }
        printf("\n");  // Quebra de linha após cada linha do tabuleiro
    }
    printf("\n");
}

bool Regras() {
    char pronto;
    system("clear"); 
    system("cls");  
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

void Pegar_Jogada(Tabuleiro *tabuleiro, int *x, int *y, char *acao) {
    char entrada[10];
    bool entrada_valida = false;

    while (!entrada_valida) {
        printf("# - Marcar bandeira.\n! - Desmarca bandeira.\n");
        printf("Digite sua jogada (ex: A15, #B7, !C3): ");
        scanf("%s", entrada);

        /* Verifica se a entrada tem pelo menos 2 caracteres */
        if (strlen(entrada) < 2) {
            printf("Entrada invalida! Tente novamente.\n");
            continue;
        }

        char *ptr;
        if (entrada[0] == '#' || entrada[0] == '!') {
            *acao = entrada[0];  // Ação: marcar ou desmarcar bandeira
            *x = toupper(entrada[1]) - 'A'; // Linha (A=0, B=1, ...)
            *y = strtol(&entrada[2], &ptr, 10) - 1; // Coluna
        } else {
            *acao = 'A';  // Ação: abrir célula
            *x = toupper(entrada[0]) - 'A';
            *y = strtol(&entrada[1], &ptr, 10) - 1;
        }

        /* Verifica se a conversão falhou (ptr == &entrada[1] indica erro) */
        if (ptr == &entrada[1] || *y < 0) {
            printf("Numero inválido! Tente novamente.\n");
            continue;
        }

        /* Verifica se as coordenadas estão dentro dos limites do tabuleiro */
        if (*x >= 0 && *x < tabuleiro->largura && *y >= 0 && *y < tabuleiro->altura) {
            entrada_valida = true;
        } else {
            printf("Coordenada invalida! Tente novamente.\n");
        }
    }
}

void Reiniciar_Jogo(Tabuleiro *tabuleiro, int *altura, int *largura, int *num_bombas) {
    // Libera a memória do tabuleiro atual
    Liberar_Tabuleiro(tabuleiro);

    // Recoleta as dimensões e o número de bombas (opcional, se quiser redefinir)
    // Dados_iniciais(altura, largura, num_bombas);

    // Inicializa um novo tabuleiro com as mesmas configurações
    Inicializando_Tabuleiro(tabuleiro, *largura, *altura, *num_bombas);
    Bombas_Perto_Celula(tabuleiro);
}


void MenuPosJogo(Tabuleiro *tabuleiro, int *altura, int *largura, int *num_bombas, double tempo_decorrido) {
    short int opcao;

    printf("\033[0;33m"); // cor amarela no terminal
    printf("\n\n");
    printf("   ==================================\n");
    printf("            DESEJA CONTINUAR?            \n");
    printf("   ==================================\n");
    printf("\n");
    
    printf("           1 - Jogar novamente         \n");
    
    printf("           2 - Voltar ao menu principal               \n");
   
    printf("           3 - Sair                 \n");
    printf("\n");
    printf("   Tempo decorrido: %.2f segundos\n", tempo_decorrido);
    printf("   Escolha uma opcao: ");
    printf("\033[0m"); // retorna para a cor original do terminal (branco)
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            // Reinicia o jogo com as mesmas configurações
            Reiniciar_Jogo(tabuleiro, altura, largura, num_bombas);
            Start(tabuleiro, altura, largura, num_bombas);
            break;
        case 2:
            // Volta ao menu principal
            MenuPrincipal(tabuleiro);
            break;
        case 3:
            // Sai do jogo
            printf("Saindo... Obrigado por jogar!\n");
            exit(0);
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
            MenuPosJogo(tabuleiro, altura, largura, num_bombas, tempo_decorrido);  // Chama novamente em caso de opção inválida
            break;
    }
}