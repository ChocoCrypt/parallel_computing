#include <cstdio>
#include <cstdlib>
#include <omp.h>


double pi_calc(long N) {
  double pi4 = 0.;
  double val;
  for(int i = 1; i <= N; i++){
    val = (double(i) - 0.5) / N;
    pi4 += 1. / (1+val*val);
  }
  return 4*pi4 / N;
}

int main(int argc, char** argv) {
  long N = atoi(argv[1]);

  double t_start = omp_get_wtime();
  double pi = pi_calc(N);
  double t_stop = omp_get_wtime();
  
  printf("Pi = %.12f\n",pi);
  printf("Time: %f\n",t_stop-t_start);
  
  return 0;
}
