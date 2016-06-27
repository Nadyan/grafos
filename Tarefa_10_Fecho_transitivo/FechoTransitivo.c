#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void dfsFTD(int i, int **matrizFTD, int qtdVert, int *visitados);
void dfsFTI(int i, int **matrizFTI, int qtdVert, int *visitados);
void adjacente(int **matrizFTD, int **matrizFTI, int quantidadeVertices); //funçao para criar a matriz adjacente
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
    int **matrizFTD, **matrizFTI;
    int qtdNos, i, j, inicio, fti;

    printf("\n    Informe a quantidade de vertices: ");
    scanf("%d", &qtdNos);

    int visitados[qtdNos];
    memset(visitados, 0, sizeof(visitados)); /*inicia o vetor com 0*/

    /*-alocação e montagem da matriz adjacente-*/
    matrizFTD = malloc(sizeof(int*) * qtdNos);  //aloca as linhas da matriz
    matrizFTI = malloc(sizeof(int*) * qtdNos);
    for(i = 0; i < qtdNos; i++){
        matrizFTD[i] = malloc(sizeof(int) * qtdNos);   // aloca as colunas da matriz
        matrizFTI[i] = malloc(sizeof(int*) * qtdNos);
        for(j = 0; j < qtdNos; j++){
            matrizFTD[i][j] = 0;    //inicializa a matriz com 0
            matrizFTI[i][j] = 0;
        }
    }
    adjacente(matrizFTD, matrizFTI, qtdNos);  //monta a matriz adjacente
    /*-----------------------------------------*/

    /* FECHO TRANSITIVO DIRETO */
    for(i = 0; i < qtdNos; i++){
        printf("\n    FTD do vertice %d:   ", i+1);

        /*chama DFS com o inicio*/
        dfsFTD(i, matrizFTD, qtdNos, visitados);

        memset(visitados, 0, sizeof(visitados)); //zera visitados

        printf("\n");
    }

    printf("\n");

    /* FECHO TRANSITIVO INDIRETO */
    for(i = 0; i < qtdNos; i++){
        printf("\n    FTI do vertice %d:   ", i+1);

        /*chama DFS com o inicio*/
        dfsFTI(i, matrizFTI, qtdNos, visitados);

        memset(visitados, 0, sizeof(visitados)); //zera visitados

        printf("\n");
    }

    printf("\n\n\n    ");

    system("pause");
    system("cls");

    free(matrizFTD);
    free(matrizFTI);
}

void dfsFTD(int i, int **matrizFTD, int qtdVert, int *visitados){
    int j; //contador

    visitados[i] = 1;

    for(j = 0; j < qtdVert; j++){
        if(!visitados[j] && matrizFTD[i][j] != 0){   //se nao foi visitado e
                                                  //existe ligaçao entre os vertices i e j

            printf("%d  ", j+1);  //imprime j e executa a recursão

            dfsFTD(j, matrizFTD, qtdVert, visitados);
        }
    }
}

void dfsFTI(int i, int **matrizFTI, int qtdVert, int *visitados){
    int j; //contador

    visitados[i] = 1;

    for(j = 0; j < qtdVert; j++){
        if(!visitados[j] && matrizFTI[i][j] != 0){   //se nao foi visitado e
                                                  //existe ligaçao entre os vertices i e j

            printf("%d  ", j+1);  //imprime j e executa a recursão

            dfsFTI(j, matrizFTI, qtdVert, visitados);
        }
    }
}

void adjacente(int **matrizFTD, int **matrizFTI, int quantidadeVertices){
	FILE *f = fopen("grafo2.txt", "r+");
	int x, y; //campos da matriz
	int peso;

	if(f == NULL)
			printf("Erro ao abrir o arquivo!\n");
	else{
		while((fscanf(f," %d %d %d\n", &x, &peso, &y)) != EOF){   //le uma linha de cada vez
			matrizFTD[x-1][y-1]++;
			matrizFTI[y-1][x-1]++;                                  //e aumenta o numero de arestas entre cada vertice
		}
	}
}
