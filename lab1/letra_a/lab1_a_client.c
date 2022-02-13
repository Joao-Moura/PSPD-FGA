#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "lab1_a.h"


void
generate_vetor (vetor *argp, int tam)
{
        argp->vetor_len = tam;
        argp->vetor_val = malloc (sizeof (float) * tam);

        for (int i = 0; i < tam; i++)
                argp->vetor_val[i] = (i - tam / 2);
}


void
prog_10 (CLIENT *clnt, int tam)
{
	float  *result_1;
	float  *result_2;
	vetor  vetor_arg;

        generate_vetor (&vetor_arg, tam);

	result_1 = menor_10 (&vetor_arg, clnt);
	if (result_1 == (float *) NULL)
                clnt_perror (clnt, "Erro na chamada do RPC\n");
        printf("O menor valor e: %f\n", *result_1);

	result_2 = maior_10 (&vetor_arg, clnt);
	if (result_2 == (float *) NULL)
                clnt_perror (clnt, "Erro na chamada do RPC\n");
        printf("O maior valor e: %f\n", *result_2);
}


int
main (int argc, char *argv[])
{
        CLIENT *clnt;
        int tam;

	if (argc < 3) {
		fprintf (stderr, "Uso correto: %s server_host tamanho_vetor\n", argv[0]);
		exit (1);
	}

        /* Cria servidor tcp */
	clnt = clnt_create (argv[1], PROG, VERSAO, "tcp");
	if (clnt == (CLIENT *) NULL) {
		clnt_pcreateerror (argv[1]);
		exit (1);
        }

        tam = atoi (argv[2]);
        if (tam <= 0) {
                fprintf (stderr, "tamanho_vetor deve ser inteiro maior que 0\n");
                exit (1);
        }

	prog_10 (clnt, (u_int) tam);
        clnt_destroy(clnt);
        exit (0);
}
