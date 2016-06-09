#include <stdio.h>
#include <stdlib.h>
#include "ABP.h"
#include "FilaEncadeada.h"

void mostra_int(void *info);
int compara_int(void *a, void *b);

int main()
{
   ABP arvore;
   int x = 0, y;
   int escolha;

   inicializa_ABP(&arvore, sizeof(int));

   do{
       printf("\n TEORIA DOS GRAFOS - PERCURSO EM ARVORE BINARIA\n\n\n");
       printf(" 1 - Inserir elementos\n");
       printf(" 2 - Percurso em Ordem\n");
       printf(" 3 - Percurso Pre-ordem\n");
       printf(" 4 - Percurso Pos-ordem\n");
       printf(" 5 - Percurso em largura\n");
       printf(" 6 - Buscar elemento\n");
       printf(" 0 - Sair\n\n ");

       scanf("%d", &escolha);

       switch(escolha){
               case 1:
                   system("cls");
                   while(x != -1){
                        printf("Informe o valor a ser inserido na arvore (Digite -1 quando terminar): ");
                        scanf("%d", &x);
                        if(x != -1){
                           printf("Inserindo %d...\n\n", x);
                           insere_ABP(&arvore, &x, compara_int);
                           mostra_estrutura(arvore, mostra_int);
                           system("pause");
                           system("cls");
                       }
                    }
                    system("cls");
                    break;
               case 2:
                   percurso_em_ordem(arvore, mostra_int);
                   system("pause");
                   system("cls");
                   break;
               case 3:
                   percurso_pre_ordem(arvore, mostra_int);
                   system("pause");
                   system("cls");
                   break;
               case 4:
                   percurso_pos_ordem(arvore, mostra_int);
                   system("PAUSE");
                   system("CLS");
                   break;
               case 5:
                   percurso_em_largura(arvore, mostra_int);
                   system("PAUSE");
                   system("CLS");
                   break;
               case 6:
                   printf("Digite um valor para ser buscado na arvore: ");
                   scanf("%i", &y);
                   printf("%Buscando %i...\n\n", y);
                   if(busca_APB(arvore, &y, compara_int))
                      printf("%i encontrado!!\n\n", y);
                   else
                      printf("%i nao encontrado!!\n\n", y);
                   system("PAUSE");
                   system("CLS");
                   break;
               case 0:
                   limpa_ABP(&arvore);
                   break;

       }
	}while(escolha != 0);

    return 0;
}

void mostra_int(void *info){
   int *p = (int *) info;
   printf("%i\n", *p);
}

int compara_int(void *a, void *b){
    int *pa = (int *) a;
    int *pb = (int *) b;

    if(*pa > *pb)
       return 1;

    if(*pa < *pb)
       return -1;

    return 0;
}
