#include "mpi.h"
#include <stdio.h>


int
main (int argc, char *argv)
{
        int rank, nproc, tipo = 777;
        MPI_Init (&argc, &argv);
        char msg[20];
        MPI_Status status;

        MPI_Comm_size (MPI_COMM_WORLD, &nproc);
        MPI_Comm_rank (MPI_COMM_WORLD, &rank);

        MPI_Recv (msg, 13, MPI_CHAR, 0, tipo, MPI_COMM_WORLD, &status);
        printf ("Proc %d recebendo mensagem: %.13s\n", rank, msg);
        MPI_Finalize ();
        return 0;
}
