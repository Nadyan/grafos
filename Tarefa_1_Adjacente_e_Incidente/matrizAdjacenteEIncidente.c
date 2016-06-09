#include <stdio.h>
#include <stdlib.h>

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

typedef struct Vertice{
    int noSaida;
    int noChegada;
    int aresta;
}Vertice;

void adjacente();
void adjacenteDirecionado();
void incidencia();
void incidenciaDirecionado();
void adicionarDirecionado();
void adicionarNaoDirecionado();

int main(){

	int escolha;

	do{
        printf("\n                TEORIA DOS GRAFOS\n");
        printf("\n                NAO DIRECIONADOS\n");
        printf(" ------------------------------------------\n\n");
        printf("    1 - Calcular a matriz adjacente, grau de cada no e complemento\n");
        printf("    2 - Calcular a matriz de incidencia\n");
        printf("    3 - Adicionar vertice(s)\n");
        printf("\n\n                 DIRECIONADOS\n");
        printf(" ------------------------------------------\n\n");
        printf("    4 - Calcular a matriz adjacente, grau de cada no e complemento\n");
        printf("    5 - Calcular a matriz de incidencia\n\n");
        printf("    6 - Adicionar vertice(s)\n");

        printf("___________________________________________\n\n");

        printf("    0 - Sair\n\n");

        printf("    Informe a operacao a ser efetuada: ");

		scanf("%d", &escolha);
		system("cls || clear");
		switch(escolha){
			case 1:
				adjacente();
				break;
			case 2:
				incidencia();
				break;
			case 3:
                adicionarNaoDirecionado();
                break;
			case 4:
                adjacenteDirecionado();
                break;
            case 5:
                incidenciaDirecionado();
                break;
            case 6:
                adicionarDirecionado();
                break;
			case 0:
				break;
		}
	}while(escolha != 0);

	return 0;
}

void adjacente(){
	FILE *f = fopen("grafoND.txt", "r+");
	int i, j; //campos da matriz
    int qtdVertices;
	int aresta;
    int **matriz, **matrizComplementar; // declara a matriz de acordo com aquantidade de vertices
    int *grauNo;

	if(f == NULL)
			printf("Erro ao abrir o arquivo!\n");
	else{
		printf("\n    Informe a quantidade de vertices: ");
		scanf("%d", &qtdVertices);
		//fscanf(f, "%d \n", &qtdVertices);


        matriz= malloc(sizeof(int*)* qtdVertices);  //aloca as linhas da matriz
        matrizComplementar = malloc(sizeof(int*) * qtdVertices);
        grauNo= malloc(sizeof(int)*qtdVertices);    // aloca o vertice

		for(i = 0; i < qtdVertices; i++){
          matriz[i]= malloc(sizeof(int)*qtdVertices);   // aloca as colunas da matriz
          matrizComplementar[i] = malloc(sizeof(int) * qtdVertices);
			for(j = 0; j < qtdVertices; j++){ //inicializa a matriz com 0
				matriz[i][j] = 0;
				matrizComplementar[i][j] = 0;
			}
		}

		while((fscanf(f," %d %d %d\n", &i, &aresta, &j)) != EOF){   //le uma linha de cada vez
			matriz[j-1][i-1]++;                                    //e aumenta o numero de arestas entre cada vertice
		}

		for(i = 0; i < qtdVertices; i++){
			for(j = 0; j < qtdVertices; j++){
			    if(i > j)
                    matriz[j][i] = matriz[i][j];
			}
		}

		printf("\n\n****** Matriz de adjacencia ******\n\n");
		for(i = 0; i < qtdVertices; i++){
			for(j = 0; j < qtdVertices; j++){                    //imprime a matriz
				printf("%d ", matriz[i][j]);
			}
			printf("\n");
		}

        printf("\n...................................\n\n");
        for(i = 0; i < qtdVertices; i++){
                grauNo[i] = 0;
                for(j = 0; j < qtdVertices; j++){
                    grauNo[i] += matriz[j][i];
                }
                printf("    Grau do no %d: %d\n", i+1, grauNo[i]);
            }
        printf("\n....................................\n\n");

        /* Complemento do grafo: */
        for(i = 0; i < qtdVertices; i++){
            for(j = 0; j < qtdVertices; j++){
                if(matriz[i][j] == 0)
                    matrizComplementar[i][j] = 1;
                else if(matriz[i][j] == 1)
                    matrizComplementar[i][j] = 0;
            }
        }

        printf("****** Matriz de adjacencia complementar do grafo ****** \n\n");
        for(i = 0; i < qtdVertices; i++){
            for(j = 0; j < qtdVertices; j++){
                    printf("%d ", matrizComplementar[i][j]);
            }
            printf("\n");
        }
        printf("\n\n");
        /*************************/
	}

	free(matriz);
	free(matrizComplementar);
	fclose(f);
    system("pause");
    system("cls || clear");
}

void adjacenteDirecionado(){
	FILE *f = fopen("grafoD.txt", "r+");
	int i, j; //campos da matriz
    int qtdVertices;
	char aresta[3];
    int **matriz, **matrizComplementar; // declara a matriz de acordo com aquantidade de vertices
    int *grauNo;

	if(f == NULL)
			printf("Erro ao abrir o arquivo!\n");
	else{
		printf("\n    Informe a quantidade de vertices: ");
		scanf("%d", &qtdVertices);
		//fscanf(f, "%d \n", &qtdVertices);

        matriz= malloc(sizeof(int*)* qtdVertices);  //aloca as linhas da matriz
        matrizComplementar = malloc(sizeof(int*) * qtdVertices);
        grauNo= malloc(sizeof(int)*qtdVertices);    // aloca o vertice

		for(i = 0; i < qtdVertices; i++){
          matriz[i]= malloc(sizeof(int)*qtdVertices);   // aloca as colunas da matriz
          matrizComplementar[i] = malloc(sizeof(int) * qtdVertices);
			for(j = 0; j < qtdVertices; j++){ //inicializa a matriz com 0
				matriz[i][j] = 0;
				matrizComplementar[i][j] = 0;
			}
		}

		while((fscanf(f," %d %s %d\n", &i, aresta, &j)) != EOF){   //le uma linha de cada vez
			matriz[i-1][j-1]++;                                    //e aumenta o numero de arestas entre cada vertice
		}


		printf("\n\n****** Matriz de adjacencia Direcionada ******\n\n");
		for(i = 0; i < qtdVertices; i++){
			for(j = 0; j < qtdVertices; j++){                    //imprime a matriz
				printf("%d ", matriz[i][j]);
			}
			printf("\n");
		}

        printf("\n...................................\n\n");
        for(i = 0; i < qtdVertices; i++){
                grauNo[i] = 0;
                if(matriz[i][i]==1){
                      grauNo[i]++;
                    }
                for(j = 0; j < qtdVertices; j++){
                    //grauNo[i] += matriz[j][i];
                    if(matriz[i][j]==1){
                       grauNo[i]++;
                    }
                    if(matriz[j][i]==1 && i!=j){
                       grauNo[i]++;
                    }
                }
                printf("    Grau do no %d: %d\n", i+1, grauNo[i]);
            }
        printf("\n....................................\n\n");

        /* Complemento do grafo: */
        for(i = 0; i < qtdVertices; i++){
            for(j = 0; j < qtdVertices; j++){
                if(matriz[i][j] == 0)
                    matrizComplementar[i][j] = 1;
                else if(matriz[i][j] == 1)
                    matrizComplementar[i][j] = 0;
            }
        }

        printf("****** Matriz de adjacencia complementar do grafo ****** \n\n");
        for(i = 0; i < qtdVertices; i++){
            for(j = 0; j < qtdVertices; j++){
                    printf("%d ", matrizComplementar[i][j]);
            }
            printf("\n");
        }
        printf("\n\n");
        /*************************/
	}

	free(matriz);
	free(matrizComplementar);
	fclose(f);
    system("pause");
    system("cls || clear");
}



void incidencia(){
	FILE *f = fopen("grafoND.txt", "r+");
	int i, j; //campos da matriz
    int qtdVertices, qtdArestas;
	int aresta;
	int **matriz; // declara a matriz de acordo com aquantidade de vertices
    int *grauNo;

	if(f == NULL)
			printf("Erro ao abrir o arquivo!\n");
	else{
		printf("\n    Informe a quantidade de vertices: ");
		scanf("%d", &qtdVertices);
		//fscanf(f, "%d \n", &qtdVertices);
		printf("\n    Informe a quantidade de arestas: ");
		scanf("%d", &qtdArestas);

         matriz= malloc(sizeof(int*)*qtdArestas);
         grauNo= malloc(sizeof(int)* qtdVertices);

		for(i = 0; i < qtdArestas; i++){
          matriz[i]= malloc(sizeof(int)* qtdVertices);
			for(j = 0; j < qtdVertices; j++){ //inicializa a matriz com 0
				matriz[i][j] = 0;
			}
		}

		while((fscanf(f," %d %d %d\n", &i, &aresta, &j)) != EOF){
			matriz[aresta-1][i-1]++;  //primeira leitura, vertice aresta
			matriz[aresta-1][j-1]++;  //segunda leitura, aresta vertice
		}

		system("cls || clear");
		printf("\n\n****** Matriz de incidencia ******\n\n");
		for(i = 0; i < qtdArestas; i++){
			for(j = 0; j < qtdVertices; j++){ //imprime a matriz
				printf("%d ", matriz[i][j]);
			}
			printf("\n");
		}
		fclose(f);
	}
	printf("\n...................................\n\n");

            for(i = 0; i < qtdVertices; i++){
                grauNo[i] = 0;
                /*if(matriz[i][i]==1 || matriz[i][i]==-1){
                      grauNo[i]++;
                    }*/
                for(j = 0; j < qtdVertices; j++){
                    //grauNo[i] += matriz[j][i];
                    if(matriz[j][i]==1 || matriz[j][i]==-1 ){
                       grauNo[i]++;
                    }
                }
                printf("    Grau do no %d: %d\n", i+1, grauNo[i]);
            }
        printf("\n....................................\n\n");


    system("pause");
    system("cls || clear");
}

void incidenciaDirecionado(){
	FILE *f = fopen("grafoD.txt", "r+");
	int i, j; //campos da matriz
    int qtdVertices, qtdArestas;
	int aresta;
	int **matriz; // declara a matriz de acordo com aquantidade de vertices
    int *grauNo;

	if(f == NULL)
			printf("Erro ao abrir o arquivo!\n");
	else{
		printf("\n    Informe a quantidade de vertices: ");
		scanf("%d", &qtdVertices);
		//fscanf(f, "%d \n", &qtdVertices);
		printf("\n    Informe a quantidade de arestas: ");
		scanf("%d", &qtdArestas);

        matriz= malloc(sizeof(int*)*qtdArestas);
        grauNo= malloc(sizeof(int)* qtdVertices);

		for(i = 0; i < qtdArestas; i++){
          matriz[i]= malloc(sizeof(int)* qtdVertices);
			for(j = 0; j < qtdVertices; j++){ //inicializa a matriz com 0
				matriz[i][j] = 0;
			}
		}

		while((fscanf(f," %d %d %d\n", &i, &aresta, &j)) != EOF){
			matriz[aresta-1][i-1]++;  //primeira leitura, vertice aresta
			matriz[aresta-1][j-1]--;  //segunda leitura, aresta vertice
		}

		system("cls || clear");
		printf("\n\n****** Matriz de incidencia Direcionada ******\n\n");
		for(i = 0; i < qtdArestas; i++){
			for(j = 0; j < qtdVertices; j++){ //imprime a matriz
                    printf(" %d", matriz[i][j]);
			}
			printf("\n");
		}
		fclose(f);
	}
	printf("\n...................................\n\n");
     for(i = 0; i < qtdVertices; i++){
                grauNo[i] = 0;
                /*if(matriz[i][i]==1 || matriz[i][i]==-1){
                      grauNo[i]++;
                    }*/
                for(j = 0; j < qtdVertices; j++){
                    //grauNo[i] += matriz[j][i];
                    if(matriz[j][i]==1 || matriz[j][i]==-1 ){
                       grauNo[i]++;
                    }
                }
                printf("    Grau do no %d: %d\n", i+1, grauNo[i]);
            }
        printf("\n....................................\n\n");

    system("pause");
    system("cls || clear");
}

void adicionarNaoDirecionado(){
    FILE *f = fopen("grafoND.txt", "r+");
    int qtdVertices;
    int i;
    Vertice novoVertice;

    printf("Adicionar vertice para grafo nao direcionado...\n");

    i = 0;
    while(i == 0){
        printf("Informe o vertice1 aresta vertice2: ");
        scanf("%d %d %d", &novoVertice.noSaida, &novoVertice.aresta, &novoVertice.noChegada);

        fseek(f, 0, SEEK_END);  //posiciona o ponteiro no final do arquivo para gravar
        fprintf(f, "%d %d %d\n", novoVertice.noSaida, novoVertice.aresta, novoVertice.noChegada); //ida
        fprintf(f, "%d %d %d\n", novoVertice.noChegada, novoVertice.aresta, novoVertice.noSaida); //volta

        printf("Ja adicionou todos os vertices? (1 - SIM | 0 - NAO): ");
        scanf("%d", &i);
    }

    fclose(f);
    system("pause");
    system("cls || clear");
}

void adicionarDirecionado(){
    FILE *f = fopen("grafoD.txt", "r+");
    int qtdVertices;
    int i;
    Vertice novoVertice;

    printf("Adicionar vertice para grafo direcionado...\n");

    i = 0;
    while(i == 0){
        printf("Informe o verticeSaida aresta verticeEntrada: ");
        scanf("%d %d %d", &novoVertice.noSaida, &novoVertice.aresta, &novoVertice.noChegada);

        fseek(f, 0, SEEK_END);  //posiciona o ponteiro no final do arquivo para gravar
        fprintf(f, "%d %d %d\n", novoVertice.noSaida, novoVertice.aresta, novoVertice.noChegada);

        printf("Ja adicionou todos os vertices? (1 - SIM | 0 - NAO): ");
        scanf("%d", &i);
    }

    fclose(f);
    system("pause");
    system("cls || clear");
}
