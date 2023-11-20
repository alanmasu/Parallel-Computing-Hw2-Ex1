#include "ex1.h"

#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
// #include <linux/time.h>

double randomD(int min, int max, int prec){ 
  prec = 10 * prec; 
  return (rand() % (max * prec - min * prec + 1) + min * prec) / (double)prec; 
}

void populateMatrix(double *A, int n, int prec){
  for(int i = 0; i < n*n; i++){
    A[i] = randomD(0, 100, prec);
  }
}

uint32_t matMul(double* A, double* B, double* __restrict C, int n){
    int r, c, k;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(r = 0; r < n; r++){
        for(c = 0; c < n; c++){
            double sum = 0;
            for(k = 0; k < n; k++){
                sum += A[r*n + k] * B[k*n + c];
            }
            C[r*n + c] = sum;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
}