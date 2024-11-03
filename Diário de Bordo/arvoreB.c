#include <stdio.h>
#include <stdlib.h>

#define GRAU 4
#define FALSO 0
#define VERDADEIRO 1

// Estrutura do nó da árvore B
struct NoB
{
    int n;                    // Número de chaves atualmente no nó
    int chaves[GRAU - 1];     // Chaves armazenadas no nó
    struct NoB *filhos[GRAU]; // Ponteiros para os filhos do nó
    int folha;                // Se é uma folha ou não
};

typedef struct NoB NoB;
NoB *criarNo(int folha);
void dividirFilho(NoB *no, int pos);
void inserirNoNaoCheio(NoB *no, int chave);
NoB *inserirNo(NoB *raiz, int chave);
void imprimirArvoreB(NoB *no);

int main(void)
{
    NoB *raiz = NULL;
    raiz = inserirNo(raiz, 10);
    raiz = inserirNo(raiz, 5);
    raiz = inserirNo(raiz, 6);
    raiz = inserirNo(raiz, 15);
    raiz = inserirNo(raiz, 13);

    printf("Árvore B:\n");
    imprimirArvoreB(raiz);

    return 0;
}

// Função para criar um novo nó da árvore B
NoB *criarNo(int folha)
{
    NoB *no = (NoB *)malloc(sizeof(NoB));
    if (no == NULL)
    {
        printf("Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    no->n = 0;
    no->folha = folha;
    for (int i = 0; i < GRAU; i++)
        no->filhos[i] = NULL;
    return no;
}

// Função que divide um nó filho ao atingir o número máximo de chaves
void dividirFilho(NoB *no, int pos)
{
    NoB *filho = no->filhos[pos];         // Filho que será dividido
    NoB *novoFilho = criarNo(filho->folha); // Novo nó para metade das chaves
    novoFilho->n = GRAU / 2 - 1;

    for (int i = 0; i < GRAU / 2 - 1; i++)
        novoFilho->chaves[i] = filho->chaves[i + GRAU / 2];

    if (filho->folha == FALSO)
    {
        for (int i = 0; i < GRAU / 2; i++)
            novoFilho->filhos[i] = filho->filhos[i + GRAU / 2];
    }

    filho->n = GRAU / 2 - 1;

    for (int i = no->n; i >= pos + 1; i--)
        no->filhos[i + 1] = no->filhos[i];

    no->filhos[pos + 1] = novoFilho;

    for (int i = no->n - 1; i >= pos; i--)
        no->chaves[i + 1] = no->chaves[i];

    no->chaves[pos] = filho->chaves[GRAU / 2 - 1];
    no->n++;
}

// Função para inserir uma chave em um nó que não está cheio
void inserirNoNaoCheio(NoB *no, int chave)
{
    int i = no->n - 1;

    if (no->folha == VERDADEIRO)
    {
        while (i >= 0 && no->chaves[i] > chave)
        {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->n++;
    }
    else
    {
        while (i >= 0 && no->chaves[i] > chave)
            i--;

        i++;
        if (no->filhos[i]->n == GRAU - 1)
        {
            dividirFilho(no, i);
            if (no->chaves[i] < chave)
                i++;
        }
        inserirNoNaoCheio(no->filhos[i], chave);
    }
}

// Função para inserir uma nova chave na árvore B
NoB *inserirNo(NoB *raiz, int chave)
{
    if (raiz == NULL)
    {
        raiz = criarNo(VERDADEIRO);
        raiz->chaves[0] = chave;
        raiz->n = 1;
        return raiz;
    }

    if (raiz->n == GRAU - 1)
    {
        NoB *novaRaiz = criarNo(FALSO);
        novaRaiz->filhos[0] = raiz;
        dividirFilho(novaRaiz, 0);
        raiz = novaRaiz;
    }
    inserirNoNaoCheio(raiz, chave);

    return raiz;
}

// Função para imprimir a árvore B em ordem
void imprimirArvoreB(NoB *no)
{
    if (no != NULL)
    {
        int i;
        for (i = 0; i < no->n; i++)
        {
            imprimirArvoreB(no->filhos[i]);
            printf("%d ", no->chaves[i]);
        }
        imprimirArvoreB(no->filhos[i]);
    }
}
