#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição de nó para estrutura árvore + heap, conhecida como Treap
struct NodoTreap
{
    int chave;             // Valor do nó
    int prioridade;        // Prioridade do nó
    struct NodoTreap *esquerda; // Ponteiro para o nó à esquerda
    struct NodoTreap *direita;  // Ponteiro para o nó à direita
};

typedef struct NodoTreap NodoTreap;
NodoTreap *inicializarTreap(int chave);
NodoTreap *girarEsquerda(NodoTreap *raiz);
NodoTreap *girarDireita(NodoTreap *raiz);
NodoTreap *adicionarNodo(NodoTreap *raiz, int chave);
NodoTreap *removerNodo(NodoTreap *raiz, int chave);
void exibirTreap(NodoTreap *raiz, int profundidade);

int main(void)
{
    NodoTreap *raiz = inicializarTreap(10);
    raiz = adicionarNodo(raiz, 5);
    raiz = adicionarNodo(raiz, 6);
    raiz = adicionarNodo(raiz, 15);
    raiz = adicionarNodo(raiz, 13);

    printf("Estrutura Treap:\n");
    exibirTreap(raiz, 0);

    raiz = removerNodo(raiz, 5);
    printf("\nEstrutura Treap após remoção:\n");
    exibirTreap(raiz, 0);

    return 0;
}

// Função para criar uma Treap com um valor inicial
NodoTreap *inicializarTreap(int chave)
{
    NodoTreap *novoNodo = (NodoTreap *)malloc(sizeof(NodoTreap));
    if (novoNodo == NULL)
    {
        printf("Erro de alocação de memória.\n");
        exit(EXIT_FAILURE);
    }

    novoNodo->chave = chave;
    novoNodo->prioridade = rand() % 100;
    novoNodo->esquerda = NULL;
    novoNodo->direita = NULL;
    return novoNodo;
}

// Função para fazer uma rotação à esquerda em uma Treap
NodoTreap *girarEsquerda(NodoTreap *raiz)
{
    NodoTreap *novaRaiz = raiz->direita;
    raiz->direita = novaRaiz->esquerda;
    novaRaiz->esquerda = raiz;
    return novaRaiz;
}

// Função para fazer uma rotação à direita em uma Treap
NodoTreap *girarDireita(NodoTreap *raiz)
{
    NodoTreap *novaRaiz = raiz->esquerda;
    raiz->esquerda = novaRaiz->direita;
    novaRaiz->direita = raiz;
    return novaRaiz;
}

// Função para adicionar um valor na Treap
NodoTreap *adicionarNodo(NodoTreap *raiz, int chave)
{
    if (raiz == NULL)
        return inicializarTreap(chave);

    if (chave < raiz->chave)
    {
        raiz->esquerda = adicionarNodo(raiz->esquerda, chave);

        // Manter a Treap balanceada
        if (raiz->esquerda->prioridade > raiz->prioridade)
            raiz = girarDireita(raiz);
    }
    else if (chave > raiz->chave)
    {
        raiz->direita = adicionarNodo(raiz->direita, chave);

        if (raiz->direita->prioridade > raiz->prioridade)
            raiz = girarEsquerda(raiz);
    }

    return raiz;
}

// Função para remover um valor da Treap
NodoTreap *removerNodo(NodoTreap *raiz, int chave)
{
    if (raiz == NULL)
        return raiz;

    // Buscando o valor na Treap
    if (chave < raiz->chave)
        raiz->esquerda = removerNodo(raiz->esquerda, chave);

    else if (chave > raiz->chave)
        raiz->direita = removerNodo(raiz->direita, chave);

    // Se a chave foi encontrada, proceder com a remoção
    else
    {
        // Caso 1: Nó sem filhos
        if (raiz->esquerda == NULL && raiz->direita == NULL)
        {
            free(raiz);
            return NULL;
        }
        // Caso 2: Somente filho à direita
        else if (raiz->esquerda == NULL)
        {
            NodoTreap *temp = raiz->direita;
            free(raiz);
            return temp;
        }
        // Caso 3: Somente filho à esquerda
        else if (raiz->direita == NULL)
        {
            NodoTreap *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        // Caso 4: Dois filhos
        else
        {
            // Escolhendo o sucessor baseado na prioridade
            if (raiz->esquerda->prioridade > raiz->direita->prioridade)
            {
                raiz = girarDireita(raiz);
                raiz->direita = removerNodo(raiz->direita, chave);
            }
            else
            {
                raiz = girarEsquerda(raiz);
                raiz->esquerda = removerNodo(raiz->esquerda, chave);
            }
        }
    }

    return raiz;
}

// Função para exibir a Treap de maneira hierárquica
void exibirTreap(NodoTreap *raiz, int profundidade)
{
    if (raiz == NULL)
        return;

    // Exibindo o filho à direita
    exibirTreap(raiz->direita, profundidade + 1);

    // Exibindo o nó atual com recuo baseado na profundidade
    for (int i = 0; i < profundidade; i++)
        printf("\t");

    printf("(%d, %d)\n", raiz->chave, raiz->prioridade);

    // Exibindo o filho à esquerda
    exibirTreap(raiz->esquerda, profundidade + 1);
}
