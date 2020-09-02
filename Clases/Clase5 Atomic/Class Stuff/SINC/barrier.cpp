#include <cstdio>
#include <omp.h>


int foo1(int x) {
  return 8*x;
}

int foo2(int x) {
  return x/4;
}


int main() {
  int Nthr = 8;
  
  int array1[Nthr];
  int array2[Nthr];
  #pragma omp parallel num_threads(Nthr)
  {
    int id = omp_get_thread_num();
    
    array1[id] = foo1(id);

    #pragma omp barrier

    array2[id] = foo2(array1[Nthr-1-id]);
  }

  for(int i = 0; i < Nthr; ++i)
    printf("%d ",array2[i]);
  printf("\n");
  
  return 0;
}
