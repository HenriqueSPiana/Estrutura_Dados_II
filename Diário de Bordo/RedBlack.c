#include <stdio.h>
#include <stdlib.h>

#define COR_PRETA 0
#define COR_VERMELHA 1

// Estrutura do Nó na Árvore Rubro-Negra
typedef struct Nodo {
    int valor;
    struct Nodo *esquerda;
    struct Nodo *direita;
    int cor;
} Nodo;

// Declaração das funções de manipulação da árvore
int obterCor(Nodo *no);
void inverterCor(Nodo *no);
Nodo* girarEsquerda(Nodo *no);
Nodo* girarDireita(Nodo *no);
Nodo* inicializarArvore(int valor);
Nodo* adicionar(Nodo* raiz, int valor);
Nodo* adicionarNodo(Nodo *raiz, int valor);
Nodo* deletar(Nodo *raiz, int valor);
Nodo* deletarNodo(Nodo *raiz, int valor);
Nodo* ajustarEsq(Nodo *no);
Nodo* ajustarDir(Nodo *no);
Nodo* ajustarBalanceamento(Nodo *no);
Nodo* buscarMenor(Nodo *raiz);
Nodo* removerMenor(Nodo *raiz);
void exibirArvore(Nodo *raiz, int profundidade);

int main(void) {
    Nodo *raiz = inicializarArvore(10);
    raiz = adicionar(raiz, 5);
    raiz = adicionar(raiz, 6);
    raiz = adicionar(raiz, 15);
    raiz = adicionar(raiz, 13);

    exibirArvore(raiz, 3);

    raiz = deletar(raiz, 5);
    printf("\n");
    
    exibirArvore(raiz, 3);
    
    return 0;
}

// Função para criar uma árvore rubro-negra inicial
Nodo* inicializarArvore(int valor) {
    Nodo *raiz = (Nodo*)malloc(sizeof(Nodo));
    if (raiz == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    raiz->valor = valor;
    raiz->direita = NULL;
    raiz->esquerda = NULL;
    raiz->cor = COR_VERMELHA;

    return raiz;
}

// Função para verificar a cor do nó
int obterCor(Nodo *no) {
    return (no == NULL) ? COR_PRETA : no->cor;
}

// Função para alternar a cor do nó
void inverterCor(Nodo *no) {
    no->cor = !no->cor;
    if (no->esquerda != NULL) no->esquerda->cor = !no->esquerda->cor;
    if (no->direita != NULL) no->direita->cor = !no->direita->cor;
}

// Rotação para a esquerda na subárvore
Nodo* girarEsquerda(Nodo *no) {
    Nodo *x = no->direita;
    no->direita = x->esquerda;
    x->esquerda = no;
    x->cor = no->cor;
    no->cor = COR_VERMELHA;
    return x;
}

// Rotação para a direita na subárvore
Nodo* girarDireita(Nodo *no) {
    Nodo *x = no->esquerda;
    no->esquerda = x->direita;
    x->direita = no;
    x->cor = no->cor;
    no->cor = COR_VERMELHA;
    return x;
}

// Função para movimentar o nó vermelho à esquerda
Nodo* ajustarEsq(Nodo *no) {
    inverterCor(no);
    if (obterCor(no->direita->esquerda) == COR_VERMELHA) {
        no->direita = girarDireita(no->direita);
        no = girarEsquerda(no);
        inverterCor(no);
    }
    return no;
}

// Função para movimentar o nó vermelho à direita
Nodo* ajustarDir(Nodo *no) {
    inverterCor(no);
    if (obterCor(no->esquerda->esquerda) == COR_VERMELHA) {
        no = girarDireita(no);
        inverterCor(no);
    }
    return no;
}

// Função de balanceamento da árvore
Nodo* ajustarBalanceamento(Nodo *no) {
    if (obterCor(no->direita) == COR_VERMELHA) no = girarEsquerda(no);
    if (obterCor(no->esquerda) == COR_VERMELHA && obterCor(no->esquerda->esquerda) == COR_VERMELHA) no = girarDireita(no);
    if (obterCor(no->esquerda) == COR_VERMELHA && obterCor(no->direita) == COR_VERMELHA) inverterCor(no);

    return no;
}

Nodo* adicionar(Nodo* raiz, int valor) {
    raiz = adicionarNodo(raiz, valor);
    if (raiz != NULL) raiz->cor = COR_PRETA;
    return raiz;
}

// Inserção de um novo nó na árvore
Nodo* adicionarNodo(Nodo *raiz, int valor) {
    if (raiz == NULL) return inicializarArvore(valor);

    if (valor < raiz->valor) raiz->esquerda = adicionarNodo(raiz->esquerda, valor);
    else if (valor > raiz->valor) raiz->direita = adicionarNodo(raiz->direita, valor);

    if (obterCor(raiz->direita) == COR_VERMELHA && obterCor(raiz->esquerda) == COR_PRETA) raiz = girarEsquerda(raiz);
    if (obterCor(raiz->esquerda) == COR_VERMELHA && obterCor(raiz->esquerda->esquerda) == COR_VERMELHA) raiz = girarDireita(raiz);
    if (obterCor(raiz->esquerda) == COR_VERMELHA && obterCor(raiz->direita) == COR_VERMELHA) inverterCor(raiz);

    return raiz;
}

Nodo* deletar(Nodo* raiz, int valor) {
    raiz = deletarNodo(raiz, valor);
    if (raiz != NULL) raiz->cor = COR_PRETA;
    return raiz;
}

// Remoção de um nó específico
Nodo* deletarNodo(Nodo *raiz, int valor) {
    if (valor < raiz->valor) {
        if (obterCor(raiz->esquerda) == COR_PRETA && obterCor(raiz->esquerda->esquerda) == COR_PRETA) raiz = ajustarEsq(raiz);
        raiz->esquerda = deletarNodo(raiz->esquerda, valor);
    } else {
        if (obterCor(raiz->esquerda) == COR_VERMELHA) raiz = girarDireita(raiz);
        if (valor == raiz->valor && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }
        if (obterCor(raiz->direita) == COR_PRETA && obterCor(raiz->direita->esquerda) == COR_PRETA) raiz = ajustarDir(raiz);
        if (valor == raiz->valor) {
            Nodo* menor = buscarMenor(raiz->direita);
            raiz->valor = menor->valor;
            raiz->direita = removerMenor(raiz->direita);
        } else {
            raiz->direita = deletarNodo(raiz->direita, valor);
        }
    }
    return ajustarBalanceamento(raiz);
}

Nodo* buscarMenor(Nodo *raiz) {
    if (raiz->esquerda == NULL) return raiz;
    return buscarMenor(raiz->esquerda);
}

Nodo* removerMenor(Nodo *raiz) {
    if (raiz->esquerda == NULL) {
        free(raiz);
        return NULL;
    }
    if (obterCor(raiz->esquerda) == COR_PRETA && obterCor(raiz->esquerda->esquerda) == COR_PRETA) raiz = ajustarEsq(raiz);
    raiz->esquerda = removerMenor(raiz->esquerda);
    return ajustarBalanceamento(raiz);
}

void exibirArvore(Nodo *raiz, int profundidade) {
    if (raiz != NULL) {
        exibirArvore(raiz->direita, profundidade + 1);
        for (int i = 0; i < profundidade; i++) printf("       ");
        if (raiz->cor == COR_VERMELHA)
            printf("\033[31m%d\033[0m\n\n", raiz->valor);
        else
            printf("%d\n\n", raiz->valor);
        exibirArvore(raiz->esquerda, profundidade + 1);
    }
}
