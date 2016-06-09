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
void dfs(int i, int **matriz, int qtdVert, int *visitados, int *path, int *maxPath, int *mediana); //algortimo de busca em profundidade

int main(){

	int escolha;

	do{
        printf("\n                TEORIA DOS GRAFOS\n");
        printf("\n    1 - Calcular centro do grafo\n");

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
    int qtdVertices;

    printf("\n    Informe a quantidade de vertices: ");
    scanf("%d", &qtdVertices);

    int caminhosMaximos[qtdVertices]; //caminhos maximos de cada vertice
    int visitados[qtdVertices];
    int mediana[qtdVertices];

    /****** INICIALIZA VARIAVEIS *******/
    memset(caminhosMaximos, 0, sizeof(caminhosMaximos));
    memset(visitados, 0, sizeof(visitados));
    memset(mediana, 0, sizeof(mediana));
    path = 0;
    maxPath = 0;
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
        //dfs é um algoritmo que percorre grafos
        dfs(i, matriz, qtdVertices, visitados, &path, &maxPath, mediana);

        caminhosMaximos[i] = maxPath; //o vetor recebe o caminho maximo do vertice i

        //comparaçao para saber qual a menor excentricidade do grafo
        if(maxPath < menorCaminhoMax)
            menorCaminhoMax = maxPath;

        //Zera as variaveis para a proxima interação
        path = 0;
        maxPath = 0;
        memset(visitados, 0, sizeof(visitados));
    }

    for(i = 0; i < qtdVertices; i++){
        if(mediana[i] < medianaGrafo){ //encontra o vertice com a menor mediana que sera a mediana do grafo
            medianaGrafo = mediana[i];
            verticeMedio = i;
        }
    }

    printf("\n\n    Vertice    |    Excentricidade    |    Mediana    \n\n");

    for(i = 0; i < qtdVertices; i++){
        if(i+1 < 10)
            printf("       %d       |          %d           |      %d       \n", i+1, caminhosMaximos[i], mediana[i]);
        else
            printf("       %d      |          %d           |      %d       \n", i+1, caminhosMaximos[i], mediana[i]);
    }


    printf("\n\n    Vertice(s) central(is):");
    for(i = 0; i < qtdVertices; i++){
        if(caminhosMaximos[i] == menorCaminhoMax)
            printf(" %d", i+1);
    }

    printf("\n\n    Excentricidade do grafo: %d", menorCaminhoMax);

    printf("\n\n    Vertice medio do grafo: %d", verticeMedio+1);

    printf("\n\n\n    ");

    free(matriz);
    system("pause");
    system("cls || clear");
}

void adjacente(int **matriz, int quantidadeVertices){
	FILE *f = fopen("grafoND2.txt", "r+");
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

void dfs(int i, int **matriz, int qtdVert, int *visitados, int *path, int *maxPath, int *mediana){
    int j; //contador

    visitados[i] = 1;

    for(j = 0; j < qtdVert; j++){
        if(!visitados[j] && matriz[i][j] != 0){   //se nao foi visitado e
                                                  //existe ligaçao entre os vertices i e j

            //path fará a contagem das arestas dos vertices alcançáveis a partir de i
            (*path)++;

            dfs(j, matriz, qtdVert, visitados, path, maxPath, mediana);
        }

    }

    mediana[i] += *path;

    //compara para garantir que o vertice fique com a excentricidade maior
    if((*path) > (*maxPath)){
        *maxPath = *path;
    }

    (*path)--; //diminiu path por ser um nó folha
}

