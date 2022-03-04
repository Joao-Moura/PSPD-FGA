#include <mpi.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LINHA 10
#define COLUNA 10


int
main (int argc, char *argv)
{
        int rank, nproc, root = 0, total;
        int linha[COLUNA], vec[LINHA * COLUNA];
        int maior_total;

        MPI_Init (&argc, &argv);
        MPI_Comm_rank (MPI_COMM_WORLD, &rank);
        MPI_Comm_size (MPI_COMM_WORLD, &nproc);

        int linhas = nproc, colunas = 6;

        if (rank == 0) {
                for (int i = 0; i < colunas; i++)
                        for (int j = 0; j < linhas; j++)
                                scanf ("%d", &vec[i * linhas + j]);
        }
        
        MPI_Barrier (MPI_COMM_WORLD);
        MPI_Scatter (vec, colunas, MPI_INT, linha, colunas, MPI_INT, root, MPI_COMM_WORLD);

        for (int i = 0; i < nproc; i++) {
                if (rank == i) {
                        printf ("Valores recebidos no proc %d -> %d", rank, linha[0]);
                        total = linha[0];
                        for (int j = 1; j < colunas; j++) {
                                printf (", %d", linha[j]);
                                total += linha[j];
                        }
                        printf ("\n");
                }
        }

        MPI_Barrier (MPI_COMM_WORLD);
        MPI_Reduce (&total, &maior_total, 1, MPI_INT, MPI_MAX, root, MPI_COMM_WORLD);

        if (rank == 0)
                printf ("\nLinha com o maior total: %d\n", maior_total);

        MPI_Finalize ();
        return 0;
}
