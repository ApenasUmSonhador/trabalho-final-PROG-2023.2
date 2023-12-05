#include <stdio.h>
#include <stdlib.h>
#include "logtree.h"

// Função auxiliar para calcular a média recursivamente
float _calcular_media(LogNode *node, int classe, int *soma, int *contador)
{
    if (node == NULL)
        return 0;

    float soma_esq = _calcular_media(node->esq, classe, soma, contador);
    float soma_dir = _calcular_media(node->dir, classe, soma, contador);

    if (node->classe == classe)
    {
        *soma += node->timer;
        (*contador)++;
    }

    return soma_esq + soma_dir + node->timer;
}

void log_registrar(Log **l, int conta, int classe, int timer, int caixa)
{
    _inserir_log_node(&(*l)->raiz, conta, classe, timer, caixa);
}

float log_media_por_classe(Log **l, int classe)
{
    int soma = 0;
    int contador = 0;
    float media = _calcular_media((*l)->raiz, classe, &soma, &contador);

    if (contador == 0)
        return 0;
    return soma / (float)contador;
}

// Função auxiliar para calcular a soma recursivamente
int _calcular_soma(LogNode *node, int classe)
{
    if (node == NULL)
        return 0;

    int soma_esq = _calcular_soma(node->esq, classe);
    int soma_dir = _calcular_soma(node->dir, classe);

    if (node->classe == classe)
        return soma_esq + soma_dir + node->timer;
    else
        return soma_esq + soma_dir;
}

int log_obter_soma_por_classe(Log **l, int classe)
{
    return _calcular_soma((*l)->raiz, classe);
}

int _contar_clientes(LogNode *node, int classe)
{
    if (node == NULL)
        return 0;

    int esq = _contar_clientes(node->esq, classe);
    int dir = _contar_clientes(node->dir, classe);

    if (node->classe == classe)
        return esq + dir + 1;
    else
        return esq + dir;
}

int log_obter_contagem_por_classe(Log **l, int classe)
{
    return _contar_clientes((*l)->raiz, classe);
}

// Função para liberar memória da árvore binária de busca
void _liberar_arvore(LogNode *node)
{
    if (node != NULL)
    {
        _liberar_arvore(node->esq);
        _liberar_arvore(node->dir);
        free(node);
    }
}

void log_destruir(Log **l)
{
    _liberar_arvore((*l)->raiz);
    free(*l);
    *l = NULL;
}