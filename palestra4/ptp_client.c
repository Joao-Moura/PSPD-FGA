#include "mpi.h"
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int
main (int argc, char *argv)
{
        int rank, tipo = 3;
        char msg[20];
        float timeUsed;
        struct timeval tempoInicio, tempoFinal;
        MPI_Status status;

        // Execucao bloqueante do programa
        MPI_Init (&argc, &argv);
        MPI_Comm_rank (MPI_COMM_WORLD, &rank);

        if (rank == 0) {
                // Clinte 0 -> Server 1 (Sincrona)
                printf ("[SYNC] Enviando mensagem...\n");
                strcpy(msg, "Hello World\0");
                MPI_Ssend (msg, 13, MPI_CHAR, 1, tipo, MPI_COMM_WORLD);
                printf ("[SYNC] Mensagem ja recebida\n");

                // Clinte 0 -> Server 2 (Ready)
                sleep(1);
                printf ("[READY] Enviando mensagem...\n");
                strcpy(msg, "Hello World\0");
                MPI_Rsend (msg, 13, MPI_CHAR, 2, tipo, MPI_COMM_WORLD);
                printf ("[READY] Mensagem ja recebida\n");

                // Clinte 0 -> Server 3 (Buffered)
                int buffer_size = 100 + MPI_BSEND_OVERHEAD;
                printf ("[BUF] Criando system buffer\n");
                MPI_Buffer_attach (malloc (buffer_size), buffer_size);

                printf ("[BUF] Enviando mensagem...\n");
                strcpy(msg, "Hello World\0");
                MPI_Bsend (msg, 13, MPI_CHAR, 3, tipo, MPI_COMM_WORLD);
                printf ("[BUF] Mensagem ja recebida\n");
        }

        else if (rank == 1) {
                sleep(1);
                printf ("[SYNC] Processo com recv iniciando\n");
                MPI_Recv (msg, 13, MPI_CHAR, 0, tipo, MPI_COMM_WORLD, &status);
                printf ("[SYNC] Mensagem %.13s recebida\n", msg);
        }

        else if (rank == 2) {
                printf ("[READY] Processo com recv iniciando\n");
                MPI_Recv (msg, 13, MPI_CHAR, 0, tipo, MPI_COMM_WORLD, &status);
                printf ("[READY] Mensagem %.13s recebida\n", msg);
        }

        else if (rank == 3) {
                printf ("[BUF] Processo com recv iniciando\n");
                MPI_Recv (msg, 13, MPI_CHAR, 0, tipo, MPI_COMM_WORLD, &status);
                printf ("[BUF] Mensagem %.13s recebida\n", msg);

                int tam;
                void *buffer = NULL;
                MPI_Buffer_detach (&buffer, &tam);
                printf ("[BUF] Removendo system buffer\n");
        }

        MPI_Finalize ();
        return 0;
}
