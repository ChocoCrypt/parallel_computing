#include <cstdio>
#include <omp.h>




int main() {
  int Nthr = 8;

  int array[] = {2, 4, 6, 8, 10, 12, 14, 16};
  int res = 0;
  
  #pragma omp parallel num_threads(Nthr)
  {
    int id = omp_get_thread_num();

    #pragma omp critical
    {
      res += array[id] / 2;
    }
  }

  printf("res = %d\n", res);
  
  return 0;
}
