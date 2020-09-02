#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <omp.h>
using namespace std;



int main(int argc, char** argv) {
  int N = atoi(argv[1]);
  int chunk_size = atoi(argv[2]);
  
  int* array = new int[N];
  for(int i = 0; i < N; ++i)
    array[i] = -1;

  double t_start = omp_get_wtime();
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    if(id == 0){
      int Nthr = omp_get_num_threads();
      printf("No. of threads: %d\n",Nthr);
    }
    
    #pragma omp for schedule(dynamic, chunk_size)
    for(int i = 0; i < N; ++i){
      array[i] = id;
    }
  }
  double t_stop = omp_get_wtime();

  for(int i = 0; i < N; ++i)
    printf("%d ",array[i]);
  printf("\n");
  
  ofstream file("dynamic.dat");
  for(int i = 0; i < N; ++i)
    file << array[i] << " ";
  file << endl;
  file.close();
  
  delete[] array;

  printf("Time: %f\n",t_stop-t_start);
  
  return 0;
}
