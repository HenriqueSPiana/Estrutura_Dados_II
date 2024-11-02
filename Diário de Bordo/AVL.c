#include <stdio.h>
#include <stdlib.h>

// Estrutura usada para criar a árvore AVL
struct No
{
  int valor;
  struct No *esq;
  struct No *dir;
  int altura;
};