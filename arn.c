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
        if (z->pai == z->pai->pai->esquerda) {
            No* y = z->pai->pai->direita;
            if (y->cor == Vermelho) {
                z->pai->cor = Preto;
                y->cor = Preto;
                z->pai->pai->cor = Vermelho;
                z = z->pai->pai;
            } else {
                if (z == z->pai->direita) {
                    z = z->pai;
                    rotacao_esquerda(a, z);
                }
                z->pai->cor = Preto;
                z->pai->pai->cor = Vermelho;
                rotacao_direita(a, z->pai->pai);
            }
        } else {
            No* y = z->pai->pai->esquerda;
            if (y->cor == Vermelho) {
                z->pai->cor = Preto;
                y->cor = Preto;
                z->pai->pai->cor = Vermelho;
                z = z->pai->pai;
            } else {
                if (z == z->pai->esquerda) {
                    z = z->pai;
                    rotacao_direita(a, z);
                }
                z->pai->cor = Preto;
                z->pai->pai->cor = Vermelho;
                rotacao_esquerda(a, z->pai->pai);
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
        if (valor < x->valor)
            x = x->esquerda;
        else if (valor > x->valor)
            x = x->direita;
        else {
            free(z);
            return; // não insere duplicados
        }
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

No* minimo(Arvore* a, No* x) {
    while (x->esquerda != a->nulo)
        x = x->esquerda;
    return x;
}

void balancear_remocao(Arvore* a, No* x) {
    while (x != a->raiz && x->cor == Preto) {
        if (x == x->pai->esquerda) {
            No* w = x->pai->direita;
            if (w->cor == Vermelho) {
                w->cor = Preto;
                x->pai->cor = Vermelho;
                rotacao_esquerda(a, x->pai);
                w = x->pai->direita;
            }
            if (w->esquerda->cor == Preto && w->direita->cor == Preto) {
                w->cor = Vermelho;
                x = x->pai;
            } else {
                if (w->direita->cor == Preto) {
                    w->esquerda->cor = Preto;
                    w->cor = Vermelho;
                    rotacao_direita(a, w);
                    w = x->pai->direita;
                }
                w->cor = x->pai->cor;
                x->pai->cor = Preto;
                w->direita->cor = Preto;
                rotacao_esquerda(a, x->pai);
                x = a->raiz;
            }
        } else {
            No* w = x->pai->esquerda;
            if (w->cor == Vermelho) {
                w->cor = Preto;
                x->pai->cor = Vermelho;
                rotacao_direita(a, x->pai);
                w = x->pai->esquerda;
            }
            if (w->direita->cor == Preto && w->esquerda->cor == Preto) {
                w->cor = Vermelho;
                x = x->pai;
            } else {
                if (w->esquerda->cor == Preto) {
                    w->direita->cor = Preto;
                    w->cor = Vermelho;
                    rotacao_esquerda(a, w);
                    w = x->pai->esquerda;
                }
                w->cor = x->pai->cor;
                x->pai->cor = Preto;
                w->esquerda->cor = Preto;
                rotacao_direita(a, x->pai);
                x = a->raiz;
            }
        }
    }
    x->cor = Preto;
}

void transplante(Arvore* a, No* u, No* v) {
    if (u->pai == a->nulo)
        a->raiz = v;
    else if (u == u->pai->esquerda)
        u->pai->esquerda = v;
    else
        u->pai->direita = v;
    v->pai = u->pai;
}

void remover(Arvore* a, int valor) {
    No* z = a->raiz;
    while (z != a->nulo) {
        if (valor == z->valor)
            break;
        if (valor < z->valor)
            z = z->esquerda;
        else
            z = z->direita;
    }
    if (z == a->nulo) return; // não encontrado

    contador_remocoes++;

    No* y = z;
    Cor y_cor_original = y->cor;
    No* x;

    if (z->esquerda == a->nulo) {
        x = z->direita;
        transplante(a, z, z->direita);
    } else if (z->direita == a->nulo) {
        x = z->esquerda;
        transplante(a, z, z->esquerda);
    } else {
        y = minimo(a, z->direita);
        y_cor_original = y->cor;
        x = y->direita;
        if (y->pai == z)
            x->pai = y;
        else {
            transplante(a, y, y->direita);
            y->direita = z->direita;
            y->direita->pai = y;
        }
        transplante(a, z, y);
        y->esquerda = z->esquerda;
        y->esquerda->pai = y;
        y->cor = z->cor;
    }

    free(z);

    if (y_cor_original == Preto)
        balancear_remocao(a, x);
}

void gerar_numeros(int* v, int n) {
    for (int i = 0; i < n; i++)
        v[i] = rand() % (n * 10);
}

int main() {
    srand(time(NULL));
    FILE* f = fopen("resultados_rubro_negra.txt", "w");
    if (!f) return 1;

    fprintf(f, "Tamanho,Insercoes,Remocoes,Rotacoes\n");

    for (int tamanho = 100; tamanho <= 10000; tamanho += 1000) {
        contador_insercoes = contador_remocoes = contador_rotacoes = 0;
        Arvore* a = criar_arvore();
        int* vetor = malloc(tamanho * sizeof(int));

        gerar_numeros(vetor, tamanho);
        for (int i = 0; i < tamanho; i++)
            inserir(a, vetor[i]);

        for (int i = 0; i < tamanho / 4; i++)
            remover(a, vetor[i]);

        fprintf(f, "%d,%d,%d,%d\n", tamanho, contador_insercoes, contador_remocoes, contador_rotacoes);

        free(vetor);
        free(a->nulo);
        free(a);
    }

    fclose(f);
    printf("Arquivo gerado com sucesso.\n");
    return 0;
}
