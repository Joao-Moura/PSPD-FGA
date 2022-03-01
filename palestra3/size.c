#include "mpi.h"
#include <stdio.h>


int
main (int argc, char *argv)
{
        int rank, nproc;
        MPI_Init (&argc, &argv);

        MPI_Comm_size (MPI_COMM_WORLD, &nproc);
        MPI_Comm_rank (MPI_COMM_WORLD, &rank);

        printf("Hello World, processo %d de %d\n", rank, nproc);
        MPI_Finalize ();
        return 0;
}
