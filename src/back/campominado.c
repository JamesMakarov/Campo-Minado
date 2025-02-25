#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include "campominado.h"

void limpar_buffer() {
    // Limpa o buffer do stdin
    while(getchar() != '\n');
}

void Dados_iniciais (int *altura, int *largura, int *num_bombas) {
    limpar_buffer();
    // declaração de variáveis: as variáveis auxiliares serão utilziadas pra não ficar mudando o valor dentro de main todo tempo
    int aux1, aux2, aux3;
    printf("Por favor, insira a altura desejada: (Min = 5, Max = 26)\n");
    scanf("%d", &aux1);
    while (5 > aux1 || aux1 > 26) {
        printf("Por favor, insira a altura desejada, agora respeitando os limites (Min = 5, Max = 26)\n");
    scanf("%d", &aux1);
    }

    printf("Por favor, insira a largura desejada: (Min = 5, Max = 40)\n");
    scanf("%d", &aux2);

    while (5 > aux2 || aux2 > 40) {
        printf("Por favor, insira a largura desejada, agora respeitando os limites (Min = 5, Max = 40)\n");
    scanf("%d", &aux2);
    }

    int num_max_bombas = ((aux1+1)*(aux2+1))/5;

    int num_min_bombas = 7;

    printf("Digite a quantidade desejada de bombas (Min = %d, Max = %d)\n", num_min_bombas, num_max_bombas);
    scanf("%d", &aux3);

    while (aux3 < num_min_bombas || aux3 > num_max_bombas) {
        printf("Digite a quantidade desejada de bombas, respeitando os limites (Min = %d, Max = %d)\n", num_min_bombas, num_max_bombas);
        scanf("%d", &aux3);
    }
    *num_bombas = aux3;
    *altura = aux2; 
    *largura = aux1;
    printf("Número de bombas: %d\nAltura = %d\nLargura = %d\n", *num_bombas,*largura ,*altura );
}


// Cria uma nova célula com valores padrões
Celula* CriarNova(int x, int y) {
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    if (!nova) {
        printf("Erro ao alocar memória para célula.\n");
        exit(1);
    }
    nova->aberto = nova->bandeira = nova->bomba = nova->dica_aplicada = false;
    nova->bombas = 0;
    nova->x = x;
    nova->y = y;
    nova->cima = nova->baixo = nova->esq = nova->dir = NULL;
    nova->dcesq = nova->dcdir = nova->dbesq = nova->dbdir = NULL;

    return nova;
}
// Inicializa o tabuleiro com uma matriz de células
void Inicializando_Tabuleiro(Tabuleiro *tabuleiro, int altura, int largura, int num_bombas) {
    tabuleiro->altura = altura;
    tabuleiro->largura = largura;

    // Alocando memória para as linhas da matriz (o número de linhas será 'altura')
    tabuleiro->grid = (Celula**)malloc(altura * sizeof(Celula*));
    if (!tabuleiro->grid) {
        printf("Erro ao alocar memória para o tabuleiro.\n");
        exit(1);
    }

    for (int i = 0; i < altura; i++) {  // Aqui o loop vai até 'altura', já que 'altura' são as linhas
        tabuleiro->grid[i] = (Celula*)malloc(largura * sizeof(Celula));  // Cada linha vai ter 'largura' células
        if (!tabuleiro->grid[i]) {
            printf("Erro ao alocar memória para linha do tabuleiro.\n");
            exit(1);
        }

        // Inicializa as células com valores padrão
        for (int j = 0; j < largura; j++) {  // Agora o loop vai até 'largura', que são as colunas
            tabuleiro->grid[i][j] = *CriarNova(i, j);  // Mantendo a referência correta para cada célula
        }
    }

    // Conecta as células vizinhas
    Conectar_Vizinhos(tabuleiro);
    Distribuir_Bombas(tabuleiro, num_bombas);
}


// Conecta as células vizinhas corretamente
void Conectar_Vizinhos(Tabuleiro *tabuleiro) {
    for (int i = 0; i < tabuleiro->altura; i++) {
        for (int j = 0; j < tabuleiro->largura; j++) {
            Celula *atual = &tabuleiro->grid[i][j];

            // Cima e baixo
            if (i > 0) atual->cima = &tabuleiro->grid[i-1][j];
            if (i < tabuleiro->altura - 1) atual->baixo = &tabuleiro->grid[i+1][j];

            // Esquerda e direita
            if (j > 0) atual->esq = &tabuleiro->grid[i][j-1];
            if (j < tabuleiro->largura - 1) atual->dir = &tabuleiro->grid[i][j+1];

            // Diagonais
            if (i > 0 && j > 0) atual->dcesq = &tabuleiro->grid[i-1][j-1];
            if (i > 0 && j < tabuleiro->largura - 1) atual->dcdir = &tabuleiro->grid[i-1][j+1];
            if (i < tabuleiro->altura - 1 && j > 0) atual->dbesq = &tabuleiro->grid[i+1][j-1];
            if (i < tabuleiro->altura - 1 && j < tabuleiro->largura - 1) atual->dbdir = &tabuleiro->grid[i+1][j+1];
        }
    }
}

// Libera memória do tabuleiro
void Liberar_Tabuleiro(Tabuleiro *tabuleiro) {
    for (int i = 0; i < tabuleiro->largura; i++) {
        free(tabuleiro->grid[i]);
    }
    free(tabuleiro->grid);
}

void Distribuir_Bombas(Tabuleiro *tabuleiro, int num_bombas) {
    srand(time(NULL));
    int a, b;
    for (int i = 0; i < num_bombas; i++) {
        a = rand() % tabuleiro->altura;
        b = rand() % tabuleiro->largura;

        if (tabuleiro->grid[a][b].bomba == false) {
            tabuleiro->grid[a][b].bomba = true;
        } else {
            i--;
        }
    }
}

void Bombas_Perto_Celula(Tabuleiro *tabuleiro){
    for (int j = 0; j < tabuleiro->altura; j++) {
        for (int i = 0; i < tabuleiro->largura; i++){
            int cont = 0;
            Celula *celula = &tabuleiro->grid[j][i]; 
            if (celula->cima && celula->cima->bomba) cont++;
            if (celula->baixo && celula->baixo->bomba) cont++;
            if (celula->esq && celula->esq->bomba) cont++;
            if (celula->dir && celula->dir->bomba) cont++;
            if (celula->dbdir && celula->dbdir->bomba) cont++;
            if (celula->dbesq && celula->dbesq->bomba) cont++;
            if (celula->dcdir && celula->dcdir->bomba) cont++;
            if (celula->dcesq && celula->dcesq->bomba) cont++;

            celula->bombas = cont;
        }
    }
}


int bandeiras_perto(Tabuleiro *tabuleiro , int x, int y){
    if (x < 0 || x >= tabuleiro->altura || y < 0 || y >= tabuleiro->largura) {
        return EXIT_FAILURE; 
    }

    Celula *celula = &tabuleiro->grid[x][y];

    if (celula->aberto) {
        int cont = 0;
        if (celula->cima && (celula->cima->bandeira)) cont++;
        if (celula->baixo && (celula->baixo->bandeira)) cont++;
        if (celula->esq && (celula->esq->bandeira)) cont++;
        if (celula->dir && (celula->dir->bandeira)) cont++;
        if (celula->dbdir && (celula->dbdir->bandeira)) cont++;
        if (celula->dbesq && (celula->dbesq->bandeira)) cont++;
        if (celula->dcdir && (celula->dcdir->bandeira)) cont++;
        if (celula->dcesq && (celula->dcesq->bandeira)) cont++;
        return cont;
    }
    return EXIT_FAILURE;
}

int cobertos_perto(Tabuleiro *tabuleiro , int x, int y){
    if (x < 0 || x >= tabuleiro->altura || y < 0 || y >= tabuleiro->largura) {
        return EXIT_FAILURE; 
    }

    Celula *celula = &tabuleiro->grid[x][y];

    if (celula->aberto) {
        int cont = 0;
        if (celula->cima && !(celula->cima->aberto)) cont++;
        if (celula->baixo && !(celula->baixo->aberto)) cont++;
        if (celula->esq && !(celula->esq->aberto)) cont++;
        if (celula->dir && !(celula->dir->aberto)) cont++;
        if (celula->dbdir && !(celula->dbdir->aberto)) cont++;
        if (celula->dbesq && !(celula->dbesq->aberto)) cont++;
        if (celula->dcdir && !(celula->dcdir->aberto)) cont++;
        if (celula->dcesq && !(celula->dcesq->aberto)) cont++;
        return cont;
    }
    return EXIT_FAILURE; 
}

void bandeira(Tabuleiro *tabuleiro, int y, int x){
    if (x < 0 || x >= tabuleiro->altura || y < 0 || y >= tabuleiro->largura || tabuleiro->grid[x][y].aberto) {
        return; 
    }
    
    Celula *celula = &tabuleiro->grid[x][y];
    //se não houver bandeira ele coloca e se já houver ele tira
    if(!(celula->bandeira)) celula->bandeira = true;

    else celula->bandeira = false;
    
    return;
}


void Revelar_celulas(Tabuleiro *tabuleiro, int x, int y) {
    // Verifica limites do tabuleiro
    if (x < 0 || x >= tabuleiro->altura || y < 0 || y >= tabuleiro->largura ||tabuleiro->grid[x][y].bandeira ) {
        return; 
    }

    Celula *celula = &tabuleiro->grid[x][y];

    // Retorna se já estiver aberta ou se for uma bomba
    if (celula->bomba) {
        return;
    }

    if(celula->aberto == true){
        if (celula->bombas == bandeiras_perto(tabuleiro, x, y)) {
            if(celula->cima != NULL){
                if(!(celula->cima->bandeira) && !(celula->cima->aberto))
                Revelar_celulas(tabuleiro, x-1, y);
            }
            if(celula->baixo != NULL){
                if(!(celula->baixo->bandeira) && !(celula->baixo->aberto))
                Revelar_celulas(tabuleiro, x+1, y);
            }
            if(celula->esq != NULL){
                if(!(celula->esq->bandeira) && !(celula->esq->aberto))
                Revelar_celulas(tabuleiro, x, y -1);
            }
            if(celula->dcesq != NULL){
                if(!(celula->dcesq->bandeira) && !(celula->dcesq->aberto))
                Revelar_celulas(tabuleiro, x-1, y-1);
            }
            if(celula->dbesq != NULL){
                if(!(celula->dbesq->bandeira) && !(celula->dbesq->aberto))
                Revelar_celulas(tabuleiro, x+1, y-1);
            }
            if(celula->dir != NULL){
                if(!(celula->dir->bandeira) && !(celula->dir->aberto))
                Revelar_celulas(tabuleiro, x, y+1);
            }
            if(celula->dcdir != NULL){
                if(!(celula->dcdir->bandeira) && !(celula->dcdir->aberto))
                Revelar_celulas(tabuleiro, x-1, y+1);
            }
            if(celula->dbdir != NULL){
                if(!(celula->dbdir->bandeira) && !(celula->dbdir->aberto))
                Revelar_celulas(tabuleiro, x+1, y+1);
            }
        }return;
    }

    celula->aberto = true;

    // Abre automaticamente as células vizinhas se não houver bombas ao redor
    if (celula->bombas == 0) {
        if(celula->cima)Revelar_celulas(tabuleiro, x-1, y);
        if(celula->baixo)Revelar_celulas(tabuleiro, x+1, y);
        if(celula->esq)Revelar_celulas(tabuleiro, x, y -1);
        if(celula->dcesq)Revelar_celulas(tabuleiro, x-1, y-1);
        if(celula->dbesq)Revelar_celulas(tabuleiro, x+1, y-1);
        if(celula->dir)Revelar_celulas(tabuleiro, x, y+1);
        if(celula->dcdir)Revelar_celulas(tabuleiro, x-1, y+1);
        if(celula->dbdir)Revelar_celulas(tabuleiro, x+1, y+1);
    }
}


void colocarBandeira(Tabuleiro *tabuleiro, int x, int y) {
    if (x < 0 || x >= tabuleiro->altura || y < 0 || y >= tabuleiro->largura)
        return;
    Celula *cel = &tabuleiro->grid[x][y];
    if (!cel->aberto && !cel->bandeira) {
        cel->bandeira = true;
    }
}

void Dica(Tabuleiro *tabuleiro) {
    bool movimento_executado = false;
    
    // Percorre o tabuleiro (i: linhas, j: colunas)
    for (int i = 0; i < tabuleiro->altura && !movimento_executado; i++) {
        for (int j = 0; j < tabuleiro->largura && !movimento_executado; j++) {

            Celula *celula = &tabuleiro->grid[i][j];

            // Processa células abertas, com bomb count diferente de zero e que ainda não receberam dica
            if (celula->aberto && celula->bombas != 0 && !celula->dica_aplicada) {
                int cobertos = cobertos_perto(tabuleiro, i, j);

                // Se todos os vizinhos cobertos devem ser bombas, coloca bandeira em cada um que ainda não tem
                if (cobertos == celula->bombas) {
                    if (i - 1 >= 0 && j - 1 >= 0)
                        colocarBandeira(tabuleiro, i - 1, j - 1);
                    if (i - 1 >= 0)
                        colocarBandeira(tabuleiro, i - 1, j);
                    if (i - 1 >= 0 && j + 1 < tabuleiro->largura)
                        colocarBandeira(tabuleiro, i - 1, j + 1);
                    if (j - 1 >= 0)
                        colocarBandeira(tabuleiro, i, j - 1);
                    if (j + 1 < tabuleiro->largura)
                        colocarBandeira(tabuleiro, i, j + 1);
                    if (i + 1 < tabuleiro->altura && j - 1 >= 0)
                        colocarBandeira(tabuleiro, i + 1, j - 1);
                    if (i + 1 < tabuleiro->altura)
                        colocarBandeira(tabuleiro, i + 1, j);
                    if (i + 1 < tabuleiro->altura && j + 1 < tabuleiro->largura)
                        colocarBandeira(tabuleiro, i + 1, j + 1);
                    
                    celula->dica_aplicada = true;
                    movimento_executado = true;
                }
                else {
                    // Se o número de bandeiras já marcadas for igual ao número de bombas
                    // e ainda houver vizinhos cobertos, revela os vizinhos.
                    int bandeiras = bandeiras_perto(tabuleiro, i, j);
                    if (bandeiras == celula->bombas && cobertos > bandeiras) {
                        Revelar_celulas(tabuleiro, i, j);
                        celula->dica_aplicada = true;
                        movimento_executado = true;
                    }
                }
            }
        }
    }
    
    if (!movimento_executado) {
        printf("Nao foi possivel dar uma dica deterministica para o jogo atual.\n");
    }
}


bool Jogador_venceu(Tabuleiro *tabuleiro, int bombas_totais) {
    int abertas = 0;
    int total_celulas = tabuleiro->largura * tabuleiro->altura;

    for (int i = 0; i < tabuleiro->altura; i++) {
        for (int j = 0; j < tabuleiro->largura; j++) {
            if (tabuleiro->grid[i][j].aberto) abertas++;
        }
    }
    return (abertas == total_celulas - bombas_totais);
}

bool Jogador_perdeu (Tabuleiro *tabuleiro, int x, int y) {
    Celula *celula = &tabuleiro->grid[x][y];
    if (celula->bomba && !(celula->bandeira)) {
        return true;
    }
    return false;
}

void Mostrar_tabuleiro (Tabuleiro *tabuleiro) {
    for (int i = 0; i < tabuleiro->altura; i++) {
        for (int j = 0; j < tabuleiro->largura; j++) {
            Celula *celula = &tabuleiro->grid[i][j];
            if (!(celula->aberto)) celula->aberto = true;
        }
    }
    return;
}

int ContarBandeiras(Tabuleiro *tabuleiro) {
    int contador = 0;
    for (int i = 0; i < tabuleiro->largura; i++) {
        for (int j = 0; j < tabuleiro->altura; j++) {
            Celula *celula = &tabuleiro->grid[j][i];
            if (celula->bandeira) {
                contador++;
            }
        }
    }
    return contador;
}

