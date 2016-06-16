/*
		Projeto Final - Teoria dos Grafos
		Braco de solda


		O PROGRAMA VAI LER O TXT DO GRAFO COMPLETO E SUAS DISTANCIAS
		RODA O FLOYD PRA VER QUAL A DISTANCIA ENTRE TODOS OS VERTICES
		COM ISSO, MONTA O GRAFO DE LIGAÇÃO UNINDO OS VERTICES MARCADOS NO VETORSOLDA
		USANDO A DISTANCIA FORNECIDA PELO FLOYD
		COM ISSO TEREMOS A SOLDA COM AS MENORES DISTANCIAS
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define INFINITO 500

void solda();
void floydWarshall(int **matriz, int **matrizFloyd, int qtdVertices);
void adjacente(int **matriz, int quantidadeVertices);
int minimo(int a, int b);

int main(){
	int escolha;

	do{
        printf("\n                TEORIA DOS GRAFOS\n");
        printf("\n    1 - Algoritmo de Solda\n");

        printf("    0 - Sair\n\n");

        printf("    Informe a operacao a ser efetuada: ");

		scanf("%d", &escolha);
		system("cls || clear");

		switch(escolha){
			case 1:
				solda();
				break;
			case 0:
				break;
		}
	}while(escolha != 0);

    return 0;
}

void solda(){
	int qtdVertices, i, j, x, y, soldar = -20;
	int *vetorSolda;
	int **matriz;
	int **matrizFloyd;
	int **grafoFinal;
	int distanciaMinima = 0, primeiro, proximo, atual, terminou;

	printf("\n\n    Informe a quantidade de vertices: ");
	scanf("%d", &qtdVertices);

	vetorSolda = (int*)calloc(qtdVertices, sizeof(int)); //vetor de vertices que precisa soldar (calloc para inicar zerado)

	printf("\n\n    Informe os vertices a serem soldados (-1 para terminar):\n    ");
	while(soldar != -1){
        scanf("%d", &soldar);
        if(soldar != -1){
            soldar--; //decrementa o valor para colocar no vetor que inicia em 0
            vetorSolda[soldar] = 1; //marca o vertice como ponto de solda
        }
        printf("    ");
	}

	system("cls");

	/*-alocação e montagem da matriz adjacente com peso e alocacao das demais matrizes-*/
    matriz = malloc(sizeof(int*) * qtdVertices);  //aloca as linhas da matriz
	matrizFloyd = malloc(sizeof(int*) * qtdVertices);  //aloca as linhas da matriz
	grafoFinal = malloc(sizeof(int*) * qtdVertices);  //aloca as linhas da matriz
    for(i = 0; i < qtdVertices; i++){
        matriz[i] = malloc(sizeof(int) * qtdVertices);   // aloca as colunas da matriz
		matrizFloyd = malloc(sizeof(int*) * qtdVertices);  //aloca as linhas da matriz
		grafoFinal = malloc(sizeof(int*) * qtdVertices);  //aloca as linhas da matriz
        for(j = 0; j < qtdVertices; j++){
            matriz[i][j] = INFINITO;    //inicializa a matriz com pesos INFINITO
        }
    }
    adjacente(matriz, qtdVertices);  //monta a matriz adjacente
    /*-----------------------------------------*/

	floydWarshall(matriz, matrizFloyd, qtdVertices); //monta a matriz dos menores caminhos entre cada vertice

	i = 0;
	do{ //encontrar o primeiro vertice a ser soldado
		if(vetorSolda[i] == 1){
			primeiro = i;
			atual = i;
		}else{
			i++;
		}
	}while(vetorSolda[i] == 0);

	proximo = atual + 1; //proximo comeca na posicao depois do primeiro
	terminou = proximo;  //terminou ira contar os passos do proximo ate o final do vetorSolda

	while(terminou != qtdVertices){
		/*toda vez que andar com o proximo, incrementa naoTerminou*/
		while(vetorSolda[proximo] != 1){
			proximo++;
			terminou++;
		}

		distanciaMinima += matrizFloyd[atual][proximo];
		grafoFinal[atual][proximo] = matrizFloyd[atual][proximo];
		atual = proximo;
	}

	distanciaMinima += matrizFloyd[atual][primeiro]; //para completar o ciclo, pega o atual que agora eh o ultimo e liga com o primeiro

	printf("\n\n    Distancia minima a ser percorrida: %d\n\n    ", distanciaMinima);

	printf("Grafo de conexao:\n\n");
	for(x = 0; x < qtdVertices; x++){
		printf("    ");
		for(y = 0; y < qtdVertices; y++){
			printf("%d\t", grafoFinal[x][y]);
		}
		printf("\n");
	}

	system("pause");
	system("cls");

	free(matriz);
	free(vetorSolda);
}

void floydWarshall(int **matriz, int **matrizFloyd, int qtdVertices){
	int k, i, j; 		//indices
	int ***matrizes;	//vetor de k matrizes

	printf("\n\n    Calculando Floyd-Warshall... ");

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


	/**coloca o resultado final do floyd na matriz inicial**/
	for(j = 0; j < qtdVertices; j++){
		if(i == j)
            matrizFloyd[i][j] = 0;
        else
			matrizFloyd[i][j] = matrizes[qtdVertices][i][j];
	}

	free(matrizes);

	Sleep(1); //delay de 1 segundo
    printf("   OK.\n\n");
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

	printf("    Montando matriz adjacente com peso... ");
	if(f == NULL){
			printf("Erro ao abrir o grafo!\n");
            exit(1);
	}else{
		while((fscanf(f," %d %d %d\n", &x, &peso, &y)) != EOF){     //le uma linha de cada vez
			if(matriz[x-1][y-1] == -1){ /*se ainda nao foi inserido nenhum peso*/
                matriz[x-1][y-1] = peso; /*insere o peso lido*/
			}else{
                if(matriz[x-1][y-1] > peso) /*se ja foi inserido um peso mas ele é maior do que o lido*/
                    matriz[x-1][y-1] = peso; /*insere o peso novo menor*/
			}
		}
	}

	fclose(f);

	Sleep(1); //delay de 1 segundo
	printf("   OK.\n\n");
}



