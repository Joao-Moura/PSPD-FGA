#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "info.h"


typedef struct {
        struct sockaddr_in infoServ; /* contem dados do servidor */
        int sd;        	             /* socket descriptor  */
} servidor_socket;


void
generate_vetor (vetor *argp, int tam, int inicio, int final)
{
        int tamanho_v = final - inicio;
        argp->vetor_len = tamanho_v;
        argp->vetor_val = malloc (sizeof (float) * tamanho_v);
        printf("[VETOR] => Criando vetor com Inicio = %d, final = %d e tamanho = %d\n", inicio, final, tamanho_v);

        for (int i = 0; i < tamanho_v; i++)
                argp->vetor_val[i] = ((inicio + i) - tam / 2);
}

void
validate_argv(int argc, char *argv[], int *qtdClnts, int *tam)
{
  	if (argc < 5) {
                fprintf (stderr, "Uso correto: %s <qtd_servers> <ip_do_servidor> <porta_do_servidor> <tam_vetor>\n", argv[0]);
                exit(1);
        }

        *qtdClnts = atoi (argv[1]);
        if (*qtdClnts <= 0) {
                fprintf (stderr, "qtd_servers deve ser inteiro maior que 0\n");
                exit (1);
        }

        if (argc < 3 + (*qtdClnts * 2)) {
		fprintf (stderr, "Uso correto: %s <qtd_servers> [<ip_do_servidor> <porta_do_servidor>] <tam_vetor>\n", argv[0]);
		exit (1);
        }

        *tam = atoi (argv[argc - 1]);
        if (*tam <= 0) {
                fprintf (stderr, "tamanho_vetor deve ser inteiro maior que 0\n");
                exit (1);
        }
}


int
main (int argc, char *argv[])
{
        // Estrutura de servidores
        servidor_socket *servers;

        // Estruturas temporarias
        struct sockaddr_in infoServ;
        float menor, maior;
        int sd;

        // Validacao dos dados de entrada
        int tam, qtdClnts;
        validate_argv (argc, argv, &qtdClnts, &tam);
        int tam_por_server = tam / qtdClnts;

        servers = malloc (sizeof (servidor_socket) * qtdClnts);

        // Loop para criacao e envio das infos nos sockets
        for (int i = 0; i < qtdClnts; i++) {
                infoServ = servers[i].infoServ;
                sd = servers[i].sd;
                
                // Configuracao de socket
                int servidor = 2 * (i + 1);
                infoServ.sin_family = AF_INET;
                infoServ.sin_addr.s_addr = inet_addr (argv[servidor]);
                infoServ.sin_port = htons (atoi (argv[servidor + 1]));

                // Criacao de socket
                sd = socket (AF_INET, SOCK_STREAM, 0);
                if (sd < 0) {
                        fprintf (stderr, "Criacao do socket falhou!\n");
                        exit(1);
                }

                // Conexao socket
                if (connect (sd, (struct sockaddr *) &infoServ, sizeof (infoServ)) < 0) {
                        fprintf (stderr, "Tentativa de conexao falhou!\n");
                        exit(1);
                }

                // Calculo de inicio e final do vetor
                int inicio = i * tam_por_server;
                int final;

                if (i + 1 < qtdClnts) final = inicio + tam_por_server;
                else final = inicio + tam_por_server + (tam % qtdClnts);

                int tmp = htonl(final - inicio);
                send (sd, &tmp, sizeof (tmp), 0);

                // Envia dados para os sockets ja conectados
                vetor bufout;
                generate_vetor (&bufout, tam, inicio, final);
                send (sd, bufout.vetor_val, sizeof (float) * bufout.vetor_len, 0);

                // Calcula o menor e o maior valor retornado
                float menorTmp, maiorTmp;
                recv (sd, &menorTmp, sizeof (float), 0);
                recv (sd, &maiorTmp, sizeof (float), 0);
                // printf("%f %f\n", menorTmp, maiorTmp);

                if (i == 0) menor = menorTmp;
                if (i == qtdClnts - 1) maior = maiorTmp;

                close (sd);
                free(bufout.vetor_val);
        }

        free(servers);
        printf("Menor valor: %f\nMaior valor: %f\n", menor, maior);
	return (0);
}
