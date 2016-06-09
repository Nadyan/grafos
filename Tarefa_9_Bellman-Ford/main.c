#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Lista.h"

#define INFINITO 999999999

typedef struct{
    int origem;
    int peso;
    int destino;
} Aresta;

Aresta *arestas;    //vetor de arestas
Lista *precedentes; //lista de precedentes para cada vertice

void bellmanFord();                                                                     //funçao que inicia elementos e faz chamada do inicio
void calculaBellmanFord(int inicio, int qtdVertices, int numAresta, int *distancias);   //funçao que calcula as distancias
void adjacente(int **matriz, int quantidadeVertices);                                   //funçao para criar a matriz adjacente com peso
void printInt(void *i);                                                                 //funçao para imprimir elemento da lista como int
int compara_info(void *info1, void*info2);                                              //funçao para comparar elementos para adicionar na lista

int main(){
	int escolha;

	do{
        printf("\n                TEORIA DOS GRAFOS\n");
        printf("\n    1 - Algoritmo de Bellman-Ford\n");

        printf("    0 - Sair\n\n");

        printf("    Informe a operacao a ser efetuada: ");

		scanf("%d", &escolha);
		system("cls || clear");

		switch(escolha){
			case 1:
				bellmanFord();
				break;
			case 0:
				break;
		}
	}while(escolha != 0);

    return 0;
}

void bellmanFord(){
    int i, j;                       //contadores
    int qtdVertices, qtdArestas;    //quantidade de elementos do grafo
    int numAresta = 0;              //contador para o numero da aresta
    int *distancias;                //vetor de distancias
    int **matriz;                   //matriz de adjacencia com pesos
    int inicio;                     //nó inicial

    printf("\n    Informe a quantidade de vertices: ");
    scanf("%d", &qtdVertices);
    printf("\n    Informe a quantidade de arestas: ");
    scanf("%d", &qtdArestas);

    /*-alocação e montagem da matriz adjacente-*/
    matriz = (int**)malloc(sizeof(int*) * qtdVertices);         //aloca as linhas da matriz
    for(i = 0; i < qtdVertices; i++){
        matriz[i] = (int*)malloc(sizeof(int) * qtdVertices);   // aloca as colunas da matriz
        for(j = 0; j < qtdVertices; j++){
            matriz[i][j] = INFINITO;                     //inicializa a matriz com infinito pois bellman ford aceita arestas negativas
        }
    }
    adjacente(matriz, qtdVertices);                      //monta a matriz adjacente
    /*-----------------------------------------*/

    distancias = (int*)malloc(sizeof(int) * qtdVertices);
    arestas = (Aresta*)malloc(sizeof(Aresta) * qtdArestas);   //aloca o vetor de arestas
    precedentes = (Lista*)malloc(sizeof(Lista) * qtdVertices);

    for(i = 0; i < qtdVertices; i++){
        inicializa_lista(&precedentes[i], sizeof(int)); //para cada nó, inicializa uma lista de precedentes

        for(j = 0; j < qtdVertices; j++){

            //se a tem ligaçao entre i e j, preenche a struct para o nó numAresta
            if(matriz[i][j] != INFINITO){
                    arestas[numAresta].origem = i;
                    arestas[numAresta].destino = j;
                    arestas[numAresta].peso = matriz[i][j];

                    numAresta++;
            }
        }
    }

    printf("\n    Informe o vertice inicial: ");
    scanf("%d", &inicio);
    inicio--; //pois nosso grafo começa no vertice 1, enquanto a matriz no 0

    system("cls");

    calculaBellmanFord(inicio, qtdVertices, numAresta, distancias);


    /*IMPRIME DISTANCIAS*/
    printf("\n\n    --------------------- RESULTADOS ----------------------\n");
    printf("\n    Distancias do vertice inicial %d para os demais vertices:\n\n", inicio+1);

    printf("    Vertice:     ");
    for (i = 0; i < qtdVertices; ++i)
        printf("  %d\t| ", i+1);
    printf("\n");

    printf("    Distancia:   ");
    for (i = 0; i < qtdVertices; ++i)
        if(distancias[i] == INFINITO){  //se for INFINITO, ou seja, se o vertice nao é alcançavel a partir do vertice inicial
            printf("  -\t| ");
        }else{
            printf("  %d\t| ", distancias[i]);
        }
    printf("\n");

    printf("    Precedentes: ");
    for (i = 0; i < qtdVertices; i++){
        if(i == inicio)
            printf("  -\t| "); //se for o vertice inicial nao possui precedentes
        else{
            printf("  ");
            mostra_lista(precedentes[i], printInt);
            printf("\t| ");
        }
    }

    printf("\n\n    ");

    free(matriz);
    free(distancias);
    free(arestas);
    free(precedentes);

    system("pause");
    system("cls || clear");
}

void calculaBellmanFord(int inicio, int qtdVertices, int numArestas, int *distancias){
    int i, j; //contadores

    for(i = 0; i < qtdVertices; i++){
        distancias[i] = INFINITO; //inicia vetor de distancias com INFINITO
    }
    distancias[inicio] = 0;       //e a distancia para o inicio com 0

    for(i = 0; i < qtdVertices-1; i++){ //para cada vertice
        for(j = 0; j < numArestas; j++){ //analisa todas as arestas

            //se a distancia do inicio + peso da aresta < distancia armazenada no vertice de destino
            if(distancias[arestas[j].origem] + arestas[j].peso < distancias[arestas[j].destino]
               && arestas[j].destino != inicio){

                distancias[arestas[j].destino] = distancias[arestas[j].origem] + arestas[j].peso;    //atualiza vetor de distancias

                limpa_lista(&precedentes[(arestas[j].destino)]);                                     //atualiza a lista de precedentes do nó
                insereEmOrdem(&precedentes[(arestas[j].destino)], &arestas[j].origem, compara_info); //atualiza a lista de precedentes do nó
            }
        }
    }
}

/*funçao que mostra o elemento da lista como int*/
void printInt(void *i){
    int *n = (int*)i;
    (*n)++;
    printf("%d ", *n);
}

void adjacente(int **matriz, int quantidadeVertices){
	FILE *f = fopen("grafo2.txt", "r+");
	int x, y; //campos da matriz
	int peso;

	if(f == NULL)
			printf("Erro ao abrir o arquivo!\n");
	else{
		while((fscanf(f," %d %d %d\n", &x, &peso, &y)) != EOF){     //le uma linha de cada vez
			if(matriz[x-1][y-1] == INFINITO){ /*se ainda nao foi inserido nenhum peso*/
                matriz[x-1][y-1] = peso; /*insere o peso lido*/
			}else{
                if(matriz[x-1][y-1] > peso) /*se ja foi inserido um peso mas ele é maior do que o lido*/
                    matriz[x-1][y-1] = peso; /*insere o peso novo menor*/
			}
		}

        /* //imprime a matriz
		printf("\n\n****** Matriz de adjacencia ******\n\n");
		for(x = 0; x < quantidadeVertices; x++){
			for(y = 0; y < quantidadeVertices; y++){
				if(matriz[x][y] == INFINITO)
                    printf("0 ");
				else
                    printf("%d ", matriz[x][y]);
			}
			printf("\n");
		}
		fclose(f);

        printf("\n...................................\n\n");
        */
	}
}

int compara_info(void *info1, void*info2){
    return 0;
    if(*(int*)info2 < *(int*)info1)
        return -1;

    if(*(int*)info2 == *(int*)info1)
        return 0;

    if(*(int*)info2 > *(int*)info1)
        return 1;
}
