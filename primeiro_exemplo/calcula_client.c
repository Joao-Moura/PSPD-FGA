#include <stdio.h>
#include "calcula.h"

int add
(CLIENT *clnt, int x, int y)
{
    operandos ops;
    int *result;

    ops.x = x; ops.y =y;
    result = add_100 (&ops, clnt);
    if (result == NULL) {
        fprintf(stderr, "Problemas na chamada do RPC\n");
        exit (0);
    }

    return (*result);
} /* fim funcao add */

int sub
(CLIENT *clnt, int x, int y)
{
    operandos ops;
    int *result;

    ops.x = x; ops.y =y;
    result = sub_100 (&ops, clnt);
    if (result == NULL) {
        fprintf(stderr, "Problemas na chamada do RPC\n");
        exit (0);
    }

    return (*result);
} /* fim funcao sub */

int main
(int argc, char *argv[])
{
    CLIENT *clnt;
    int x,y;

    if (argc != 4) {
        fprintf(stderr,"Uso correto: %s hostname num1 num2\n", argv[0]);
        exit (0);
    }

    clnt = clnt_create(argv[1], PROG, VERSAO, "udp");
    if (clnt == (CLIENT *) NULL) {
        clnt_pcreateerror (argv[1]);
        exit (1);
    }

    /* Recupera os 2 operandos passados como argumento */
    x = atoi (argv[2]); y = atoi (argv[3]);
    printf("%d + %d = %d\n", x, y, add (clnt, x, y));
    printf("%d - %d = %d\n", x, y, sub (clnt, x, y));
    return (0);
} /* fim main */
