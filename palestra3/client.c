#include "mpi.h"
#include <stdio.h>
#include <string.h>


int
main (int argc, char *argv)
{
        int rank, nproc, tipo = 777;
        MPI_Init (&argc, &argv);
        char msg[20];

        MPI_Comm_size (MPI_COMM_WORLD, &nproc);
        MPI_Comm_rank (MPI_COMM_WORLD, &rank);

        strcpy(msg, "Hello World\0");
        printf ("Proc %d eviando mensagem\n", rank);
        for (int i = 1; i < nproc; i++)
                MPI_Send (msg, 13, MPI_CHAR, i, tipo, MPI_COMM_WORLD);

        MPI_Finalize ();
        return 0;
}
