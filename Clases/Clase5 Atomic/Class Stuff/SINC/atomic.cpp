#include <cstdio>
#include <omp.h>



int main() {
  int Nthr = 8;
  
  int count = 0;
    
  #pragma omp parallel num_threads(Nthr)
  {
    int id = omp_get_thread_num();

    #pragma omp atomic
    count += id;
  }

  printf("count = %d\n",count);
  
  return 0;
}
