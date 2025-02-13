#ifndef CAMPOMINADO_H
#define CAMPOMINADO_H

typedef struct Info {
    bool aberto, bandeira, bomba;
    short int bombas, cobertos; 
    int x,y;
    
} Info;

typedef struct Celula {
    Info dados;
    struct Celula *cima, *baixo, *esq, *dir, *dcesq, *dcdir, *dbesq, *dbdir;
} Celula;

Celula* CriarNova(Info info);
void Criar_Matriz();


#endif