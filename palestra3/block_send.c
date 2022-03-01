#include "mpi.h"
#include <stdio.h>


int
main (int argc, char *argv)
{
        int rank, nproc, tipo = 777;
        MPI_Init (&argc, &argv);

        MPI_Comm_size (MPI_COMM_WORLD, &nproc);
        MPI_Comm_rank (MPI_COMM_WORLD, &rank);

        if (rank == 0) {
                char msg[13] = "Hello World\0";
                for (int i = 1; i < nproc; i++) {
                        /* Envia a mensagem para os processos indicados
                        Essa funcao bloqueia o fluxo */
                        MPI_Send (msg, 13, MPI_CHAR, i, tipo, MPI_COMM_WORLD);
                        printf ("Mensagem enviada\n");
                }
        }

        MPI_Finalize ();
        return 0;
}
