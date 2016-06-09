
typedef struct no{
   void *info;
   int fb;
   struct no *esq, *dir, *pai;
}NoABP;

typedef struct{
   int tamanhoInfo;
   NoABP *raiz;
}ABP;

void inicializa_ABP(ABP *a, int t);
void insere_ABP(ABP *a, void *info, int (*compara_info)(void *, void *) );
void remove_ABP(ABP *a, void *info, int (*compara_info)(void *, void *) );
void limpa_ABP(ABP *a);
int busca_APB(ABP a, void *chave, int (*compara_info)(void *, void *) );
void percurso_pre_ordem(ABP a, void (*mostra_info)(void *) );
void percurso_em_ordem(ABP a, void (*mostra_info)(void *) );
void percurso_pos_ordem(ABP a, void (*mostra_info)(void *) );
void mostra_estrutura(ABP a, void (*mostra_info)(void *) );

int altura(NoABP *n);

