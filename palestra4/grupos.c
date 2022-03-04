#include <mpi.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_GROUP_SIZE 8


int
main (int argc, char *argv)
{
        int world_rank, world_nproc;
        int g1_rank = -1, g1_nproc = -1;
        int g2_rank = -1, g2_nproc = -1;

        int g1_ranks[MAX_GROUP_SIZE] = {0, 2};
        int g2_ranks[MAX_GROUP_SIZE] = {1, 3};

        MPI_Group world_group, g1_group, g2_group;
        MPI_Comm g1_comm, g2_comm;
        MPI_Status status;

        MPI_Init (&argc, &argv);
        MPI_Comm_rank (MPI_COMM_WORLD, &world_rank);
        MPI_Comm_size (MPI_COMM_WORLD, &world_nproc);

        MPI_Comm_group (MPI_COMM_WORLD, &world_group);
        MPI_Group_incl (world_group, 2, g1_ranks, &g1_group);
        MPI_Group_incl (world_group, 2, g2_ranks, &g2_group);

        MPI_Comm_create_group (MPI_COMM_WORLD, g1_group, 1, &g1_comm);
        MPI_Comm_create_group (MPI_COMM_WORLD, g2_group, 2, &g2_comm);

        if (g1_comm != MPI_COMM_NULL) {
                MPI_Comm_rank (g1_comm, &g1_rank);
                MPI_Comm_size (g1_comm, &g1_nproc);
        }

        if (g2_comm != MPI_COMM_NULL) {
                MPI_Comm_rank (g2_comm, &g2_rank);
                MPI_Comm_size (g2_comm, &g2_nproc);
        }

        int valores[10];
        if (g1_rank == 0) {
                printf ("[G1] Digite as sequencias de numeros para serem enviados no grupo 1\n");
                for (int i = 0; i < 10; i++)
                        scanf ("%d", &valores[i]);
                MPI_Ssend (valores, 10, MPI_INT, 1, 10, g1_comm);
                printf ("[G1] Mensagem finalmente enviada\n");
        }

        else if (g1_rank == 1) {
                printf ("[G1] Processo 1 do grupo 1 dormindo ...\n");
                sleep(2);
                MPI_Recv (valores, 10, MPI_INT, 0, 10, g1_comm, &status);
                printf ("[G1] Vetor recebido: %d", valores[0]);
                for (int i = 1; i < 10; i++)
                        printf (", %d", valores[i]);
                printf ("\n");
        }

        char msg[20];
        if (g2_rank == 0) {
                strcpy(msg, "Hello World G2\0");
                printf ("[G2] Proc %d enviando mensagem broadcast\n", g2_rank);
        }

        if (g2_comm != MPI_COMM_NULL) {
                MPI_Barrier (g2_comm);
                MPI_Bcast (msg, 15, MPI_CHAR, 0, g2_comm);
                printf ("[G2] Proc %d recebeu a mensagem: %s\n", g2_rank, msg);
        }
        
        if (g1_comm != MPI_COMM_NULL) {
                printf ("[G1] Proc %d recebeu a mensagem: %s\n", g1_rank, msg);
        }

        MPI_Finalize ();
        return 0;
}
