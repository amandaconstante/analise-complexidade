#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    int valor;
    int altura;
} No;

typedef struct arvore {
    struct no* raiz;
} Arvore;

// ===> Contadores de operações 
int contador_insercoes = 0;
int contador_remocoes = 0;
int contador_rotacoes = 0;

int max(int a, int b) { return a > b ? a : b; }

int altura(No* no) {
    return no != NULL ? no->altura : 0;
}

int fb(No* no) {
    return altura(no->esquerda) - altura(no->direita);
}

// ===> Criação da árvore
Arvore* criar() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
    return arvore;
}

// ===> Rotação Simples Direita 
No* rsd(Arvore* arvore, No* no) {
    contador_rotacoes++;
    No* pai = no->pai;
    No* esquerda = no->esquerda;

    if (esquerda->direita) esquerda->direita->pai = no;

    no->esquerda = esquerda->direita;
    no->pai = esquerda;

    esquerda->direita = no;
    esquerda->pai = pai;

    if (pai == NULL)
        arvore->raiz = esquerda;
    else if (pai->esquerda == no)
        pai->esquerda = esquerda;
    else
        pai->direita = esquerda;

    no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;
    esquerda->altura = max(altura(esquerda->esquerda), altura(esquerda->direita)) + 1;
    return esquerda;
}

// ===> Rotação Simples Esquerda
No* rse(Arvore* arvore, No* no) {
    contador_rotacoes++;
    No* pai = no->pai;
    No* direita = no->direita;

    if (direita->esquerda) direita->esquerda->pai = no;

    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    if (pai == NULL)
        arvore->raiz = direita;
    else if (pai->esquerda == no)
        pai->esquerda = direita;
    else
        pai->direita = direita;

    no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;
    direita->altura = max(altura(direita->esquerda), altura(direita->direita)) + 1;
    return direita;
}

// ===> Rotações duplas
No* rdd(Arvore* arvore, No* no) {
    no->esquerda = rse(arvore, no->esquerda);
    return rsd(arvore, no);
}

No* rde(Arvore* arvore, No* no) {
    no->direita = rsd(arvore, no->direita);
    return rse(arvore, no);
}

// ===> Balanceamento 
void balanceamento(Arvore* arvore, No* no) {
    while (no) {
        no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;
        int fator = fb(no);

        if (fator > 1) {
            if (fb(no->esquerda) >= 0) rsd(arvore, no);
            else rdd(arvore, no);
        } else if (fator < -1) {
            if (fb(no->direita) <= 0) rse(arvore, no);
            else rde(arvore, no);
        }

        no = no->pai;
    }
}

// ===> Inserção
void adicionar(Arvore* arvore, int valor) {
    contador_insercoes++;
    No* no = arvore->raiz;
    No* pai = NULL;

    while (no) {
        pai = no;
        no = valor < no->valor ? no->esquerda : no->direita;
    }

    No* novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->pai = pai;
    novo->esquerda = novo->direita = NULL;
    novo->altura = 1;

    if (!pai)
        arvore->raiz = novo;
    else if (valor < pai->valor)
        pai->esquerda = novo;
    else
        pai->direita = novo;

    balanceamento(arvore, pai);
}

No* localizar(No* no, int valor) {
    while (no && no->valor != valor)
        no = valor < no->valor ? no->esquerda : no->direita;
    return no;
}

No* minimo(No* no) {
    while (no->esquerda) no = no->esquerda;
    return no;
}

// ===> Remoção
void remover(Arvore* arvore, int valor) {
    No* no = localizar(arvore->raiz, valor);
    if (!no) return;

    contador_remocoes++;

    No* pai = no->pai;

    if (!no->esquerda || !no->direita) {
        No* filho = no->esquerda ? no->esquerda : no->direita;

        if (!pai)
            arvore->raiz = filho;
        else if (pai->esquerda == no)
            pai->esquerda = filho;
        else
            pai->direita = filho;

        if (filho) filho->pai = pai;
        free(no);

        balanceamento(arvore, pai);
    } else {
        No* sucessor = minimo(no->direita);
        no->valor = sucessor->valor;

        No* filho = sucessor->direita;
        No* pai_sucessor = sucessor->pai;

        if (pai_sucessor->esquerda == sucessor)
            pai_sucessor->esquerda = filho;
        else
            pai_sucessor->direita = filho;

        if (filho) filho->pai = pai_sucessor;

        free(sucessor);
        contador_remocoes++;

        balanceamento(arvore, pai_sucessor);
    }
}

void percorrer(No* no, void (*callback)(int)) {
    if (no) {
        percorrer(no->esquerda, callback);
        callback(no->valor);
        percorrer(no->direita, callback);
    }
}

void visitar(int valor) {
    printf("%d ", valor);
}

#define MAX_TAMANHO 10000
#define PASSO 1000
#define AMOSTRAS 10

// ===> Função para liberar memória da árvore recursivamente
void liberarNo(No* no) {
    if (no) {
        liberarNo(no->esquerda);
        liberarNo(no->direita);
        free(no);
    }
}

void liberarArvore(Arvore* arvore) {
    if (arvore) {
        liberarNo(arvore->raiz);
        free(arvore);
    }
}

int main() {
    srand(time(NULL));

    FILE* f = fopen("resultados_avl.txt", "w");
    if (!f) {
        printf("Erro ao criar arquivo 'resultados_avl.txt'.\n");
        return 1;
    }

    fprintf(f, "Tamanho,Insercoes,Remocoes,Rotacoes\n");

    for (int tamanho = 1000; tamanho <= MAX_TAMANHO; tamanho += PASSO) {
        int soma_insercoes = 0;
        int soma_remocoes = 0;
        int soma_rotacoes = 0;

        for (int i = 0; i < AMOSTRAS; i++) {
            Arvore* a = criar();
            contador_insercoes = 0;
            contador_remocoes = 0;
            contador_rotacoes = 0;

            int* dados = malloc(tamanho * sizeof(int));

            // Gerar chaves aleatórias
            for (int j = 0; j < tamanho; j++) {
                dados[j] = rand();
                adicionar(a, dados[j]);
            }

            // Removr metade das chaves (N/2)
            for (int j = 0; j < tamanho / 2; j++) {
                remover(a, dados[j]);
            }

            soma_insercoes += contador_insercoes;
            soma_remocoes += contador_remocoes;
            soma_rotacoes += contador_rotacoes;

            free(dados);
            liberarArvore(a);
        }

        float media_insercoes = (float)soma_insercoes / AMOSTRAS;
        float media_remocoes = (float)soma_remocoes / AMOSTRAS;
        float media_rotacoes = (float)soma_rotacoes / AMOSTRAS;

        fprintf(f, "%d,%.0f,%.0f,%.0f\n", tamanho, media_insercoes, media_remocoes, media_rotacoes);

        printf("Tamanho: %d | Inserções: %.0f | Remoções: %.0f | Rotações: %.0f\n",
               tamanho, media_insercoes, media_remocoes, media_rotacoes);
    }

    fclose(f);

    printf("Testes AVL finalizados. Resultados gravados em 'resultados_avl.txt'\n");

    return 0;
}
