#include <stdio.h>
#include <stdlib.h>
#include <cblas.h>
#include <time.h>

#define N 256

double CLOCK() {
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);
  return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

int main() {
  int m = N;
  int n = N;
  int k = N;
  double start, finish, total;
  float *A = (float *)malloc(m * k * sizeof(float));
  float *B = (float *)malloc(k * n * sizeof(float));
  float *C = (float *)malloc(m * n * sizeof(float));

  // Initialize matrix values (example)
  for (int i = 0; i < m * k; i++) {
    A[i] = i + 1;
  }
  for (int i = 0; i < k * n; i++) {
    B[i] = i + 1;
  }
  
  start = CLOCK();
  // Perform matrix multiplication using cblas_sgemm
  cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1.0f, A, k, B, n, 0.0f, C, n);
  finish = CLOCK();
  total = finish - start;

  // Print one item in resulting matrix
  printf("C[%d][%d] = %f\n", m-1, n-1, C[m * n - 1]);
  // Print time taken
  printf("Time taken = %lf ms\n", total);
  // Free allocated memory
  free(A);
  free(B);
  free(C);
  return 0;
}
