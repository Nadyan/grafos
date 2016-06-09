
/*
    TEORIA DOS GRAFOS - UDESC

     ALUNOS:
        NADYAN SURIEL PSCHEIDT
        ANDRE TRAGANCIN

    TAREFA 4 - IDENTIFICAR CICLO EULERIANO EM UM GRAFO


    "Grafos que possuem um circuito Euleriano são chamados Grafos Eulerianos.
     Uma das principais condições para um grafo ser Euleriano é que todos os vértices precisam ser de grau par.
     Entretanto, essa condição não é suficiente, pois também é necessário que o grafo seja conexo.

     Euler provou que uma condição necessária para a existência de circuitos eulerianos é de que todos os vértices tenham grau par,
     e afirmou, sem prova de que grafos conexos com todos os vértices pares tem um circuito Euleriano.
     A primeira prova completa desta última afirmação foi publicada em 1873 por Carl Hierholzer.

     Há, ainda, grafos com caminhos Eulerianos se houver 2 vértices de grau ímpar.
     Nesse caso, ao se acrescentar uma aresta ligando estes dois vértices, o novo grafo passa a ser um circuito Euleriano."
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void adjacente(int **matriz, int quantidadeVertices, int *grauNo);
void fleury();
void dfs(int i, int **matriz, int qtdVert, int *visitados, int *qtdVerticesVisitados); //algortimo de busca em profundidade

int main(){

	int escolha;

	do{
        printf("\n                TEORIA DOS GRAFOS\n");
        printf("\n    1 - Verificar existencia de ciclo euleriano\n");

        printf("    0 - Sair\n\n");

        printf("    Informe a operacao a ser efetuada: ");

		scanf("%d", &escolha);
		system("cls || clear");

		switch(escolha){
			case 1:
				fleury();
				break;
			case 0:
				break;
		}
	}while(escolha != 0);

	return 0;
}

void fleury(){

    int i, j, path, maxPath; //comprimento dos caminhos
    int menorCaminhoMax = 200, medianaGrafo = 200, verticeMedio; //menor caminho maximo percorrido por um vertice
    int **matriz;
    int qtdVertices, qtdVerticesVisitados = 0, conexo = 1, grauImpar = 0, excecao = 1;
    int primeiroImpar, segundoImpar;

    printf("\n    Informe a quantidade de vertices: ");
    scanf("%d", &qtdVertices);

    system("cls || clear");

    int visitados[qtdVertices]; //vetor de vertices visitados
    int grauNo[qtdVertices]; //vetor com o grau de cada nó

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

    adjacente(matriz, qtdVertices, grauNo);  //monta a matriz adjacente

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

    //verificaçao de todos os graus
    for(i = 0; i < qtdVertices; i++){
            if(grauNo[i] % 2 != 0){ //se o grau for impar
                grauImpar++; //sinaliza que encontrou um no com grau impar

            if(grauImpar % 2 != 0){
                primeiroImpar = i; //armazena o primeiro no com grau impar
                excecao = 0;
            }

            if(grauImpar % 2 == 0){ //se encontrou uma dupla de nos com grau par
                segundoImpar = i;  //armazena o segundo no com grau impar
                //if(matriz[primeiroImpar][segundoImpar] != 0 && (grauNo[primeiroImpar] % 2 != 0) && (grauNo[segundoImpar] % 2 != 0))
                if(matriz[primeiroImpar][segundoImpar] != 0){ //se os dois nos com grau impar possuem ligaçao

                    matriz[primeiroImpar][segundoImpar]--;//retira essa aresta, para verificar se a aresta é uma ponte (verificando se o grafo continua sendo conexo)

                    /******irá verificar se o grafo continua sendo conexo: ********/

                    memset(visitados, 0, sizeof(visitados));
                    qtdVerticesVisitados = 0;

                    for(i = 0; i < qtdVertices; i++){

                        dfs(i, matriz, qtdVertices, visitados, &qtdVerticesVisitados);

                        if(qtdVerticesVisitados != qtdVertices - 1){ //se encontrar um vertice que nao tem acesso a todos os outros
                            conexo = 0;                              //sinaliza que o grafo nao é conexo
                        }

                        //Zera variaveis para a proxima interação
                        memset(visitados, 0, sizeof(visitados));
                        qtdVerticesVisitados = 0;
                    }

                    matriz[primeiroImpar][segundoImpar]++; //restaura a aresta que foi testada

                    /***************************************************************/

                    if(conexo == 1){ //se nao for uma aresta ponte
                        excecao = 1;  //sinaliza que eles tem ligaçao e nao formam ponte, entao está apto a ter ciclo euleriano
                        grauImpar = 0; //reinicia grauImpar para caso tenha mais uma dupla de vertices vizinhos com grau impar
                    }else{//se for uma aresta ponte
                        printf("\n\n    O grafo possui uma ponte entre os vertices %d e %d!", primeiroImpar+1, segundoImpar+1);
                        printf("\n\n    O grafo NAO POSSUI um ciclo Euleriano!\n\n    ");
                        system("pause");
                        exit(1);
                    }
                }
            }
        }
    }


    /******* irá mostrar se encontrou erros, se sim, quais ***************************************************************************/
    if(conexo == 0) //se nao for conexo
        printf("\n\n    Requisito de ser um grafo conexo INSATISFEITO!");
    else
        printf("\n\n    Requisito de ser um grafo conexo SATISFEITO!");


    if(grauImpar % 2 == 0 && excecao){ //se nao tiver vertice com grau impar, ou se tiver dois nos com grau impar porém vizinhos e nao ponte
        printf("\n\n    Requisito de grau de vertices SATISFEITO!");
    }else
        printf("\n\n    Requisito de graus INSATISFEITO, vertice %d possui grau impar = %d!", primeiroImpar+1, grauNo[primeiroImpar]);

    /*********************************************************************************************************************************/

    /** resposta final **/
    if(conexo && excecao) //se for conexo e todos os nos tem grau par com exceção de pares de vizinhos com grau impar que nao formam ponte
        printf("\n\n\n    O grafo POSSUI um ciclo Euleriano!");
    else
        printf("\n\n\n    O grafo NAO POSSUI um ciclo Euleriano!");

    printf("\n\n\n\n    ");

    free(matriz);
    system("pause");
    system("cls || clear");
}

void adjacente(int **matriz, int quantidadeVertices, int *grauNo){
	FILE *f = fopen("grafoNaoEulerianoCritico.txt", "r+");
	int x, y; //campos da matriz
	char aresta;

	if(f == NULL)
			printf("Erro ao abrir o arquivo!\n");
	else{
		while((fscanf(f," %d %c %d\n", &x, &aresta, &y)) != EOF){   //le uma linha de cada vez
			matriz[y-1][x-1]++;                                     //e aumenta o numero de arestas entre cada vertice
		}

		for(x = 0; x < quantidadeVertices; x++){
			for(y = 0; y < quantidadeVertices; y++){
			    if(x > y)
                    matriz[y][x] = matriz[x][y];
			}
		}

        for(x = 0; x < quantidadeVertices; x++){
                grauNo[x] = 0;
                for(y = 0; y < quantidadeVertices; y++){
                    grauNo[x] += matriz[y][x];
                }
                //printf("    Grau do no %d: %d\n", x+1, grauNo[x]);
        }
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


