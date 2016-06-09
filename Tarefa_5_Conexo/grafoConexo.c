#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


/*
 *  NADYAN S. PSCHEIDT
 *  ANDRE TRAGANCIN
 *
 *  ESTRUTURA TXT:
 *  A representacao do grafo no arquivo txt deve seguir as regras:
 *
 * - ARESTA1 vertice ARESTA2
 * - OS NOMES (VERTICES E ARESTAS) SAO REPRESENTADOS POR NUMEROS
 *
 *  Ex:
 * 	1 1 2
 *  3 2 4   (vertice1 = 3 / vertice 2 = 4 / aresta = 2)
 *  2 3 3
 *
 */

void adjacente(int **matriz, int quantidadeVertices);
void centro();
void dfs(int i, int **matriz, int qtdVert, int *visitados, int *qtdVerticesVisitados); //algortimo de busca em profundidade

int main(){

	int escolha;

	do{
        printf("\n                TEORIA DOS GRAFOS\n");
        printf("\n    1 - Analisar conectividade\n");

        printf("    0 - Sair\n\n");

        printf("    Informe a operacao a ser efetuada: ");

		scanf("%d", &escolha);
		system("cls || clear");

		switch(escolha){
			case 1:
				centro();
				break;
			case 0:
				break;
		}
	}while(escolha != 0);

	return 0;
}

void centro(){

    int i, j, path, maxPath; //comprimento dos caminhos
    int menorCaminhoMax = 200, medianaGrafo = 200, verticeMedio; //menor caminho maximo percorrido por um vertice
    int **matriz;
    int qtdVertices, qtdVerticesVisitados = 0, conexo = 1;

    printf("\n    Informe a quantidade de vertices: ");
    scanf("%d", &qtdVertices);

    int visitados[qtdVertices]; //vetor de vertices visitados

    /****** INICIALIZA VETORES *********/
    memset(visitados, 0, sizeof(visitados));
    /***********************************/

    /*** Aloca matriz adjacente ***/
    matriz = malloc(sizeof(int*) * qtdVertices);  //aloca as linhas da matriz
    for(i = 0; i < qtdVertices; i++){
        matriz[i] = malloc(sizeof(int) * qtdVertices);   // aloca as colunas da matriz
        for(j = 0; j < qtdVertices; j++){
            matriz[i][j] = 0;    //inicializa a matriz com 0
        }
    }
    /******************************/

    adjacente(matriz, qtdVertices);  //monta a matriz adjacente

    for(i = 0; i < qtdVertices; i++){
        //dfs é um algoritmo de busca em profundidade
        dfs(i, matriz, qtdVertices, visitados, &qtdVerticesVisitados);

        if(qtdVerticesVisitados != qtdVertices - 1){ //se encontrar um vertice que nao tem acesso a todos os outros
            conexo = 0;                              //sinaliza que o grafo nao é conexo
        }

        //Zera variaveis para a proxima interação
        memset(visitados, 0, sizeof(visitados));
        qtdVerticesVisitados = 0;
    }

    if(conexo == 0)
        printf("\n    Grafo desconexo!");
    else
        printf("\n    Grafo conexo!");

    printf("\n\n\n    ");

    free(matriz);
    system("pause");
    system("cls || clear");
}

void adjacente(int **matriz, int quantidadeVertices, int *grauNo){
	FILE *f = fopen("grafoDesconexo.txt", "r+");
	int x, y; //campos da matriz
	int aresta;

	if(f == NULL)
			printf("Erro ao abrir o arquivo!\n");
	else{
		while((fscanf(f," %d %d %d\n", &x, &aresta, &y)) != EOF){   //le uma linha de cada vez
			matriz[y-1][x-1]++;                                     //e aumenta o numero de arestas entre cada vertice
		}

		for(x = 0; x < quantidadeVertices; x++){
			for(y = 0; y < quantidadeVertices; y++){
			    if(x > y)
                    matriz[y][x] = matriz[x][y];
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

void dfs(int i, int **matriz, int qtdVert, int *visitados, int *qtdVerticesVisitados){
    int j; //contador

    visitados[i] = 1;

    for(j = 0; j < qtdVert; j++){
        if(!visitados[j] && matriz[i][j] != 0){   //se nao foi visitado e
                                                  //existe ligaçao entre os vertices i e j

            (*qtdVerticesVisitados)++; //incrementa a quantidade de vertices visitados a partir do vertice i

            dfs(j, matriz, qtdVert, visitados, qtdVerticesVisitados);
        }
    }


}

