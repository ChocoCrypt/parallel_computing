#include "matrixOne.hpp"
#include <cstdlib>

using namespace std ;

int main(){
    int n = 250;
    MatrixOne M1 = MatrixOne(10 , n);
    MatrixOne M2 = MatrixOne( n ,10);
    // n x y
    MatrixOne M3 = M1*M2 ;
    M3.display();
    return 0;
}
