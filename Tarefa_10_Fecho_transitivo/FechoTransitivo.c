#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void dfs(int i, int **matriz, int qtdVert, int *visitados);
void adjacente(int **matriz, int quantidadeVertices); //funçao para criar a matriz adjacente
void busca();

int main(){
	int escolha;

	do{
        printf("\n                TEORIA DOS GRAFOS\n");
        printf("\n    1 - Analisar Fecho Transitivo\n");

        printf("    0 - Sair\n\n");

        printf("    Informe a operacao a ser efetuada: ");

		scanf("%d", &escolha);
		system("cls || clear");

		switch(escolha){
			case 1:
				busca();
				break;
			case 0:
				break;
		}
	}while(escolha != 0);

    return 0;
}

void busca(){
    int **matriz;
    int qtdNos, i, j, inicio, fti;

    printf("\n    Informe a quantidade de vertices: ");
    scanf("%d", &qtdNos);

    int visitados[qtdNos];
    memset(visitados, 0, sizeof(visitados)); /*inicia o vetor com 0*/

    /*-alocação e montagem da matriz adjacente-*/
    matriz = malloc(sizeof(int*) * qtdNos);  //aloca as linhas da matriz
    for(i = 0; i < qtdNos; i++){
        matriz[i] = malloc(sizeof(int) * qtdNos);   // aloca as colunas da matriz
        for(j = 0; j < qtdNos; j++){
            matriz[i][j] = 0;    //inicializa a matriz com 0
        }
    }
    adjacente(matriz, qtdNos);  //monta a matriz adjacente
    /*-----------------------------------------*/

    /* FECHO TRANSITIVO DIRETO */
    for(i = 0; i < qtdNos; i++){
        printf("\n    FTD do vertice %d:   ", i+1);

        /*chama DFS com o inicio*/
        dfs(i, matriz, qtdNos, visitados);

        memset(visitados, 0, sizeof(visitados)); //zera visitados

        printf("\n");
    }

    /* FECHO TRANSITIVO INDIRETO */
    /*        FTI AQUI!          */
    /*                           */

    printf("\n\n\n    ");

    system("pause");
    system("cls");

    free(matriz);
}

void dfs(int i, int **matriz, int qtdVert, int *visitados){
    int j; //contador

    visitados[i] = 1;

    for(j = 0; j < qtdVert; j++){
        if(!visitados[j] && matriz[i][j] != 0){   //se nao foi visitado e
                                                  //existe ligaçao entre os vertices i e j

            printf("%d  ", j+1);  //imprime j e executa a recursão

            dfs(j, matriz, qtdVert, visitados);
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
		while((fscanf(f," %d %d %d\n", &x, &peso, &y)) != EOF){   //le uma linha de cada vez
			matriz[y-1][x-1]++;                                   //e aumenta o numero de arestas entre cada vertice
		}
	}

}
