#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "lab1_b.h"


typedef struct {
        float result_1;
        float result_2;
} resps;


void
generate_vetor (vetor *argp, int tam, int inicio, int final)
{
        int tamanho_v = final - inicio;
        argp->vetor_len = tamanho_v;
        argp->vetor_val = malloc (sizeof (float) * tamanho_v);
        printf("[VETOR]: Criando vetor com Inicio = %d, final = %d e tamanho = %d\n", inicio, final, tamanho_v);

        for (int i = 0; i < tamanho_v; i++)
                argp->vetor_val[i] = ((inicio + i) - tam / 2);
}


resps
prog_10 (CLIENT *clnt, int tam, int inicio, int final)
{
	float *result_1;
	float *result_2;
	vetor vetor_arg;
        resps retorno;

        generate_vetor (&vetor_arg, tam, inicio, final);

        printf("[CLIENTE]: Comunicando com o servidor a funcao menor_10\n");
	result_1 = menor_10 (&vetor_arg, clnt);
	if (result_1 == (float *) NULL)
                clnt_perror (clnt, "Erro na chamada do RPC\n");
        printf("[SERVER]: O menor valor e: %f\n", *result_1);
        retorno.result_1 = *result_1;

        printf("[CLIENTE]: Comunicando com o servidor a funcao maior_10\n");
	result_2 = maior_10 (&vetor_arg, clnt);
	if (result_2 == (float *) NULL)
                clnt_perror (clnt, "Erro na chamada do RPC\n");
        printf("[SERVER]: O maior valor e: %f\n", *result_2);
        retorno.result_2 = *result_2;

        printf("[VETOR]: Liberando vetor...\n");
        free(vetor_arg.vetor_val);
        return retorno;
}


CLIENT *
create_server (char *host, char *proto)
{
        CLIENT *clnt;
        printf("[SERVER]: Criando server com host: %s\n", host);
	clnt = clnt_create (host, PROG, VERSAO, proto);
	if (clnt == (CLIENT *) NULL) {
		clnt_pcreateerror (host);
		exit (1);
        }
        return clnt;
}


void
validate_argv(int argc, char *argv[], int *qtdClnts, int *tam)
{
	if (argc < 4) {
		fprintf (stderr, "Uso correto: %s qtd_servers server_host tamanho_vetor\n", argv[0]);
		exit (1);
	}

        *qtdClnts = atoi (argv[1]);
        if (*qtdClnts <= 0) {
                fprintf (stderr, "qtd_servers deve ser inteiro maior que 0\n");
                exit (1);
        }

        if (argc < 3 + (*qtdClnts)) {
		fprintf (stderr, "Uso correto: %s qtd_servers [server_host] tamanho_vetor\n", argv[0]);
		exit (1);
        }

        *tam = atoi (argv[*qtdClnts + 2]);
        if (*tam <= 0) {
                fprintf (stderr, "tamanho_vetor deve ser inteiro maior que 0\n");
                exit (1);
        }
}


int
main (int argc, char *argv[])
{
        resps *respostas;
        int qtdClnts;
        int tam;

        validate_argv(argc, argv, &qtdClnts, &tam);
        respostas = malloc (sizeof (resps) * qtdClnts);

        int tam_por_server = tam / qtdClnts;
        for (int i = 0; i < qtdClnts; i++) {
                CLIENT *clnt;
                clnt = create_server (argv[i + 2], "tcp");
                int inicio = i * tam_por_server;
                int final;

                if (i + 1 < qtdClnts) final = inicio + tam_por_server;
                else final = inicio + tam_por_server + (tam % qtdClnts);

                resps resposta = prog_10 (clnt, tam, inicio, final);
                respostas[i] = resposta;
                clnt_destroy(clnt);
        }

        printf("\n\nMenor valor geral: %f.\nMaior valor geral: %f.\n", respostas[0].result_1, respostas[qtdClnts-1].result_2);
        exit (0);
}
