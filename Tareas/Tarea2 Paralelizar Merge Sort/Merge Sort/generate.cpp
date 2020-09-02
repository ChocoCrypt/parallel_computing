#include "generate_random.hpp"


int main(int argc, char** argv) {
  int size = atoi(argv[1]);
  
  int* a = new int[size];

  unsigned seed = 123;
  generate_norepeat_vector(size, a, seed);

  write_vector(size, a);
  
  return 0;
}
