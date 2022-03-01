#include "mpi.h"
#include <stdio.h>
#include <string.h>


int
main (int argc, char *argv)
{
        int rank, nproc, tipo = 777;
        char msg[20];
        MPI_Status status;

        MPI_Init (&argc, &argv);
        MPI_Comm_size (MPI_COMM_WORLD, &nproc);
        MPI_Comm_rank (MPI_COMM_WORLD, &rank);

        if (rank == 0) {
                printf("Proc %d enviando mensagem\n", rank);
                strcpy(msg, "Hello World\0");
                for (int i = 1; i < nproc; i++) {
                        MPI_Send (msg, 13, MPI_CHAR, i, tipo, MPI_COMM_WORLD);
                        printf ("Mensagem BLOKANTE, mas foi recebida.\n");
                }
        }
        else {
                MPI_Recv (msg, 13, MPI_CHAR, 0, tipo, MPI_COMM_WORLD, &status);
                printf ("Proc %d recebendo mensagem: %.13s\n", rank, msg);
        }

        MPI_Finalize ();
        return 0;
}
