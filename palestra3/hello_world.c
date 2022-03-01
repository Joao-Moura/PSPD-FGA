#include "mpi.h"
#include <stdio.h>


int
main (int argc, char *argv)
{
        /* Inicia o ambiente MPI para uso.
        Primeiro comando a ser chamado */
        MPI_Init (&argc, &argv);
        printf("Hello World\n");

        /* Finaliza o ambiente MPI. Ultima rotina chamada
        e deve ser feita apenas se não existir mais nenhuma
        comunicacao entre processos */
        MPI_Finalize ();
        return 0;
}
