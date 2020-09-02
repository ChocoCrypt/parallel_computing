#include "vectormatrixone.hpp"
#include <cstdlib>
#include <vector>

using namespace std ;

int main(){


    VectorMatrixOne mat1 = VectorMatrixOne(1000 , 1000);
    VectorMatrixOne mat2 = VectorMatrixOne(1000 , 1000);

    VectorMatrixOne mat3 = mat1*mat2 ;
    //mat3.display();

}
