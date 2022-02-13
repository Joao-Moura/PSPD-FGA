#include <stdio.h>
#include "lab1_a.h"


void
print_vetor (vetor *argp)
{
        printf("%f", argp->vetor_val[0]);
        for (int i = 1; i < argp->vetor_len; i++)
            printf(", %f", argp->vetor_val[i]);
        printf("\n");
}


float *
menor_10_svc (vetor *argp, struct svc_req *rqstp)
{
	static float result;
        
        result = argp->vetor_val[0];
	return &result;
}


float *
maior_10_svc (vetor *argp, struct svc_req *rqstp)
{
	static float result;

        result = argp->vetor_val[argp->vetor_len - 1];
	return &result;
}
