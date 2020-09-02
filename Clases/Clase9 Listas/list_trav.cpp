#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <list>
#include <omp.h>
using namespace std;


void foo(double& val) {
  #pragma omp parallel
  {
  #pragma omp for reduction( + : val)
  for(int i = 0; i < 10000; ++i){
     #pragma omp atomic
     val += erfc(cos(sqrt(val)));
    }
  //printf("%f ",val);
  }

}

void traverse_list(list<double>& l) {
  list<double>::iterator it = l.begin();
  while(it != l.end()){
    foo(*it);
    it++;
  }
}


int main(int argc, char** argv) {
  int size = atoi(argv[1]);

  list<double> myList;
  for(int i = 0; i < size; ++i)
    myList.push_back(double(i)/2);

  double t_start = omp_get_wtime();
  traverse_list(myList);
  double t_stop = omp_get_wtime();

  double sum = 0;
  list<double>::iterator it;
      for(it = myList.begin(); it != myList.end(); ++it)
        sum += *it;

      printf("Res: %f\n",sum);
      printf("Time: %f\n",t_stop-t_start);

  return 0;
}
