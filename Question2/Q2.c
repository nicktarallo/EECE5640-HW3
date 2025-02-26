#include <stdio.h>
#include <x86intrin.h>
#include <stdlib.h>
#include <time.h>

#define N 4096

// Function to get current time in ms, provided on Canvas
double CLOCK() {
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);
  return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

// multiplies a matrix of size m x n with a vector of length n to store in a vector of length m. Stored in output_vec
void matrix_vector_mult(const float *mat, const float *vec, float *output_vec, size_t m, size_t n) {
  // iterate over matrix rows
  for (size_t i = 0; i < m; i++) {
    // iterate through vector and across each row
    for (size_t j = 0; j < n; j++ ) {
      output_vec[i] += (mat[i*n + j] * vec[j]);
    }
  }
}

void matrix_vector_mult_avx512f(const float *mat, const float *vec, float *output_vec, size_t m, size_t n) {
  // iterate over matrix rows
  for (size_t i = 0; i < m; i++) {
    size_t j = 0;
    float sum_arr[16];

    __m512 sum_vec, mat_vec, vec_vec;  // mat_vec will store items from a row in the matrix, vec_vec is from the input vector

    sum_vec = _mm512_setzero_ps();

    for (; j + 16 <= n; j += 16) {
      mat_vec = _mm512_loadu_ps(&mat[i*n + j]);
      vec_vec = _mm512_loadu_ps(&vec[j]);
      sum_vec = _mm512_fmadd_ps(mat_vec, vec_vec, sum_vec);
    }
    
    _mm512_storeu_ps(sum_arr, sum_vec);
    float total_sum = 0.0f;
    for (int k = 0; k < 16; k++) {
      total_sum += sum_arr[k];
    }

    for (; j < n; j++) {
      total_sum += (mat[i*n + j] * vec[j]);
    }

    output_vec[i] = total_sum;
  }
}

int main() {
  double start, finish, total;
  
  size_t m = N;
  size_t n = N;

  float mat[m][n];
  float vec[n], output_vec_no_avx[m], output_vec_avx[m];

  for (size_t i = 0; i < m; i++) {
    output_vec_no_avx[i] = 0.0;
    output_vec_avx[i] = 0.0;
    for (size_t j = 0; j < n; j++) {
      mat[i][j] = 1.0;
    }
  }

  for (size_t i = 0; i < n; i++) {
    vec[i] = 1.0;
  }

  start = CLOCK();
  matrix_vector_mult_avx512f(&mat[0][0], vec, output_vec_avx, m, n);
  finish = CLOCK();
  total = finish - start;
  printf("output_vec_avx[%zu] = %f\n", m-1, output_vec_avx[m-1]);
  printf("Time taken with AVX = %f ms\n\n", total);

  start = CLOCK();
  matrix_vector_mult(&mat[0][0], vec, output_vec_no_avx, m, n);
  finish = CLOCK();
  total = finish - start;
  printf("output_vec[%zu] = %f\n", m-1, output_vec_no_avx[m-1]);
  printf("Time taken without AVX = %f ms\n", total);
}
