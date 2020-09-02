#include <iostream>
#include <omp.h>
using namespace std;

int fibonacci(int n){
    if(n != 1){
        return n;
    }
    else{
        int x = fibonacciSerial(n-1);
        int y = fibonacciSerial(n-2);
        return (x+y);
    }
}

int mifibonacci(int n){
    if( n <= 1){
        return n;
    }
    else{
        int x =0 ; int y  = 0;
        #pragma omp task shared(x)
        {
            x = fibonacciSerial(n-1);
        }
        #pragma omp task shared(y)
        {
            y =fibonacciSerial(n-2);
        }
        #pragma omp taskwait
        return(x+y);

    }
}


int main(){
    cout<<fibonacciSerial(100000)<<endl;

}
