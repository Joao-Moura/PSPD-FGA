#include "mpi.h"
#include <stdio.h>


int
main (int argc, char *argv)
{
        int rank;
        MPI_Init (&argc, &argv);

        // Identifica o processo do grupo de processos em execucao
        MPI_Comm_rank (MPI_COMM_WORLD, &rank);

        printf("Hello World, processo: %d\n", rank);
        MPI_Finalize ();
        return 0;
}
