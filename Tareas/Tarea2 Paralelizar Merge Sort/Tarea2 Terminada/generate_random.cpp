#include "generate_random.hpp"


void print_vector(int size, const int* a) {
  for(int i = 0; i < size; ++i)
    printf("%d ",a[i]);
  printf("\n");
}

void write_vector(int size, const int* a) {
  ofstream Out("vector.dat");
  for(int i = 0; i < size; ++i)
    Out << a[i] << " ";
  Out << "\n";
  Out.close();
}

void read_vector(int size, int* a) {
  ifstream In("vector.dat");
  for(int i = 0; i < size; ++i)
    In >> a[i];
  In.close();
}

void generate_vector(int size, int* a, unsigned seed) {
  minstd_rand0 rng(seed);
  
  const int max_num = size;
  //Generation of a sequence of (pseudo)random numbers
  rng();
  for(int i = 0; i < size; ++i){
    int num = int(max_num * ( double(rng()) / rng.max() ));
    a[i] = num;
  }
}

void generate_norepeat_vector(int size, int* a, unsigned seed) {
  minstd_rand0 rng(seed);
  
  const int max_num = 3*size;
  //use set to profit from the count method
  set<int> numbers;
  //Generation of a sequence of (pseudo)random numbers
  rng();
  int count = 0;
  while(count < size){
    int num = int(max_num * ( double(rng()) / rng.max() ));
    if(numbers.count(num) == 0){ //if number not in set
      numbers.insert(num);
      a[count] = num;
      count++;
    }
  }
}
