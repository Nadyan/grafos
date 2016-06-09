#include "Lista.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void inicializa_lista(Lista *l, size_t t)
{
    l->tamInfo = t;
    l->cabeca = NULL;
}

int insereNoInicio(Lista *l, void *info)
{
    Elemento *p = aloca_elemento(l->tamInfo, info);
    p->proximo = l->cabeca;
    l->cabeca = p;
    return 1; //Sucesso
}

int removeDoInicio(Lista *l, void *info)
{
    if (l->cabeca == NULL)
    {
        return ERRO_LISTA_VAZIA;
    }
    Elemento *p = l->cabeca;
    l->cabeca = p->proximo;
    memcpy(info, p->info, l->tamInfo);
    free(p->info);
    free(p);
    return 1; //Sucesso
}

int insereNoFim(Lista *l, void *info)
{
    if(l->cabeca == NULL)
    {
        return insereNoInicio(l, info);
    }

    Elemento *aux = l->cabeca;
    while(aux->proximo != NULL)
    {
        aux = aux->proximo;
    }

    Elemento *p = aloca_elemento(l->tamInfo, info);
    p->proximo = NULL;
    aux->proximo = p;
    return 1; //Sucesso
}

int removeDoFim(Lista *l, void *info)
{
    if (l->cabeca == NULL)
        return ERRO_LISTA_VAZIA;

    if(l->cabeca->proximo == NULL)
        return removeDoInicio(l, info);

    Elemento *aux = l->cabeca;
    while(aux->proximo->proximo != NULL)
    {
        aux = aux->proximo;
    }
    memcpy(info, aux->proximo->info, l->tamInfo);
    free(aux->proximo->info);
    free(aux->proximo);
    aux->proximo = NULL;
    return 1; //Sucesso
}

int insereNaPosicao(Lista *l, void *info, int pos)
{
    if(pos < 0)
        return ERRO_POSICAO_INVALIDA;
    if(pos == 0)
        return insereNoInicio(l, info);

    Elemento *aux = l->cabeca;
    int cont = 0;
    while(cont < pos-1 && aux->proximo != NULL)
    {
        aux = aux->proximo;
        cont++;
    }
    if(cont != pos-1)
        return ERRO_POSICAO_INVALIDA;

    Elemento *novo = aloca_elemento(l->tamInfo, info);
    if(novo == NULL)
        return 0; //Fracasso
    novo->proximo = aux->proximo;
    aux->proximo = novo;
    return 1; //Sucesso
}

int removeNaPosicao(Lista *l, void *info, int pos)
{
    if(pos < 0)
        return ERRO_POSICAO_INVALIDA;
    if(pos == 0)
        return removeDoInicio(l, info);

    Elemento *aux = l->cabeca;
    int cont = 0;
    while(cont < pos-1 && aux->proximo != NULL)
    {
        aux = aux->proximo;
        cont++;
    }
    if (cont != pos-1 || aux->proximo == NULL)
        return ERRO_POSICAO_INVALIDA;

    memcpy(info, aux->proximo->info, l->tamInfo);

    Elemento *aux2 = aux->proximo;
    aux->proximo = aux->proximo->proximo;

    free(aux2->info);
    free(aux2);
    return 1; //Sucesso
}

int insereEmOrdem(Lista *l, void *info, int (*compara_info)(void*, void *))
{
    int cont = 0;
    Elemento *aux = l->cabeca;
    while(aux != NULL && compara_info(aux->info, info) < 0)
    {
        aux = aux->proximo;
        cont++;
    }
    return insereNaPosicao(l, info, cont);
}

int removeInfo(Lista *l, void *info)
{
    if(l->cabeca == NULL)
        return ERRO_LISTA_VAZIA;
    int cont = 0;
    Elemento *aux = l->cabeca;
    while(aux->proximo != NULL && memcmp(aux->info, info, l->tamInfo) != 0)
    {
        aux = aux->proximo;
        cont++;
    }
    if (memcmp(aux->info, info, l->tamInfo) == 0)
        return removeNaPosicao(l, info, cont);

	return ERRO;
}

int modificaNaPosicao(Lista *l, void *info, int pos)
{
    if(pos < 0)
        return ERRO_POSICAO_INVALIDA;

    Elemento *aux = l->cabeca;
    int cont = 0;
    while(cont != pos && aux->proximo != NULL)
    {
        aux = aux->proximo;
        cont++;
    }
    if(cont != pos)
        return ERRO_POSICAO_INVALIDA;
    memcpy(aux->info, info, l->tamInfo);
    return 1; //Sucesso
}

int leNaPosicao(Lista *l, void *info, int pos)
{
    if(pos < 0)
        return ERRO_POSICAO_INVALIDA;

    Elemento *aux = l->cabeca;
    int cont = 0;
    while(cont != pos && aux->proximo != NULL)
    {
        aux = aux->proximo;
        cont++;
    }
    if(cont != pos)
        return ERRO_POSICAO_INVALIDA;
    memcpy(info, aux->info, l->tamInfo);
    return 1; //Sucesso
}

Elemento *aloca_elemento(size_t t, void *info)
{
    Elemento *p;
    p = (Elemento*) malloc(sizeof(Elemento));

    if(p == NULL)
        return NULL;

    p->info = malloc(t);
    if (p->info == NULL)
    {
        free(p);
        return NULL;
    }
    memcpy(p->info, info, t);
    return p;
}

void mostra_lista(Lista l, void (*mostra_info)(void *))
{
    Elemento *aux = l.cabeca;
    if (aux == NULL)
        return;

    while(aux != NULL)
    {
        mostra_info(aux->info);
        aux = aux->proximo;
    }
}
int limpa_lista(Lista *l)
{
	Elemento *aux = l->cabeca;
	// Lista vazia
	if (aux == NULL)
		return 1;

	while (aux != NULL)
	{
		if (aux->proximo == NULL)
		{
			l->cabeca = NULL;
			free(aux->info);
			free(aux);
			return 1;
		}

		while (aux->proximo->proximo == NULL)
		{
			aux = aux->proximo;
		}

		free(aux->proximo->info);
		free(aux->proximo);
		aux->proximo = NULL;
		aux = l->cabeca;
	}

	return 1;
}

/*
FUNCAO RECURSIVA.
Imprime toda vez que o dfs comeca a rodar no vertice u,
ou seja, assim que ele visita o vertice.
*/

void dfs_preordem(Lista *listaAdj, int u, int *visitados)
{
    //Imprime vertice assim que u eh visitado
    printf("%d ", u);
    //Marca como visitado
    visitados[u] = 1;

    //Pega a lista dos vertices que estao ligados com o vertice u
    Lista l;
    leNaPosicao(listaAdj, &l, u);
    //Percore todos os filhos de u
    Elemento *aux = l.cabeca;
    //Enquanto ele ainda tiver filhos
    while(aux != NULL)
    {
        // Pegue o numero do vertice do filho de u e converta
        // para um inteiro
        int *a = (int*) aux->info;
        // Se ele nao visitou, rode o dfs naquele vertice
        if (visitados[*a] != 1) {
            dfs_preordem(listaAdj, *a, visitados);
        }
        //Avance o filho
        aux = aux->proximo;
    }

}

/*
FUNCAO RECURSIVA.
Imprime o vertice u se ele nao tem filhos, ou a primeira
vez que ele volta do seu primeiro filho.
*/
void dfs_emordem(Lista *listaAdj, int u, int *visitados)
{
    // Variavel para controle para ele nao imprimir o vertice u varias vezes
    int imprimiu = 0;
    // Marca como visitado
    visitados[u] = 1;
    // Pega a lista dos vertices que estao ligados com o vertice u
    Lista l;
    leNaPosicao(listaAdj, &l, u);
    //Percore todos os filhos de u
    Elemento *aux = l.cabeca;
    // Se ele nao tiver filhos, imprima o vertice u
    if (aux == NULL) {
        printf("%d ", u);
    }
    while(aux != NULL)
    {
        // Pegue o numero do vertice do filho de u e converta
        // para um inteiro
        int *a = (int*) aux->info;
        // Se ele nao visitou, rode o dfs naquele vertice
        if (visitados[*a] != 1) {
            dfs_emordem(listaAdj, *a, visitados);
            // Se ele tem filhos, a primeira vez que ele voltar de um filho
            // ele vai imprimir o no u
            if(!imprimiu) {
                printf("%d ", u);
                imprimiu = 1;
            }
        }
        // Avanca nos filhos
        aux = aux->proximo;
    }
}

/*
FUNCAO RECURSIVA.
Imprime o vertice u apos ele percorrer todos os seus filhos
*/
void dfs_posordem(Lista *listaAdj, int u, int *visitados)
{
    // Marca u como visitado
    visitados[u] = 1;
    // Pega a lista dos vertices que estao ligados com o vertice u
    Lista l;
    leNaPosicao(listaAdj, &l, u);
    //Percore todos os filhos de u
    Elemento *aux = l.cabeca;
    // Enquanto ele tem filhos, faca o while
    while(aux != NULL)
    {
        // Pegue o numero do vertice do filho de u e converta
        // para um inteiro
        int *a = (int*) aux->info;
        // Rode dfs no vertice a se ele nao o visitou
        if (visitados[*a] != 1) {
            dfs_posordem(listaAdj, *a, visitados);
        }
        aux = aux->proximo;
    }
    // Imprima vertice u
    printf("%d ", u);
}
