#include <iostream>
#include <omp.h>

using namespace std;

int main(){
    #pragma omp parallel
    {
        #pragma omp single
        {

        }
    }
}
