#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Estrutura para representar o Nó na árvore binária
typedef struct No {
    int chave;
    struct No *esquerda;
    struct No *direita;
} No;

// Prototipação das funções para manipulação da árvore binária
No* inicializarArvore(int chave);
No* adicionarNo(No *raiz, int chave);
No* buscarNo(No *raiz, int chave);
No* excluirNo(No *raiz, int chave);
void exibirArvore(No *raiz);

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    printf("Árvore Binária em C!\n");

    No *raiz = inicializarArvore(10);
    adicionarNo(raiz, 5);
    adicionarNo(raiz, 6);
    adicionarNo(raiz, 15);
    adicionarNo(raiz, 13);

    exibirArvore(raiz);

    excluirNo(raiz, 10);
    printf("\n");

    exibirArvore(raiz);

    return 0;
}

// Função para criar uma nova árvore com um nó raiz
No* inicializarArvore(int chave) {
    No *raiz = (No *)malloc(sizeof(No));
    if (!raiz) {
        fprintf(stderr, "Falha na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    raiz->chave = chave;
    raiz->esquerda = raiz->direita = NULL;
    return raiz;
}

// Função para inserir um nó na árvore
No* adicionarNo(No *raiz, int chave) {
    if (!raiz) {
        return inicializarArvore(chave);
    }

    if (chave < raiz->chave) {
        raiz->esquerda = adicionarNo(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        raiz->direita = adicionarNo(raiz->direita, chave);
    } else {
        printf("Chave já presente na árvore.\n");
    }

    return raiz;
}

// Função para localizar um nó na árvore
No* buscarNo(No *raiz, int chave) {
    if (!raiz) {
        printf("Chave não encontrada.\n");
        return NULL;
    }
    if (raiz->chave == chave) {
        return raiz;
    } else if (chave < raiz->chave) {
        return buscarNo(raiz->esquerda, chave);
    } else {
        return buscarNo(raiz->direita, chave);
    }
}

// Função para remover um nó da árvore
No* excluirNo(No *raiz, int chave) {
    if (!raiz) return NULL;

    if (chave < raiz->chave) {
        raiz->esquerda = excluirNo(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        raiz->direita = excluirNo(raiz->direita, chave);
    } else {
        if (!raiz->esquerda && !raiz->direita) {
            free(raiz);
            return NULL;
        } else if (!raiz->esquerda || !raiz->direita) {
            No *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            free(raiz);
            return temp;
        } else {
            No *temp = raiz->esquerda;
            while (temp->direita) {
                temp = temp->direita;
            }
            raiz->chave = temp->chave;
            temp->chave = chave;
            raiz->esquerda = excluirNo(raiz->esquerda, chave);
        }
    }
    return raiz;
}

// Função para exibir a árvore em ordem
void exibirArvore(No *raiz) {
    if (raiz) {
        exibirArvore(raiz->esquerda);
        printf("%d ", raiz->chave);
        exibirArvore(raiz->direita);
    }
}

