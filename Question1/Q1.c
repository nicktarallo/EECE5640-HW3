#include <stdlib.h>
#include <stdio.h>
#include <math.h>

long factorial(long n) {
  long result = 1;
  for (int i = n; i > 0; i--) {
    result *= i;
  }
  return result;
}

float sin_float(float x, long num_terms) {
  float result = 0;
  for (long n = 0; n < num_terms; n++) {
    long two_n_plus_1 = (2 * n) + 1;
    float term_to_add = pow(-1, n) / factorial(two_n_plus_1) * pow(x, two_n_plus_1);
    result += term_to_add;
  }
  return result;
}

double sin_double(double x, long num_terms) {
  double result = 0;
  for (long n = 0; n < num_terms; n++) {
    long two_n_plus_1 = (2 * n) + 1;
    double term_to_add = pow(-1, n) / factorial(two_n_plus_1) * pow(x, two_n_plus_1);
    result += term_to_add;
  }
  return result;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Please supply command line arguments in the form `[x] [num_terms]`");
    return 1;
  }
  double x_double = atof(argv[1]);  // atof returns a double
  float x_float = (float) x_double;
  long num_terms = atol(argv[2]);

  float result_float = sin_float(x_float, num_terms);
  float result_double = sin_double(x_double, num_terms);
 
  printf("Num terms = %ld\n", num_terms);
  printf("With float: sin(%f) = %.10f\n", x_float, result_float);
  printf("With double: sin(%lf) = %.10lf\n", x_double, result_double);
  
  return 0;
}
