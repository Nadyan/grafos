#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define INFINITO 500


void floydWarshall();
void adjacente(int **matriz, int quantidadeVertices);            //funçao para criar a matriz adjacente com peso
int minimo(int a, int b);


int main(){
	int escolha;

	do{
        printf("\n                TEORIA DOS GRAFOS\n");
        printf("\n    1 - Algoritmo de Floyd-Warshall\n");

        printf("    0 - Sair\n\n");

        printf("    Informe a operacao a ser efetuada: ");

		scanf("%d", &escolha);
		system("cls || clear");

		switch(escolha){
			case 1:
				floydWarshall();
				break;
			case 0:
				break;
		}
	}while(escolha != 0);

    return 0;
}

void floydWarshall(){
	int k, i, j; 		//indices
	int qtdVertices;	//quantidade de vertices do grafo
	int **matriz;		//matriz adjacente original com peso
	int ***matrizes;	//vetor de k matrizes


	printf("\n\n    Informe a quantidade de vertices: ");
	scanf("%d", &qtdVertices);

	system("cls");


	/*-alocação e montagem da matriz adjacente com peso-*/
    matriz = malloc(sizeof(int*) * qtdVertices);  //aloca as linhas da matriz
    for(i = 0; i < qtdVertices; i++){
        matriz[i] = malloc(sizeof(int) * qtdVertices);   // aloca as colunas da matriz
        for(j = 0; j < qtdVertices; j++){
            matriz[i][j] = INFINITO;    //inicializa a matriz com pesos INFINITO
        }
    }
    adjacente(matriz, qtdVertices);  //monta a matriz adjacente
    /*-----------------------------------------*/


	/** alocacacao das matrizes em tres niveis **/
	matrizes = (int***)malloc(sizeof(int**) * (qtdVertices+1)); //alocacao do prim. nivel
	for(i = 0; i <= qtdVertices; i++){
		matrizes[i] = (int**)calloc(sizeof(int*), qtdVertices); //alocacao do seg. nivel
	}
	for(i = 0; i <= qtdVertices; i++){
		for(j = 0; j <= qtdVertices; j++){
			matrizes[i][j] = (int*)calloc(sizeof(int), qtdVertices); //alocacao do terc. nivel
		}
	}


	/**inicializacao da primeira matriz com a matriz adj original**/
	for(i = 0; i < qtdVertices; i++){
		for(j = 0; j < qtdVertices; j++){
			matrizes[0][i][j] = matriz[i][j];
		}
	}


	/**criacao das k outras matrizes utilizando a formula
		Dij(k) = min(Dij^(k-1), Dik^(k-1) + Dkj^(k-1))   **/

	for(k = 1; k <= qtdVertices; k++){
		for(i = 0; i < qtdVertices; i++){
			for(j = 0; j < qtdVertices; j++){
				matrizes[k][i][j] = minimo(matrizes[k-1][i][j], matrizes[k-1][i][k-1] + matrizes[k-1][k-1][j]);
			}
		}
	}


	/**Impressao da matriz 0**/
	printf("\n\n    Matriz 0 (ORIGINAL)\n\n");
	for(i = 0; i < qtdVertices; i++){
        printf("    ");
        for(j = 0; j < qtdVertices; j++){
            if(i == j)
                printf("0\t");
            else{
                if(matriz[i][j] >= 150)
                    printf("INF\t");
                else
                    printf("%d\t", matriz[i][j]);
            }
        }
        printf("\n");
	}
	printf("\n\n");
	printf("------------------------------------------\n");

	/**Impressao das matrizes**/
	for(k = 1; k <= qtdVertices; k++){
		printf("\n\n    Matriz %d\n\n", k);
		for(i = 0; i < qtdVertices; i++){
            printf("    ");
			for(j = 0; j < qtdVertices; j++){
				if(i == j)
                    printf("0\t");
                else{
                    if(matrizes[k][i][j] >= 150)
                        printf("INF\t");
                    else
                        printf("%d\t", matrizes[k][i][j]);
                }
			}
			printf("\n");
		}
		printf("\n\n");
		printf("------------------------------------------\n");
	}

	free(matriz);
	free(matrizes);

    printf("\n\n    ");
    system("pause");
    system("cls");
}

int minimo(int a, int b){
    if (a < b){
        return a;
    }else{
        return b;
    }
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

        /* //imprime a matriz
		printf("\n\n****** Matriz de adjacencia ******\n\n");
		for(x = 0; x < quantidadeVertices; x++){
			for(y = 0; y < quantidadeVertices; y++){
				printf("%d ", matriz[x][y]);
			}
			printf("\n");
		}


        printf("\n...................................\n\n");*/
	}

	fclose(f);
}
