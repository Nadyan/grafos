#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdlib.h>

#define ERRO_ALOCACAO -1
#define ERRO_LISTA_VAZIA -2
#define ERRO_POSICAO_INVALIDA -3
#define ERRO -4

typedef struct elemento {
    void *info;
    struct elemento *proximo;
} Elemento;

typedef struct {
    size_t tamInfo;
    Elemento *cabeca;
} Lista;

void inicializa_lista(Lista *l, size_t t);
void mostra_lista(Lista l, void (*mostra_info)(void *));

int insereNoInicio(Lista *l, void *info);
int insereNoFim(Lista *l, void *info);
int insereNaPosicao(Lista *l, void *info, int pos);
int insereEmOrdem(Lista *l, void *info, int (*compara_float)(void *, void *));
int removeDoInicio(Lista *l, void *info);
int removeNaPosicao(Lista *l, void *info, int pos);
int removeInfo(Lista *l, void *info);
int modificaNaPosicao(Lista *l, void *info, int pos);
int leNaPosicao(Lista *l, void *info, int pos);
int limpa_lista(Lista *l);


//TEG
void dfs_preordem(Lista *l, int u, int *visitados);
void dfs_emordem(Lista *l, int u, int *visitados);
void dfs_posordem(Lista *l, int u, int *visitados);

Elemento *aloca_elemento(size_t t, void *info);

#endif // LISTA_H_INCLUDED
