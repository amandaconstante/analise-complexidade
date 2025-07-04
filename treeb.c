#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int contador_insercoes = 0;
int contador_remocoes = 0;
int contador_balanceamentos = 0;

typedef struct no {
    int total;
    int* chaves;
    struct no** filhos;
    struct no* pai;
} No;

typedef struct arvoreB {
    No* raiz;
    int ordem;
} ArvoreB;

ArvoreB* criaArvore(int ordem) {
    ArvoreB* a = malloc(sizeof(ArvoreB));
    a->ordem = ordem;
    a->raiz = NULL;
    return a;
}

No* criaNo(ArvoreB* arvore) {
    int max = arvore->ordem * 2;
    No* no = malloc(sizeof(No));
    no->chaves = malloc(sizeof(int) * (max + 1));
    no->filhos = malloc(sizeof(No*) * (max + 2));
    no->total = 0;
    no->pai = NULL;
    for (int i = 0; i < max + 2; i++) no->filhos[i] = NULL;
    return no;
}

int pesquisaBinaria(No* no, int chave) {
    int i = 0;
    while (i < no->total && chave > no->chaves[i]) i++;
    return i;
}

No* localizaNo(ArvoreB* arvore, int chave) {
    No* no = arvore->raiz;
    while (no != NULL) {
        int i = pesquisaBinaria(no, chave);
        if (no->filhos[i] == NULL) return no;
        no = no->filhos[i];
    }
    return NULL;
}

void adicionaChaveNo(No* no, No* novo, int chave) {
    int i = pesquisaBinaria(no, chave);
    for (int j = no->total - 1; j >= i; j--) {
        no->chaves[j + 1] = no->chaves[j];
        no->filhos[j + 2] = no->filhos[j + 1];
    }
    no->chaves[i] = chave;
    no->filhos[i + 1] = novo;
    no->total++;
}

int transbordo(ArvoreB* arvore, No* no) {
    return no->total > arvore->ordem * 2;
}

No* divideNo(ArvoreB* arvore, No* no, int* promovido) {
    contador_balanceamentos++;
    int meio = arvore->ordem;
    *promovido = no->chaves[meio];
    No* novo = criaNo(arvore);
    novo->pai = no->pai;

    for (int i = meio + 1; i < no->total; i++) {
        novo->chaves[novo->total] = no->chaves[i];
        novo->filhos[novo->total] = no->filhos[i];
        if (novo->filhos[novo->total]) novo->filhos[novo->total]->pai = novo;
        novo->total++;
    }
    novo->filhos[novo->total] = no->filhos[no->total];
    if (novo->filhos[novo->total]) novo->filhos[novo->total]->pai = novo;
    no->total = meio;
    return novo;
}

void adicionaChaveRecursivo(ArvoreB* arvore, No* no, No* novo, int chave) {
    adicionaChaveNo(no, novo, chave);
    if (transbordo(arvore, no)) {
        int promovido;
        No* novoIrmao = divideNo(arvore, no, &promovido);
        if (no->pai == NULL) {
            No* pai = criaNo(arvore);
            pai->filhos[0] = no;
            adicionaChaveNo(pai, novoIrmao, promovido);
            no->pai = pai;
            novoIrmao->pai = pai;
            arvore->raiz = pai;
        } else {
            adicionaChaveRecursivo(arvore, no->pai, novoIrmao, promovido);
        }
    }
}

void adicionaChave(ArvoreB* arvore, int chave) {
    contador_insercoes++;
    if (arvore->raiz == NULL) {
        arvore->raiz = criaNo(arvore);
    }
    No* no = localizaNo(arvore, chave);
    adicionaChaveRecursivo(arvore, no, NULL, chave);
}

void removeChave(ArvoreB* arvore, int chave) {
    No* no = localizaNo(arvore, chave);
    if (!no) return;
    int i = pesquisaBinaria(no, chave);
    if (i >= no->total || no->chaves[i] != chave) return;
    for (int j = i; j < no->total - 1; j++) {
        no->chaves[j] = no->chaves[j + 1];
        no->filhos[j + 1] = no->filhos[j + 2];
    }
    no->total--;
    contador_remocoes++;
}

void liberaNos(No* no, int maxFilhos) {
    if (no) {
        for (int i = 0; i <= no->total; i++) liberaNos(no->filhos[i], maxFilhos);
        free(no->chaves);
        free(no->filhos);
        free(no);
    }
}

void liberaArvore(ArvoreB* arvore) {
    liberaNos(arvore->raiz, arvore->ordem * 2 + 1);
    free(arvore);
}

int main() {
    srand(time(NULL));

    int amostras = 10;
    int tamanhos[] = {100, 500, 1000, 2000, 4000, 6000, 8000, 10000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(int);
    int ordens[] = {1, 5, 10};

    for (int o = 0; o < 3; o++) {
        int ordem = ordens[o];
        FILE* f = fopen("resultados_arvore_b.txt", o == 0 ? "w" : "a");
        if (!f) {
            printf("Erro ao criar arquivo de saída.\n");
            continue;
        }
        if (o == 0) fprintf(f, "Tamanho,Ordem,Insercoes,Remocoes,Balanceamentos\n");

        for (int t = 0; t < num_tamanhos; t++) {
            int tam = tamanhos[t];
            int soma_ins = 0, soma_rem = 0, soma_bal = 0;

            for (int a = 0; a < amostras; a++) {
                contador_insercoes = 0;
                contador_remocoes = 0;
                contador_balanceamentos = 0;

                ArvoreB* arv = criaArvore(ordem);
                int* dados = malloc(sizeof(int) * tam);
                for (int i = 0; i < tam; i++) dados[i] = rand();
                for (int i = 0; i < tam; i++) adicionaChave(arv, dados[i]);
                for (int i = 0; i < tam / 2; i++) removeChave(arv, dados[i]);

                soma_ins += contador_insercoes;
                soma_rem += contador_remocoes;
                soma_bal += contador_balanceamentos;

                free(dados);
                liberaArvore(arv);
            }

            fprintf(f, "%d,%d,%d,%d,%d\n", tam, ordem, soma_ins / amostras, soma_rem / amostras, soma_bal / amostras);
        }

        fclose(f);
    }

    printf("Resultados salvos com sucesso.\n");
    return 0;
}