#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Lista.h"

#define INFINITO 999999999

void dijkstra();
void printInt(void *i);
void adjacente(int **matriz, int quantidadeVertices);
int minimo(int *distancia, int *visitados, int qtdVertices);


int main(){
	int escolha;

	do{
        printf("\n                TEORIA DOS GRAFOS\n");
        printf("\n    1 - Algoritmo de Dijkstra\n");

        printf("    0 - Sair\n\n");

        printf("    Informe a operacao a ser efetuada: ");

		scanf("%d", &escolha);
		system("cls || clear");

		switch(escolha){
			case 1:
				dijkstra();
				break;
			case 0:
				break;
		}
	}while(escolha != 0);

    return 0;
}

void dijkstra(){
    int **matriz;
    int *distancia, *visitados;
    int i, j, qtdVertices;
    int inicio;
    int infinito = 0; //flag para impressao dos resultados
    Lista precedentes;

    inicializa_lista(&precedentes, sizeof(Lista));

    printf("\n    Informe a quantidade de vertices: ");
    scanf("%d", &qtdVertices);
    printf("\n    Vertice inicial: ");
    scanf("%d", &inicio);


    /*-alocação e montagem da matriz adjacente-*/
    matriz = malloc(sizeof(int*) * qtdVertices);  //aloca as linhas da matriz
    for(i = 0; i < qtdVertices; i++){
        matriz[i] = malloc(sizeof(int) * qtdVertices);   // aloca as colunas da matriz
        for(j = 0; j < qtdVertices; j++){
            matriz[i][j] = -1;    //inicializa a matriz com -1
        }
    }
    adjacente(matriz, qtdVertices);  //monta a matriz adjacente
    /*-----------------------------------------*/

    /*-alocação do vetores de distancias e visitados-*/
    distancia = malloc(sizeof(int*) * qtdVertices);
    visitados = malloc(sizeof(int*) * qtdVertices);

    for(i = 0; i < qtdVertices; i++){
        distancia[i] = INFINITO;    /*inicia as distancias com infinito*/
        visitados[i] = 0;           /*inicia visitados com 0*/
    }

    distancia[inicio-1] = 0; /*distancia para o inicio é sempre 0, -1 pois nosso grafo começa no v = 1
                               enquanto a matriz começa em v = 0                                      */

    //n listas de precedentes
    for(i = 0; i < qtdVertices; i++){
        Lista list;
        inicializa_lista(&list, sizeof(int));
        insereNoFim(&precedentes, &list);
    }

    /*inicio das interações*/
    for(i = 0; i < qtdVertices; i++){
        int min;

        min = minimo(distancia, visitados, qtdVertices); //procura o vertice de menor distancia
        visitados[min] = 1; //marca como visitado;

        for(j = 0; j < qtdVertices; j++){
            if(!visitados[j]  /*se ainda nao foi visitado*/
               && (matriz[min][j] != -1)  /*e possui ligação*/
               && (distancia[min] != INFINITO)   /*e nao é distancia infinita*/
               && ((distancia[min] + matriz[min][j]) <= distancia[j])){  /*e a distancia é menor que a atual*/

                    if(distancia[min] + matriz[min][j] == distancia[j]){ /*se a dist. do no inicial + ate o no de menor dist for */
                        Lista list;                                      /*igual, adicione tambem como precedente                */
                        removeNaPosicao(&precedentes, &list, j);
                        insereNoFim(&list, &min);
                        insereNaPosicao(&precedentes, &list, j);
                    }else{ /*e achou um caminho menor, retira os precedentes e insere o novo precedente*/
                        Lista list;
                        removeNaPosicao(&precedentes, &list, j);
                        limpa_lista(&list);
                        insereNoFim(&list, &min);
                        insereNaPosicao(&precedentes, &list, j);
                    }

                    distancia[j] = distancia[min] + matriz[min][j];
            }
        }
    }

    /*-mostrar resultados-*/
    printf("\n\n    ---------\n");
    printf("    Vertices:     ");
    for(i = 1; i <= qtdVertices; i++)
        printf("%d     ", i);

    printf("\n\n");

    printf("    Estimativas:  ");
    for(i = 0; i < qtdVertices; i ++)
        if(distancia[i] == INFINITO){
            printf("INF   ");
            infinito = 1;
        }
        else{
            if(distancia[i] < 10)
                printf("%d     ", distancia[i]);
            else
                printf("%d    ", distancia[i]); //retira um espaço para alinhar a tabela caso seja > 10
        }

    if(infinito == 1) //caso ocorra um infinito
        printf("\n\n    Obs: a estimativa INF significa que o vertice estimado\n    eh inalcancavel a partir do inicio!");

    printf("\n    ---------");

    printf("\n\n");

    printf("    Precedentes:  ");
    for(i = 0; i < qtdVertices; i++){
        printf("\n    do vertice %d: ", i+1);

        Lista list;
        leNaPosicao(&precedentes, &list, i);
        mostra_lista(list, printInt);
    }

    printf("\n\n");

    system("pause");
    system("cls");

    free(matriz);
    free(distancia);
    free(visitados);
}

int minimo(int *distancia, int *visitados, int qtdVertices){ /*encontra o vertice mais perto*/
    int min = INFINITO;
    int vMin;
    int vertice;

    for(vertice = 0; vertice < qtdVertices; vertice++){
        if(!visitados[vertice] && (distancia[vertice] <= min)){ /*se nao foi visitado e é mais perto*/
            min = distancia[vertice];
            vMin = vertice;
        }
    }
    return vMin;
}

void adjacente(int **matriz, int quantidadeVertices){
	FILE *f = fopen("grafo.txt", "r+");
	int x, y; //campos da matriz
	int peso;

	if(f == NULL)
			printf("Erro ao abrir o arquivo!\n");
	else{
		while((fscanf(f," %d %d %d\n", &x, &peso, &y)) != EOF){     //le uma linha de cada vez
			if(matriz[x-1][y-1] == -1){ /*se ainda nao foi inserido nenhum peso*/
                matriz[x-1][y-1] = peso; /*insere o peso lido*/
			}else{
                if(matriz[x-1][y-1] > peso) /*se ja foi inserido um peso mas ele é maior do que o lido*/
                    matriz[x-1][y-1] = peso; /*insere o peso novo menor*/
			}
		}

        /*
		printf("\n\n****** Matriz de adjacencia ******\n\n");
		for(x = 0; x < quantidadeVertices; x++){
			for(y = 0; y < quantidadeVertices; y++){                    //imprime a matriz
				printf("%d ", matriz[x][y]);
			}
			printf("\n");
		}
		fclose(f);

        printf("\n...................................\n\n");
        */
	}

    //system("pause");
    //system("cls || clear");
}

/*funçao que mostra o elemento da lista como int*/
void printInt(void *i){
    int *n = (int*)i;
    (*n)++;
    printf("%d ", *n);
}




















