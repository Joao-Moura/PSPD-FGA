#include <stdio.h>
#include "lab1_b.h"


float *
menor_10_svc (vetor *argp, struct svc_req *rqstp)
{
	static float result;
        printf("[CLIENTE]: Chamada em menor_10_svc\n");
        
        result = argp->vetor_val[0];
	return &result;
}


float *
maior_10_svc (vetor *argp, struct svc_req *rqstp)
{
	static float result;
        printf("[CLIENTE]: Chamada em maior_10_svc\n");

        result = argp->vetor_val[argp->vetor_len - 1];
	return &result;
}
