/*                      INTRODUCTION TO PARALLEL COMPUTING - Prof. VELLA 

    Student: Alan Masutti - 226901 - alan.masutti@studenti.unitn.it

    Assignment 2 - Exercise 1:
      The first exercise consists of implementing a parallel matrix multiplication program using OpenMP.
      The program must be able to handle efficiently both dense and sparse matrices of real numbers. The
      tasks to be performed are:
      - T1: Serial matrix multiplication:
            Implement a serial matrix multiplication algorithm. You will need to define a matMul function
            that takes two input matrices, A and B, and returns their product, C. Be sure to validate the
            compatibility of the matrices for multiplication.
      - T2: Parallel matrix multiplication:
            Parallelize matrix multiplication using OpenMP. Create a matMulPar function that takes the
            same inputs as the sequential version and parallelizes the algorithm. Experiment with different
            OpenMP directives to improve performance. Explore different parallelization strategies to find
            the most efficient implementation.
      - T3: Performance analysis:
            Evaluate the performance and scalability of your parallel implementation of matrix multiplication. Calculate speedup and efficiency gains for different matrix sizes and number of threads.
            Consider for this task the time of the routine and compute the FLOPS as performance metrics. Identify potential bottlenecks or problems and propose optimizations to help
            solve them.

    Notes:

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <omp.h>

#include "ex1.h"

#ifndef COMPILATION_NOTES
    #define COMPILATION_NOTES ""
#endif

#define RUN_NOTES "serial"
#define RUN_DESCRIPTION "Serial matrix multiplication"

int main(int argc, char const *argv[]){
  char hostbuffer[256] = "";
  int hostname;
  uint32_t n, bs;

  //Retriving some info about the machine
  // retrieve hostname
  hostname = gethostname(hostbuffer, sizeof(hostbuffer));
  if (hostname == -1) {
    printf("Error when getting hostname\n");
  }

  //Save running information:
  FILE *infoFile = fopen("./results/infoFile.csv", "r");
  if(infoFile == NULL){
    #ifdef PRINT  
      printf("Creating infoFile.csv file\n");
    #endif
    infoFile = fopen("./results/infoFile.csv", "w");
    //hostname,run_notes,run_description,compilation_time,compilation_date
    fprintf(infoFile, "%s,%s,%s,%s,%s\n", hostbuffer, RUN_NOTES, RUN_DESCRIPTION,__TIME__, __DATE__);
    fclose(infoFile);
  }    

  //opening file to write results
  FILE *matMulFile = fopen("./results/matMulFile.csv", "r");
  if(matMulFile == NULL){
    #ifdef PRINT  
      printf("Creating matMulFile.csv file\n");
    #endif
    matMulFile = fopen("./results/matMulFile.csv", "w");
    if(matMulFile == NULL){
      printf("Error when opening matMulFile.csv file\n");
      exit(1);
    }
    fprintf(matMulFile, "matrix_size,matMul_wallTime[us],matMulPar_wallTime[us],hostname,compilation_notes,run_notes\n");
  }else{
    fclose(matMulFile);
    matMulFile = fopen("./results/matMulFile.csv", "a");
  }

  //getting sizes from command line
#ifndef N
  do{
    printf("Insert matrix size: ");
    scanf("%d", &n);
  }while(n <= 0);
#else
  n = N;
#endif

  //Execution of the serial matrix multiplication
#ifdef PRINT
  printf("Doing serial matrix multiplication\n");
#endif
  double *A = (double *)malloc(n*n*sizeof(double));
  double *B = (double *)malloc(n*n*sizeof(double));
  double *C = (double *)malloc(n*n*sizeof(double));

  if(A == NULL || B == NULL || C == NULL){
    printf("Error when allocating memory\n");
    return (-1);
  }

  //Populate matrices
  for(int i = 0; i < n*n; i++){
    A[i] = i;
    B[i] = i;
  }


#ifdef DEBUG
  //Print matrices
  for(int r = 0; r < n; r++){
    for(int ca = 0; ca < n; ca++){
      printf("%f\t", A[r*n + ca]);
    }
    printf("\t\t");
    for(int cb = 0; cb < n; cb++){
      printf("%f\t", B[r*n + cb]);
    }
    printf("\n");
  }
#endif

  //Execution of the serial matrix multiplication
  uint64_t time = matMul(A, B, C, n);
#ifdef PRINT
  printf("serial matrix multiplication done. Wall Time: \t%ld us\n", time); 
#endif

#ifdef DEBUG
  //Print result matrix
  for(int r = 0; r < n; r++){
    for(int c = 0; c < n; c++){
      printf("%f\t", C[r*n + c]);
    }
    printf("\n");
  }
#endif

  //Execution of the parallel matrix multiplication
// #ifdef PRINT
//   printf("Doing parallel matrix multiplication\n");
// #endif
//   populateMatrix(A, n, 1);
//   uint32_t timePar = matTpar(A, B, n);
// #ifdef PRINT
//   printf("parallel matrix multiplication done. Wall Time: \t%ld us\n", timePar);
// #endif


  //Exporting results
  fprintf(matMulFile, "%d,%ld,%ld,%s,%s,%s\n", n, time, 0, hostbuffer, COMPILATION_NOTES, RUN_NOTES);
  // fprintf(matMulFile, "%d,%ld,%ld,%s,%s\n", n, time, timePar, hostbuffer, COMPILATION_NOTES);

  //Closing results files
  fclose(matMulFile);

  //Release memory
  free(A);
  free(B);
  free(C);
}
