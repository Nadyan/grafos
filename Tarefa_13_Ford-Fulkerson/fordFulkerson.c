#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define INFINITO 999


void fordFulkerson();
void adjacente(int **matriz, int quantidadeVertices);                                				    //funçao para criar a matriz adjacente com peso
int dfs(int i, int **matriz, int qtdVert, int *visitados, int vertPai, int vertFinal, int *pai);		//busca em profundidade
int minimo(int a, int b);


int main(){
	int escolha;

	do{
        printf("\n                TEORIA DOS GRAFOS\n");
        printf("\n    1 - Algoritmo de Ford-Fulkerson\n");

        printf("    0 - Sair\n\n");

        printf("    Informe a operacao a ser efetuada: ");

		scanf("%d", &escolha);
		system("cls || clear");

		switch(escolha){
			case 1:
				fordFulkerson();
				break;
			case 0:
				break;
		}
	}while(escolha != 0);

    return 0;
}

void fordFulkerson(){
	int i, j, k;			//contadores
	int source, sink;		//vertices de origem e destino
	int qtdVertices;		//quantidade de vertices no grafo
	int **matriz;			//matriz adjacente com peso
	int fluxoMaximo = 0;	//fluxo maximo do grafo
	int *visitados;			//vetor de vertices que ja foram visitados
	int *pai;


	printf("\n\n    Informe a quantidade de vertices: ");
	scanf("%d", &qtdVertices);

	printf("\n    Informe o vertice inicial: ");
	scanf("%d", &source);
	source--; 	//a matriz comeca em 0 enquanto o grafo em 1
	printf("\n    Informe o vertice final: ");
	scanf("%d", &sink);
	sink--; 	//a matriz comeca em 0 enquanto o grafo em 1

	system("cls");


	/*-alocação e montagem da matriz adjacente com peso-*/
    matriz = malloc(sizeof(int*) * qtdVertices);  //aloca as linhas da matriz
    for(i = 0; i < qtdVertices; i++){
        matriz[i] = malloc(sizeof(int) * qtdVertices);   // aloca as colunas da matriz
        for(j = 0; j < qtdVertices; j++){
            matriz[i][j] = 0;    //inicializa a matriz
        }
    }
    adjacente(matriz, qtdVertices);  //monta a matriz adjacente
	visitados = (int *)calloc(qtdVertices, sizeof(int));
	pai = (int *)calloc(qtdVertices, sizeof(int));
    /*-----------------------------------------*/


	//Inicio das interacoes
	//Enquanto existir fluxo possivel entre o vertice inicial e final
	//caminho 'e procurado pelo DFS
	while(dfs(source, matriz, qtdVertices, visitados, 0, sink, pai)){
		int fluxoLocal = INFINITO;
		int x, y;

		//caminho contrario para buscar o menor fluxo maximo
		for(x = sink; x != source; x = pai[x]){
			y = pai[x];
			fluxoLocal = minimo(fluxoLocal, matriz[y][x]);
		}

		//atualiza matriz com o fluxo encontrado
		for(x = sink; x != source; x = pai[x]){
			y = pai[x];
			matriz[y][x] -= fluxoLocal;
			matriz[x][y] += fluxoLocal;
		}

		fluxoMaximo += fluxoLocal;

		memset(visitados, 0, sizeof(int)*qtdVertices);
        memset(pai, 0, sizeof(int)*qtdVertices);
	}


	//impressao dos resultados:
	printf("\n\n    Matriz adjacente da Rede Residual:\n\n");
	for(i = 0; i < qtdVertices; i++){
        printf("    ");
		for(j = 0; j < qtdVertices; j++){
			printf("\t%d", matriz[i][j]);
		}
		printf("\n");
	}

	printf("\n\n    Fluxo maximo: %d", fluxoMaximo);
	printf("\n\n\n    ");

	system("pause");
	system("cls");


	free(matriz);
	free(visitados);
	free(pai);
}

//DFS alem de encontrar o caminho, vai preencher o vetor "pai", armazenando o caminho feito
int dfs(int i, int **matriz, int qtdVert, int *visitados, int vertPai, int vertFinal, int *pai){
    int j; //contador

    visitados[i] = 1;
	pai[i] = vertPai;

    for(j = 0; j < qtdVert; j++){
        if(!visitados[j] && matriz[i][j] > 0){   //se nao foi visitado e
                                                  //existe ligaçao entre os vertices i e j

            dfs(j, matriz, qtdVert, visitados, i, vertFinal, pai);
        }
    }

	//se visitados[sink] == 1 'e porque conseguiu encontrar caminho
	return visitados[vertFinal];
}

int minimo(int a, int b){
    if (a < b){
        return a;
	}else{
		return b;
	}
}

void adjacente(int **matriz, int quantidadeVertices){
	FILE *f = fopen("grafo2.txt", "r+");
	int x, y; //campos da matriz
	int peso;

	if(f == NULL)
			printf("Erro ao abrir o arquivo!\n");
	else{
		while((fscanf(f," %d %d %d\n", &x, &peso, &y)) != EOF){     //le uma linha de cada vez
			if(matriz[x-1][y-1] == 0){ /*se ainda nao foi inserido nenhum peso*/
                matriz[x-1][y-1] = peso; /*insere o peso lido*/
			}else{
                if(matriz[x-1][y-1] > peso) /*se ja foi inserido um peso mas ele é maior do que o lido*/
                    matriz[x-1][y-1] = peso; /*insere o peso novo menor*/
			}
		}

        /* //imprime a matriz
		printf("\n\n****** Matriz inicial ******\n\n");
		for(x = 0; x < quantidadeVertices; x++){
			for(y = 0; y < quantidadeVertices; y++){
				printf("%d ", matriz[x][y]);
			}
			printf("\n");
		}
		fclose(f);

        printf("\n...................................\n\n");
        */
	}
}
