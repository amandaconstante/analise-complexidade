#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum { Vermelho, Preto } Cor;

typedef struct no {
    int valor;
    Cor cor;
    struct no *pai, *esquerda, *direita;
} No;

typedef struct {
    No *raiz;
    No *nulo;
} Arvore;

int contador_insercoes = 0;
int contador_remocoes = 0;
int contador_rotacoes = 0;

Arvore* criar_arvore() {
    Arvore* a = malloc(sizeof(Arvore));
    a->nulo = malloc(sizeof(No));
    a->nulo->cor = Preto;
    a->nulo->pai = a->nulo->esquerda = a->nulo->direita = NULL;
    a->nulo->valor = 0;
    a->raiz = a->nulo;
    return a;
}

No* criar_no(Arvore* a, int valor) {
    No* novo = malloc(sizeof(No));
    if (!novo) {
        printf("Erro ao alocar nó.\n");
        exit(1);
    }
    novo->valor = valor;
    novo->cor = Vermelho;
    novo->pai = novo->esquerda = novo->direita = a->nulo;
    return novo;
}

void rotacao_esquerda(Arvore* a, No* x) {
    contador_rotacoes++;
    No* y = x->direita;
    x->direita = y->esquerda;
    if (y->esquerda != a->nulo) y->esquerda->pai = x;
    y->pai = x->pai;
    if (x->pai == a->nulo)
        a->raiz = y;
    else if (x == x->pai->esquerda)
        x->pai->esquerda = y;
    else
        x->pai->direita = y;
    y->esquerda = x;
    x->pai = y;
}

void rotacao_direita(Arvore* a, No* x) {
    contador_rotacoes++;
    No* y = x->esquerda;
    x->esquerda = y->direita;
    if (y->direita != a->nulo) y->direita->pai = x;
    y->pai = x->pai;
    if (x->pai == a->nulo)
        a->raiz = y;
    else if (x == x->pai->direita)
        x->pai->direita = y;
    else
        x->pai->esquerda = y;
    y->direita = x;
    x->pai = y;
}

void balancear_insercao(Arvore* a, No* z) {
    while (z->pai->cor == Vermelho) {
        No* pai = z->pai;
        No* avo = pai->pai;

        if (avo == a->nulo) break;

        if (pai == avo->esquerda) {
            No* tio = avo->direita;
            if (tio->cor == Vermelho) {
                pai->cor = Preto;
                tio->cor = Preto;
                avo->cor = Vermelho;
                z = avo;
            } else {
                if (z == pai->direita) {
                    z = pai;
                    rotacao_esquerda(a, z);
                }
                pai->cor = Preto;
                avo->cor = Vermelho;
                rotacao_direita(a, avo);
            }
        } else {
            No* tio = avo->esquerda;
            if (tio->cor == Vermelho) {
                pai->cor = Preto;
                tio->cor = Preto;
                avo->cor = Vermelho;
                z = avo;
            } else {
                if (z == pai->esquerda) {
                    z = pai;
                    rotacao_direita(a, z);
                }
                pai->cor = Preto;
                avo->cor = Vermelho;
                rotacao_esquerda(a, avo);
            }
        }
    }
    a->raiz->cor = Preto;
}

void inserir(Arvore* a, int valor) {
    contador_insercoes++;
    No* z = criar_no(a, valor);
    No* y = a->nulo;
    No* x = a->raiz;

    while (x != a->nulo) {
        y = x;
        if (valor == x->valor) {
            free(z);  // valor duplicado
            return;
        }
        if (valor < x->valor)
            x = x->esquerda;
        else
            x = x->direita;
    }

    z->pai = y;
    if (y == a->nulo)
        a->raiz = z;
    else if (valor < y->valor)
        y->esquerda = z;
    else
        y->direita = z;

    balancear_insercao(a, z);
}

void gerar_numeros(int* v, int n) {
    for (int i = 0; i < n; i++)
        v[i] = rand() % (n * 10);
}

int main() {
    srand(time(NULL));
    FILE* f = fopen("resultados_rubro_negra.txt", "w");
    if (!f) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    fprintf(f, "Tamanho,Insercoes,Remocoes,Rotacoes\n");

    for (int tamanho = 100; tamanho <= 1000; tamanho += 100) {
        contador_insercoes = contador_remocoes = contador_rotacoes = 0;

        Arvore* a = criar_arvore();
        int* vetor = malloc(tamanho * sizeof(int));
        if (!vetor) {
            printf("Erro ao alocar vetor.\n");
            return 1;
        }

        gerar_numeros(vetor, tamanho);

        for (int i = 0; i < tamanho; i++)
            inserir(a, vetor[i]);

        fprintf(f, "%d,%d,%d,%d\n", tamanho, contador_insercoes, contador_remocoes, contador_rotacoes);

        free(vetor);
        free(a->nulo);
        free(a);
    }

    fclose(f);
    printf("Resultados salvos com sucesso!\n");
    return 0;
}
