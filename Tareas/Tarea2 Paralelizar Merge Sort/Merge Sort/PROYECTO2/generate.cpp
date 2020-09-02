#include "generate_random.hpp"
#include <iostream>

using namespace std;

int main(int argc, char** argv){
  string name = "size.txt";
  int size = atoi(argv[1]);  
  int* a = new int[size];

  unsigned seed = 123;
  generate_norepeat_vector(size, a, seed);

  write_vector(size, a); 
  write_size(size,name);
  return 0;
}
