//Norma de Frobenius de una matriz
//Código serial

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <omp.h>



int frobenius(int* A, int m, int n) {
  int norm = 0;
  for(int i = 0; i < m; ++i){
    for(int j = 0; j < n; ++j)
      norm += A[i*n+j]*A[i*n+j];
  }
  return sqrt(norm);
}
int paralelfrobenius(int* A, int m, int n) {
  int norm = 0;
  #pragma omp parallel
  {
     #pragma omp for reduction(+:norm) collapse(2)
      for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j)
        //  #pragma omp atomic
          norm += A[i*n+j]*A[i*n+j];
     }
}
  return norm;
}



int main(int argc, char** argv) {
  int m = atoi(argv[1]);
  int n = atoi(argv[2]);

  int* A = new int[m*n];
  for(int i = 0; i < m; ++i){
    for(int j = 0; j < n; ++j)
      A[i*n+j] = 1;
  }

  double t_start = omp_get_wtime();
  int norm = paralelfrobenius(A, m, n);
  double t_stop = omp_get_wtime();

  printf("norm: %d\n",norm);
  printf("Time: %f\n",t_stop-t_start);

  delete[] A;

  return 0;
}
