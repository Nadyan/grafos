#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void kruskal();
void adjacente(int **matriz, int quantidadeVertices);
int dfs(int i, int **matrizDFS, int qtdVert, int *visitados);

int flagCiclo = 0;
int inicioDFS;


int main(){
	int escolha;

	do{
        printf("\n                TEORIA DOS GRAFOS\n");
        printf("\n    1 - Algoritmo de Kruskal\n");

        printf("    0 - Sair\n\n");

        printf("    Informe a operacao a ser efetuada: ");

		scanf("%d", &escolha);
		system("cls || clear");

		switch(escolha){
			case 1:
			    system("cls");
				kruskal();
				break;
			case 0:
				break;
		}
	}while(escolha != 0);

    return 0;
}

void kruskal(){
    int *visitados;
    int **matriz, **matrizDFS;
    int qtdVertices, i, j, pesoAresta, qtdArestasAdd;
    int ciclo = 0;

    printf("\n    Informe a quantidade de vertices: ");
    scanf("%d", &qtdVertices);
    system("cls");

    /*-alocação e montagem da matriz adjacente com peso-*/
    matriz = malloc(sizeof(int*) * qtdVertices);  //aloca as linhas da matriz
    matrizDFS = malloc(sizeof(int*) * qtdVertices);
    for(i = 0; i < qtdVertices; i++){
        matriz[i] = malloc(sizeof(int) * qtdVertices);   // aloca as colunas da matriz
        matrizDFS[i] = malloc(sizeof(int*) * qtdVertices);
        for(j = 0; j < qtdVertices; j++){
            matriz[i][j] = -1;    //inicializa a matriz com pesos -1
            matrizDFS[i][j] = 0;
        }
    }
    adjacente(matriz, qtdVertices);  //monta a matriz adjacente
    /*-----------------------------------------*/
    //alocacao do vetor de vertices visitados
    visitados = malloc(sizeof(int*) * qtdVertices);
    memset(visitados, 0, sizeof(visitados)); //inicializa visitados com 0


    pesoAresta = 1; //peso aresta verifica as arestas com determinado peso
    qtdArestasAdd = 0;

    printf("\n\n\n     V1\t\tPeso\t\tV2\n\n");

    while(qtdArestasAdd < qtdVertices-1){ //pára quando a quantidade de arestas for qtdVertices-1
        //ira percorrer a matriz inteira procurando uma aresta do peso menor da vez:
        for(i = 0; i < qtdVertices; i++){
            for(j = 0; j < qtdVertices; j++){
                if(matriz[i][j] == pesoAresta && (qtdArestasAdd < (qtdVertices-1))){ //se a aresta tiver o menor peso da vez
                    //verificar se forma ciclo, se formar, nao adiciona a aresta na arvore geradora
                    matrizDFS[i][j] = 1; //adiciona a aresta na matriz para testar com o DFS se a adicao da aresta causara um ciclo
                    matrizDFS[j][i] = 1; //espelhada para o DFS

                    inicioDFS = i;
                    //dfs(inicioDFS, matrizDFS, qtdVertices, visitados); //DFS que irá verificar a existencia de ciclos na arvore geradora
                    memset(visitados, 0, sizeof(visitados)); //inicializa visitados com 0

                    //se nao formar, printa a aresta e incrementa qtdArestasAdd
                    if(flagCiclo == 0){ //se o DFS nao achou ciclo
                        printf("\n     %d\t\t%d\t\t%d\n", i+1, matriz[i][j], j+1);
                        qtdArestasAdd++;
                    }else{ //se formar um ciclo, ignora a aresta e retira ela da matrizDFS
                        matrizDFS[i][j] = 0;
                        matrizDFS[j][i] = 0;
                        flagCiclo = 0;
                        //printf("\nCICLO EM %d %d", i+1, j+1);
                    }
                }
            }
        }
        pesoAresta++;
    }

    printf("\n\n\n    ");
    system("pause");
    system("cls || clear");

    free(matriz);
    free(visitados);
}

int dfs(int i, int **matrizDFS, int qtdVert, int *visitados){
    int j; //contador

    visitados[i]++;

    for(j = 0; j < qtdVert; j++){
        if(visitados[j] <= 2 && matrizDFS[i][j] != 0){   //se nao foi visitado e existe ligaçao entre os vertices i e j

                if(i == inicioDFS && visitados[i] == 2){ //se encontrar o inicio e nao é na primeira vez que ele esta sendo visitado
                    printf("CICLO ENCONTRADO!"); //esse if ta errado, mas nao sei por que!
                    flagCiclo = 1;
                }

                dfs(j, matrizDFS, qtdVert, visitados);


        }
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
