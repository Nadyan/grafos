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

#define TOTALVERTICES 50

typedef struct Vertice{
    int noSaida;
    int noChegada;
    int aresta;
}Vertice;

typedef struct item{
	int campo;
	int aresta;
	struct item* prox;
}ITEM;

int *grauNo; //variavel global
int qtdVerticesVetor; //variavel global
ITEM lista[TOTALVERTICES+1];  //declara a lista

void adjacente();
void adjacenteDirecionado();
void incidencia();
void incidenciaDirecionado();
void adicionarDirecionado();
void adicionarNaoDirecionado();

/************* FUNÇÕES DA LISTA E VETOR ******************/
void inicializaLista(ITEM *lista, int qtdVertices);
void imprimirLista(ITEM *lista, int qtdVertices);
void inserirArestaLista(ITEM *lista);
void inicializaVetor();

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
        printf("    7 - Gerar Lista do Grafo\n");
        printf("    8 - Gerar Vetor do Grafo\n");
        printf("___________________________________________\n\n");
        printf("    0 - Sair\n\n");

        printf("    Informe a operacao a ser efetuada: ");
		scanf("%d", &escolha);

		system("cls || clear");
		switch(escolha){
			case 1:
				adjacente();
				system("pause");
                system("cls || clear");
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
            case 7:
                inserirArestaLista(lista);
                break;
            case 8:
                inicializaVetor();
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
    //int *grauNo;

	if(f == NULL)
			printf("Erro ao abrir o arquivo!\n");
	else{
		printf("\n    Informe a quantidade de vertices: ");
		scanf("%d", &qtdVertices);
		//fscanf(f, "%d \n", &qtdVertices);

		qtdVerticesVetor = qtdVertices;

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

	free(matrizComplementar);
	fclose(f);
}

void adjacenteDirecionado(){
	FILE *f = fopen("grafoD.txt", "r+");
	int i, j; //campos da matriz
    int qtdVertices;
	char aresta[3];
    int **matriz, **matrizComplementar; // declara a matriz de acordo com aquantidade de vertices
    //int *grauNo;

	if(f == NULL)
			printf("Erro ao abrir o arquivo!\n");
	else{
		printf("\n    Informe a quantidade de vertices: ");
		scanf("%d", &qtdVertices);
		//fscanf(f, "%d \n", &qtdVertices);

		qtdVerticesVetor = qtdVertices;

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
    //int *grauNo;

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
    //int *grauNo;

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



/***************** FUNÇOES DE LISTA ******************/
void inicializaLista(ITEM *lista, int qtdVertices){
    int i;

    qtdVerticesVetor = qtdVertices;

    for(i = 1; i <= qtdVertices; i++){
        lista[i].campo = 0;
        lista[i].prox = NULL;
    }
}

void inserirArestaLista(ITEM *lista){
    int qtdVertices, a, b, aresta, tipoGrafo;  //aresta nao sera utilizada
    FILE *f;
    ITEM *aux;
    ITEM *tmp;

    printf("\n    informe o tipo do grafo:\n    1 - Nao direcionado\n    2 - Direcionado\n");
    scanf("%d", &tipoGrafo);

    switch(tipoGrafo){
        case 1:
            f = fopen("grafoND.txt", "r+");
            break;
        case 2:
            f = fopen("grafoD.txt", "r+");
            break;
    }

    printf("\n    Informe a quantidade de vertices: ");
    scanf("%d", &qtdVertices);

    system("cls || clear");

    inicializaLista(lista, qtdVertices);

    if(f == NULL)
			printf("\n    Erro ao abrir o arquivo!\n");
	else{
            while((fscanf(f," %d %d %d\n", &a, &aresta, &b)) != EOF){
                aux = (ITEM*) malloc((int)sizeof(ITEM));    //retorno de um ponteiro genérico.
                aux->campo = b;
                aux->prox = NULL;

                lista[a].campo++;
                if(lista[a].prox == NULL)                   // Se a lista estiver vazia
                  lista[a].prox = aux;
                else{
                  tmp = lista[a].prox;
                  if (tmp->campo > b){                     //insere como primeiro da lista
                    aux->prox = tmp;
                    lista[a].prox = aux;
                    lista[a].aresta = aresta;
                } 		                                    //insere os vértices ordenados
                  else if(tmp->prox == NULL){
                    aux->prox = tmp->prox;
                    tmp->prox = aux;
                }
                else{
                    while((tmp->prox != NULL) && (tmp->prox->campo < b))
                        tmp = tmp->prox;
                    aux->prox = tmp->prox;
                    tmp->prox = aux;
                  }
                }
            }
	}

    fclose(f);

    imprimirLista(lista, qtdVertices);
}

void imprimirLista(ITEM *lista, int qtdVertices){
      int i;
      ITEM *tmp;

      printf("\n    Vertice    ==>    Vertices_adjacentes\n\n");

      for(i = 1; i <= qtdVertices; i++){
        tmp = lista[i].prox;
        printf("    %d:        ==>", i);
        while(tmp != NULL){
          printf("       %d  ", tmp->campo);
          tmp = tmp->prox;
        }
        printf("\n\n");
      }
      printf("\n");
      system("pause");
      system("cls || clear");
}

/****************** FUNCOES VETORES *********************/
void inicializaVetor(){
    int tipoGrafo, i, j, t, cont = 0, a, b, aresta, x;
    int *v; //vetor com o grau de cada no
    int *w; //vetor com os nos adjacentes
    FILE *f;

    printf("\n    informe o tipo do grafo:\n    1 - Nao direcionado\n    2 - Direcionado(indisponivel)\n");
    scanf("%d", &tipoGrafo);

    switch(tipoGrafo){
        case 1:
            adjacente();   //pegar grau do no de grafo nao direcionado
            system("cls || clear");
            f = fopen("grafoND.txt", "r+");
            break;
        case 2:
            printf("\n    Opcao indisponivel!\n\n");
            system("pause");
            return;
    }

    v = malloc(sizeof(int) * qtdVerticesVetor);

    for(i = 0; i < qtdVerticesVetor; i++){
        cont =  cont + grauNo[i];
        v[i] = grauNo[i];  //preenche vetor v
    }

    t = 0;

    w = malloc(sizeof(int) * cont);

    while((fscanf(f," %d %d %d\n", &a, &aresta, &b) != EOF)){
        w[t] = b;
        t++;
    }

    /********* Imprime vetor ***********/
    x = 0;
    for(i = 0; i < qtdVerticesVetor; i++){
        printf("Vertice %d ==> ", i+1);
        for(j = 0; j < v[i]; j++){
            printf(" %d ", w[x]);  //imprime vizinhos
            x++;
        }
        printf("\n");
    }
    /***********************************/

    free(v);
    free(w);
    free(grauNo);
    cont = 0;

    fclose(f);

    printf("\n\n");
    system("pause");
    system("cls || clear");
}




