#include <omp.h>
#include <iostream>
#include <stdio.h>
using namespace std;
void foo(){
    int cont = 0;
    #pragma omp parallel
    {
        #pragma omp for
        for(int i = 0 ; i<10000000 ; i++){
            cont++;
            cout<<"";
        }
    }
    cout<<"\n \n \n";
}
int main(){
    cout<<"start : \n ";
    #pragma omp parallel
    {
        foo();
        #pragma omp master
        {
            foo();
        }
        #pragma omp critical
        foo();
        #pragma omp single
        foo();
    }
    cout<<"\n \n \n \n \n private: \n";
    int var = 5;
    cout<<"private: \n";
    #pragma omp parallel private(var)
    {
        cout<<var<<endl;
    }
    cout<<"firstprivate: \n";
    #pragma omp parallel firstprivate(var)
    {
        cout<<var<<endl;
    }

}
