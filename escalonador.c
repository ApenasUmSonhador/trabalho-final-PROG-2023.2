#include <stdio.h>
#include <stdlib.h>
#include "escalonador.h"

int e_consultar_prox_fila(Escalonador *e);

void e_inicializar(Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5)
{
    e->caixas = caixas;
    e->delta_t = delta_t;
    e->n_1 = n_1;
    e->n_2 = n_2;
    e->n_3 = n_3;
    e->n_4 = n_4;
    e->n_5 = n_5;

    // Inicialize as cinco filas
    for (int i = 0; i < 5; i++)
    {
        f_inicializar(&(e->filas[i]));
    }
}

int e_inserir_por_fila(Escalonador *e, int classe, int num_conta, int qtde_operacoes)
{
    return f_inserir(&(e->filas[classe - 1]), num_conta, qtde_operacoes);
}

int e_obter_prox_num_conta(Escalonador *e)
{
    int prox_fila = e_consultar_prox_fila(e);

    if (prox_fila == -1)
        return -1; // Não há clientes para atender

    return f_obter_proxima_chave(&(e->filas[prox_fila]));
}
int e_consultar_prox_num_conta(Escalonador *e)
{
    int prox_fila = e_consultar_prox_fila(e);

    if (prox_fila == -1)
        return -1; // Não há clientes para atender

    return f_consultar_proxima_chave(&(e->filas[prox_fila]));
}

int e_consultar_prox_qtde_oper(Escalonador *e)
{
    int prox_fila = e_consultar_prox_fila(e);

    if (prox_fila == -1)
        return -1; // Não há clientes para atender

    return f_consultar_proximo_valor(&(e->filas[prox_fila]));
}

int e_consultar_prox_fila(Escalonador *e)
{
    if (f_num_elementos(&(e->filas[0])) > 0)
        return 0;
    if (f_num_elementos(&(e->filas[1])) > 0)
        return 1;
    if (f_num_elementos(&(e->filas[2])) > 0)
        return 2;
    if (f_num_elementos(&(e->filas[3])) > 0)
        return 3;
    if (f_num_elementos(&(e->filas[4])) > 0)
        return 4;

    return -1; // Todas as filas estão vazias
}

int e_consultar_qtde_clientes(Escalonador *e)
{
    int total_clientes = 0;
    for (int i = 0; i < 5; i++)
    {
        total_clientes += f_num_elementos(&(e->filas[i]));
    }
    return total_clientes;
}

int e_consultar_tempo_prox_cliente(Escalonador *e)
{
    int prox_fila = e_consultar_prox_fila(e);

    if (prox_fila == -1)
        return -1; // Não há clientes para atender

    int qtde_oper = f_consultar_proximo_valor(&(e->filas[prox_fila]));
    return qtde_oper * e->delta_t;
}

int e_conf_por_arquivo(Escalonador *e, char *nome_arq_conf)
{
    FILE *arq_conf = fopen(nome_arq_conf, "r");
    if (arq_conf == NULL)
    {
        perror("Erro ao abrir o arquivo de configuração");
        return 0;
    }

    // Lógica para ler o arquivo de configuração e configurar o escalonador
    fscanf(arq_conf, "%d %d %d %d %d %d %d %d",
           &e->caixas, &e->delta_t, &e->n_1, &e->n_2, &e->n_3, &e->n_4, &e->n_5);

    fclose(arq_conf);
    return 1; // Retorna 1 em caso de sucesso
}

typedef struct
{
    int num_conta;
    int qtde_operacoes;
} Cliente;

void atender_cliente(Escalonador *e, FILE *arq_out, int caixa, Cliente cliente)
{
    fprintf(arq_out, "Caixa %d vai atender o cliente de número de conta %d.\n", caixa, cliente.num_conta);
    fprintf(arq_out, "Número de conta: %d\n", cliente.num_conta);
    fprintf(arq_out, "Quantidade de operações: %d\n", cliente.qtde_operacoes);
    fprintf(arq_out, "Tempo para atendimento: %d minutos\n", cliente.qtde_operacoes * e->delta_t);
    fprintf(arq_out, "Tempo de espera: %d minutos\n\n", (cliente.num_conta - 1) * e->delta_t); // Suposição simples de tempo de espera

    int tempo_servico = cliente.qtde_operacoes * e->delta_t;
    // Simulação de atendimento: aguarda o tempo necessário para o atendimento do cliente
    for (int tempo = 0; tempo < tempo_servico; tempo++)
    {
        fprintf(arq_out, "Tempo decorrido de atendimento: %d minutos\n", tempo);
        // Aqui, poderiam ser realizadas operações durante o atendimento do cliente
    }
    fprintf(arq_out, "Cliente de número de conta %d foi atendido.\n\n", cliente.num_conta);
}

void e_rodar(Escalonador *e, char *nome_arq_in, char *nome_arq_out)
{
    FILE *arq_in = fopen(nome_arq_in, "r");
    FILE *arq_out = fopen(nome_arq_out, "w");
    if (arq_in == NULL || arq_out == NULL)
    {
        perror("Erro ao abrir arquivo de entrada ou saída");
        return;
    }

    // Lógica para executar a simulação do atendimento
    int caixa_disponivel = 1; // Caixas numerados de 1 a e->caixas
    Cliente cliente;
    while (fscanf(arq_in, "%d %d", &cliente.num_conta, &cliente.qtde_operacoes) == 2)
    {
        atender_cliente(e, arq_out, caixa_disponivel, cliente);
        caixa_disponivel = (caixa_disponivel % e->caixas) + 1; // Avança para o próximo caixa (cíclico)
    }

    fclose(arq_in);
    fclose(arq_out);
}