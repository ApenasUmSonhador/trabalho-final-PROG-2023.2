#include <stdio.h>
#include <stdlib.h>
#include "fila_fifo.h"

void f_inicializar(Fila_FIFO **f)
{
    *f = (Fila_FIFO *)malloc(sizeof(Fila_FIFO));
    (*f)->inicio = NULL;
    (*f)->fim = NULL;
    (*f)->tamanho = 0;
}

int f_inserir(Fila_FIFO **f, int chave, int valor)
{
    Node *novoNo = (Node *)malloc(sizeof(Node));
    if (novoNo == NULL)
        return 0; // Falha na alocação de memória

    novoNo->chave = chave;
    novoNo->valor = valor;
    novoNo->prox = NULL;

    if ((*f)->fim == NULL)
    {
        (*f)->inicio = novoNo;
    }
    else
    {
        (*f)->fim->prox = novoNo;
    }

    (*f)->fim = novoNo;
    (*f)->tamanho++;
    return 1; // Inserção bem sucedida
}

int f_obter_proxima_chave(Fila_FIFO **f)
{
    if ((*f)->inicio == NULL)
        return -1; // Fila vazia

    Node *temp = (*f)->inicio;
    int chave = temp->chave;
    (*f)->inicio = temp->prox;
    free(temp);

    if ((*f)->inicio == NULL)
        (*f)->fim = NULL;

    (*f)->tamanho--;
    return chave;
}

int f_consultar_proxima_chave(Fila_FIFO **f)
{
    if ((*f)->inicio == NULL)
        return -1; // Fila vazia

    return (*f)->inicio->chave;
}

int f_consultar_proximo_valor(Fila_FIFO **f)
{
    if ((*f)->inicio == NULL)
        return -1; // Fila vazia

    return (*f)->inicio->valor;
}

int f_num_elementos(Fila_FIFO **f)
{
    return (*f)->tamanho;
}

int f_consultar_chave_por_posicao(Fila_FIFO **f, int posicao)
{
    if (posicao < 1 || posicao > (*f)->tamanho || (*f)->inicio == NULL)
        return -1; // Posição inválida ou fila vazia

    Node *atual = (*f)->inicio;
    for (int i = 1; i < posicao; i++)
    {
        atual = atual->prox;
    }

    return atual->chave;
}

int f_consultar_valor_por_posicao(Fila_FIFO **f, int posicao)
{
    if (posicao < 1 || posicao > (*f)->tamanho || (*f)->inicio == NULL)
        return -1; // Posição inválida ou fila vazia

    Node *atual = (*f)->inicio;
    for (int i = 1; i < posicao; i++)
    {
        atual = atual->prox;
    }

    return atual->valor;
}

int f_consultar_proxima_chave(Fila_FIFO **f)
{
    if ((*f)->inicio == NULL)
        return -1; // Fila vazia

    return (*f)->inicio->chave;
}

int f_consultar_proximo_valor(Fila_FIFO **f)
{
    if ((*f)->inicio == NULL)
        return -1; // Fila vazia

    return (*f)->inicio->valor;
}

int f_num_elementos(Fila_FIFO **f)
{
    return (*f)->tamanho;
}

int f_consultar_chave_por_posicao(Fila_FIFO **f, int posicao)
{
    if (posicao < 1 || posicao > (*f)->tamanho || (*f)->inicio == NULL)
        return -1; // Posição inválida ou fila vazia

    Node *atual = (*f)->inicio;
    for (int i = 1; i < posicao; i++)
    {
        atual = atual->prox;
    }

    return atual->chave;
}

int f_consultar_valor_por_posicao(Fila_FIFO **f, int posicao)
{
    if (posicao < 1 || posicao > (*f)->tamanho || (*f)->inicio == NULL)
        return -1; // Posição inválida ou fila vazia

    Node *atual = (*f)->inicio;
    for (int i = 1; i < posicao; i++)
    {
        atual = atual->prox;
    }

    return atual->valor;
}

// Função para liberar memória da fila
void f_destruir(Fila_FIFO **f)
{
    Node *atual = (*f)->inicio;
    while (atual != NULL)
    {
        Node *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(*f);
    *f = NULL;
}