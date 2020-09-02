#include <iostream>
#include <omp.h>
using namespace std;

int main(){
    int var = 5;
    #pragma omp parallel //default(shared) private(var)
    {
        int id = omp_get_thread_num();
        var =  var +1 ;
        if(var %2 == 0){
            #pragma omp critical
            var = var+3;
        }
    }
    cout<<var<<"\n";
}
