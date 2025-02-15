#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "campominado.h"

void Dados_iniciais (int *altura, int *largura, int *num_bombas) {
    // declaração de variáveis: as variáveis auxiliares serão utilziadas pra não ficar mudando o valor dentro de main todo tempo
    int aux1, aux2, aux3;
    printf("Por favor, insira a altura desejada: (Min = 5, Max = 40)\n");
    scanf("%d", &aux1);
    while (aux1 > 40) {
        printf("Por favor, insira a altura desejada, agora respeitando os limites (Min = 5, Max = 40)\n");
    scanf("%d", &aux1);
    }

    printf("Por favor, insira a largura desejada: (Min = 5, Max = 26)\n");
    scanf("%d", &aux2);

    while (aux2 > 26) {
        printf("Por favor, insira a largura desejada, agora respeitando os limites (Min = 5, Max = 26)\n");
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
    *altura = aux1;
    *largura = aux2;
}


// Cria uma nova célula com valores padrões
Celula* CriarNova(int x, int y) {
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    if (!nova) {
        printf("Erro ao alocar memória para célula.\n");
        exit(1);
    }

    // Valores padrão
    nova->aberto = false;
    nova->bandeira = false;
    nova->bomba = false;
    nova->bombas = 0;
    nova->x = x;
    nova->y = y;

    // Ponteiros nulos
    nova->cima = nova->baixo = nova->esq = nova->dir = NULL;
    nova->dcesq = nova->dcdir = nova->dbesq = nova->dbdir = NULL;

    return nova;
}

// Inicializa o tabuleiro com uma matriz de células
void Inicializando_Tabuleiro(Tabuleiro *tabuleiro, int altura, int largura) {
    tabuleiro->altura = altura;
    tabuleiro->largura = largura;

    // Alocando memória para o grid (matriz de células)
    tabuleiro->grid = (Celula**)malloc(largura * sizeof(Celula));
    if (!tabuleiro->grid) {
        printf("Erro ao alocar memória para o tabuleiro.\n");
        exit(1);
    }

    for (int i = 0; i < largura; i++) {
        tabuleiro->grid[i] = (Celula*)malloc(altura * sizeof(Celula));
        if (!tabuleiro->grid[i]) {
            printf("Erro ao alocar memória para linha do tabuleiro.\n");
            exit(1);
        }

        // Criando células
        for (int j = 0; j < altura; j++) {
            tabuleiro->grid[i][j] = *CriarNova(j, i);
        }
    }

    // Conecta as células vizinhas
    Conectar_Vizinhos(tabuleiro);
}

// Conecta as células vizinhas usando os ponteiros
void Conectar_Vizinhos(Tabuleiro *tabuleiro) {
    for (int i = 0; i < tabuleiro->largura; i++) {
        for (int j = 0; j < tabuleiro->altura; j++) {
            Celula *atual = &tabuleiro->grid[i][j];

            // Cima e baixo
            if (i > 0) atual->cima = &tabuleiro->grid[i-1][j];
            if (i < tabuleiro->largura - 1) atual->baixo = &tabuleiro->grid[i+1][j];

            // Esquerda e direita
            if (j > 0) atual->esq = &tabuleiro->grid[i][j-1];
            if (j < tabuleiro->altura - 1) atual->dir = &tabuleiro->grid[i][j+1];

            // Diagonais
            if (i > 0 && j > 0) atual->dcesq = &tabuleiro->grid[i-1][j-1];
            if (i > 0 && j < tabuleiro->altura - 1) atual->dcdir = &tabuleiro->grid[i-1][j+1];
            if (i < tabuleiro->largura - 1 && j > 0) atual->dbesq = &tabuleiro->grid[i+1][j-1];
            if (i < tabuleiro->largura - 1 && j < tabuleiro->altura - 1) atual->dbdir = &tabuleiro->grid[i+1][j+1];
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
    int a, b;
    for (int i = 0; i < num_bombas; i++) {
        a = rand() % tabuleiro->altura;
        b = rand() % tabuleiro->largura;

        if (tabuleiro->grid[b][a].bomba == false) {
            tabuleiro->grid[b][a].bomba = true;
        } else {
            i--;
        }
    }
}

void Bombas_Perto_Celula(Tabuleiro *tabuleiro){
    for (int i = 0; i < tabuleiro->largura; i++) {
        for (int j = 0; j < tabuleiro->altura; j++){
            int cont = 0;
            if (tabuleiro->grid[i][j].cima && tabuleiro->grid[i][j].cima->bomba) cont++;
            if (tabuleiro->grid[i][j].baixo && tabuleiro->grid[i][j].baixo->bomba) cont++;
            if (tabuleiro->grid[i][j].esq && tabuleiro->grid[i][j].esq->bomba) cont++;
            if (tabuleiro->grid[i][j].dir && tabuleiro->grid[i][j].dir->bomba) cont++;
            if (tabuleiro->grid[i][j].dbdir && tabuleiro->grid[i][j].dbdir->bomba) cont++;
            if (tabuleiro->grid[i][j].dbesq && tabuleiro->grid[i][j].dbesq->bomba) cont++;
            if (tabuleiro->grid[i][j].dcdir && tabuleiro->grid[i][j].dcdir->bomba) cont++;
            if (tabuleiro->grid[i][j].dcesq && tabuleiro->grid[i][j].dcesq->bomba) cont++;
            tabuleiro->grid[i][j].bombas = cont;
            
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

void bandeira(Tabuleiro *tabuleiro, int x, int y){
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
    if (x < 0 || x >= tabuleiro->altura || y < 0 || y >= tabuleiro->largura) {
        return; 
    }
    
    Celula *celula = &tabuleiro->grid[y][x];

    if (celula->aberto) {
        //contando as bandeiras ao redor  
        int cont = bandeiras_perto(tabuleiro, x, y);
        //se o numero de bandeiras for igual ao de bombas as células cobertas e sem bandeira sâo clicadas 
        if( cont == celula->bombas){
            if(celula->dcesq && !(celula->dcesq->bandeira) && !(celula->dcesq->aberto))
                Revelar_celulas(tabuleiro, x - 1, y - 1); 
            if(celula->esq && !(celula->esq->bandeira)&& !(celula->esq->aberto))
                Revelar_celulas(tabuleiro, x, y - 1); 
            if(celula->dbesq && !(celula->dbesq->bandeira)&& !(celula->dbesq->aberto))     
                Revelar_celulas(tabuleiro, x + 1, y - 1);
            if(celula->cima && !(celula->cima->bandeira)&& !(celula->cima->aberto))  
                Revelar_celulas(tabuleiro, x - 1, y);
            if(celula->baixo && !(celula->baixo->bandeira)&& !(celula->baixo->aberto))     
                Revelar_celulas(tabuleiro, x + 1, y);
            if(celula->dcdir && !(celula->dcdir->bandeira)&& !(celula->dcdir->aberto))    
                Revelar_celulas(tabuleiro, x - 1, y + 1); 
            if(celula->dir && !(celula->dir->bandeira)&& !(celula->dir->aberto))
                Revelar_celulas(tabuleiro, x, y + 1); 
            if(celula->dbdir && !(celula->dbdir->bandeira)&& !(celula->dbdir->aberto))     
                Revelar_celulas(tabuleiro, x + 1, y + 1);  
        }
        return;
    }

    celula->aberto = true;

    if (celula->bomba) {
        return;
    }
    //se for 0 ele clica em todos os cobertos ao redor dele 
    if (celula->bombas == 0) {
        if(!(celula->dcesq->aberto))
            Revelar_celulas(tabuleiro, x - 1, y - 1);
        if(!(celula->esq->aberto))
            Revelar_celulas(tabuleiro, x, y - 1);
        if(!(celula->dbesq->aberto))   
            Revelar_celulas(tabuleiro, x + 1, y - 1);
        if(!(celula->cima->aberto))  
            Revelar_celulas(tabuleiro, x - 1, y); 
        if(!(celula->baixo->aberto))    
            Revelar_celulas(tabuleiro, x + 1, y);   
        if(!(celula->dcdir->aberto)) 
            Revelar_celulas(tabuleiro, x - 1, y + 1);
        if(!(celula->dir->aberto))  
            Revelar_celulas(tabuleiro, x, y + 1);  
        if(!(celula->dbdir->aberto))    
            Revelar_celulas(tabuleiro, x + 1, y + 1);  
    }
}

void Dica(Tabuleiro *tabuleiro){
    //percorre ate achar uma célula aberta em que a dica pode ser aplicada 
    for (int i = 0; i < tabuleiro->largura; i++) {
        for (int j = 0; j < tabuleiro->altura; j++){

            Celula *celula = &tabuleiro->grid[i][j];

            if((celula->aberto)){
                int cont = cobertos_perto(tabuleiro, i ,j);
                //se o numero de cobertos perto e de bombas for igual todos tem bomba. ent ele coloca bandeira
                if(cont == celula->bombas){
                    if(!(celula->dcesq->bandeira))
                        bandeira(tabuleiro, i - 1, j - 1);
                    if(!(celula->esq->bandeira))
                        bandeira(tabuleiro, i, j - 1);
                    if(!(celula->dbesq->bandeira))   
                        bandeira(tabuleiro, i + 1, j - 1);
                    if(!(celula->cima->bandeira))  
                        bandeira(tabuleiro, i - 1, j); 
                    if(!(celula->baixo->bandeira))    
                        bandeira(tabuleiro, i + 1, j);   
                    if(!(celula->dcdir->bandeira)) 
                        bandeira(tabuleiro, i - 1, j + 1);
                    if(!(celula->dir->bandeira))  
                        bandeira(tabuleiro, i, j + 1);  
                    if(!(celula->dbdir->bandeira))    
                        bandeira(tabuleiro, i + 1, j + 1);    
                }
                else{
                    //se o numero de bandeiras e bombas ao redor é igual ent as celulas restantes são clicadas (o programa assume que as bandeiras posicionadas estão corretas )
                    int cont2 = bandeiras_perto(tabuleiro, i, j);
                    if(cont2 == celula->bombas && cont > cont2){
                        Revelar_celulas(tabuleiro, i, j);
                    }
                }
                //assim q o programa realizar a primeira dica ele para
                return;
            }
        }
    }
    //se não encontrar nenhuma célula em que possa aplicar a dica 
    printf("não foi possível dar uma dica para o jogo atual, é possível que a jogada a seguir dependa de sorte.");
    return;
}

bool Jogador_venceu(Tabuleiro *tabuleiro, int bombas_totais) {
    int abertas = 0;
    int total_celulas = tabuleiro->largura * tabuleiro->altura;

    for (int i = 0; i < tabuleiro->largura; i++) {
        for (int j = 0; j < tabuleiro->altura; j++) {
            if (tabuleiro->grid[i][j].aberto) abertas++;
        }
    }
    return (abertas == total_celulas - bombas_totais);
}

bool Jogador_perdeu (Tabuleiro *tabuleiro, int x, int y) {
    Celula *celula = &tabuleiro->grid[x][y];
    return(celula->bomba == true);
}

void Mostrar_tabuleiro (Tabuleiro *tabuleiro) {
    for (int i = 0; i < tabuleiro->largura; i++) {
        for (int j = 0; j < tabuleiro->altura; j++) {
            Celula *celula = &tabuleiro->grid[i][j];
            if (!(celula->aberto)) celula->aberto = true;
        }
    }
    return;
}

