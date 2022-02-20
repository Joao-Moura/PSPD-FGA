#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "info.h"


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


int
main (int argc, char *argv[])
{
	struct sockaddr_in infoServ; /* contem dados do servidor */
	int sd;          	     /* socket descriptor  */
	vetor bufout;                /* buffer de dados enviados  */
	
        // Validacao dos dados de entrada
  	if (argc < 4) {
                fprintf (stderr, "Uso correto: %s <ip_do_servidor> <porta_do_servidor> <tam_vetor>\n", argv[0]);
                exit(1);
        }

        // Configuracao de socket
	infoServ.sin_family = AF_INET;
	infoServ.sin_addr.s_addr = inet_addr (argv[1]);
	infoServ.sin_port = htons (atoi (argv[2]));

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

        // Envia dados para os sockets ja conectados
        int tam = atoi (argv[3]);
        generate_vetor (&bufout, tam, 0, tam);

        int tmp = htonl(bufout.vetor_len);
        send (sd, &tmp, sizeof (tmp), 0);

        for (int i = 0; i < bufout.vetor_len; i++)
            send (sd, &bufout.vetor_val[i], sizeof (float), 0);

        // Recebe resposta
        float menor, maior;
        recv (sd, &menor, sizeof (float), 0);
        recv (sd, &maior, sizeof (float), 0);

        printf("Menor valor: %f\nMaior valor: %f\n", menor, maior);

	close (sd);
	return (0);
}
