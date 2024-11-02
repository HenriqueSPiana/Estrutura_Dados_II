#include <stdio.h>
#include <stdlib.h>

struct No {
  int valor;
  struct No *esq;
  struct No *dir;
  int altura;
};

typedef struct No No;
int altura(No *no);
void atualizarAltura(No *no);
int fatorBalanceamento(No *no);
No* rotacaoSimplesDireita(No *no);
No* rotacaoSimplesEsquerda(No *no);
No* rotacaoDuplaDireita(No* no);
No* rotacaoDuplaEsquerda(No* no);
No* balancear(No *raiz);
No* criarArvore(int valor);
No* inserirNo(No *raiz, int valor);
No* pesquisarNo(No *raiz, int valor);
No* removerNo(No *raiz, int valor);
void imprimirNo(int valor, int b);
void imprimirArvore(No *raiz, int b);

int main(void) {
  No *raiz = criarArvore(10);
  raiz = inserirNo(raiz, 5);
  raiz = inserirNo(raiz, 6);
  raiz = inserirNo(raiz, 15);
  raiz = inserirNo(raiz, 13);

  imprimirArvore(raiz, 3);

  raiz = removerNo(raiz, 5);
  printf("\n");

  imprimirArvore(raiz, 3);

  return 0;
}

// Inicializa a árvore AVL com um nó raiz
No* criarArvore(int valor) {
  No *raiz = (No*)malloc(sizeof(No));
  if(raiz == NULL) {
    printf("Erro ao alocar memória.\n");
    exit(EXIT_FAILURE);
  }
  raiz->valor = valor;
  raiz->esq = raiz->dir = NULL;
  raiz->altura = 0;
  return raiz;
}

// Obtém a altura do nó, com ajuste de valor nulo
int altura(No *no) {
  return no == NULL ? -1 : no->altura;
}

// Define o fator de balanceamento do nó
int fatorBalanceamento(No *no) {
  return no == NULL ? 0 : altura(no->esq) - altura(no->dir);
}

// Atualiza a altura do nó após mudanças
void atualizarAltura(No *no) {
  int altEsq = altura(no->esq);
  int altDir = altura(no->dir);
  no->altura = (altEsq > altDir ? altEsq : altDir) + 1;
}

// Imprime o valor do nó com um deslocamento específico
void imprimirNo(int valor, int b) {
  for(int i = 0; i < b; i++)
    printf("   ");
  printf("%i\n", valor);
}

// Exibe a árvore no formato esquerda-raiz-direita
void imprimirArvore(No *raiz, int b) {
  if (raiz != NULL) {
    imprimirArvore(raiz->dir, b + 1);
    imprimirNo(raiz->valor, b);
    imprimirArvore(raiz->esq, b + 1);
  }
}

// Rotação simples à direita
No* rotacaoSimplesDireita(No *no) {
  No* y = no->esq;
  No* f = y->dir;

  y->dir = no;
  no->esq = f;

  atualizarAltura(no);
  atualizarAltura(y);

  return y;
}

// Rotação simples à esquerda
No* rotacaoSimplesEsquerda(No *no) {
  No* y = no->dir;
  No* f = y->esq;

  y->esq = no;
  no->dir = f;

  atualizarAltura(no);
  atualizarAltura(y);

  return y;
}

// Rotação dupla à direita
No* rotacaoDuplaDireita(No* no) {
  no->esq = rotacaoSimplesEsquerda(no->esq);
  return rotacaoSimplesDireita(no);
}

// Rotação dupla à esquerda
No* rotacaoDuplaEsquerda(No* no) {
  no->dir = rotacaoSimplesDireita(no->dir);
  return rotacaoSimplesEsquerda(no);
}

// Balanceamento de um nó específico na árvore
No* balancear(No *raiz) {
  int fb = fatorBalanceamento(raiz);

  if (fb > 1 && fatorBalanceamento(raiz->esq) >= 0)
    raiz = rotacaoSimplesDireita(raiz);
  else if (fb < -1 && fatorBalanceamento(raiz->dir) <= 0)
    raiz = rotacaoSimplesEsquerda(raiz);
  else if (fb > 1 && fatorBalanceamento(raiz->esq) < 0)
    raiz = rotacaoDuplaDireita(raiz);
  else if (fb < -1 && fatorBalanceamento(raiz->dir) > 0)
    raiz = rotacaoDuplaEsquerda(raiz);

  return raiz;
}

// Insere um novo nó na árvore AVL e a reequilibra
No* inserirNo(No *raiz, int valor) {
  if(raiz == NULL)
    return criarArvore(valor);

  if(valor < raiz->valor)
    raiz->esq = inserirNo(raiz->esq, valor);
  else if(valor > raiz->valor)
    raiz->dir = inserirNo(raiz->dir, valor);
  else
    printf("Valor já existe na árvore.\n");

  atualizarAltura(raiz);
  raiz = balancear(raiz);

  return raiz;
}

// Pesquisa um nó na árvore AVL
No* pesquisarNo(No *raiz, int valor) {
  if(raiz == NULL || raiz->valor == valor)
    return raiz;

  if(valor < raiz->valor)
    return pesquisarNo(raiz->esq, valor);
  else
    return pesquisarNo(raiz->dir, valor);
}

// Remove um nó da árvore AVL e a reequilibra
No* removerNo(No *raiz, int valor) {
  if(raiz == NULL)
    return NULL;

  if(valor < raiz->valor)
    raiz->esq = removerNo(raiz->esq, valor);
  else if(valor > raiz->valor)
    raiz->dir = removerNo(raiz->dir, valor);
  else {
    if(raiz->esq == NULL || raiz->dir == NULL) {
      No *temp = raiz->esq ? raiz->esq : raiz->dir;
      free(raiz);
      return temp;
    } else {
      No *temp = raiz->esq;
      while(temp->dir != NULL)
        temp = temp->dir;
      raiz->valor = temp->valor;
      raiz->esq = removerNo(raiz->esq, temp->valor);
    }
  }

  atualizarAltura(raiz);
  raiz = balancear(raiz);

  return raiz;
}
