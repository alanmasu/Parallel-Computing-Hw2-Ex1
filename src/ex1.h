#ifndef __EX1_H__
#define __EX1_H__
#include <stdint.h>

double randomD(int min, int max, int prec);
void populateMatrix(double *A, int n, int prec);
uint32_t matMul(double* A, double* B, double* __restrict C, int n);
uint32_t matMulPar(const double* A, const double* B, double* __restrict C, int n);


#endif // __EX1_H__
