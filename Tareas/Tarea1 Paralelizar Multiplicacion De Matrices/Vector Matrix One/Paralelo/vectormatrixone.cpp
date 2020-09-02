#include "vectormatrixone.hpp"
#include <iostream>
#include <vector>
#include <thread>
using namespace std;

VectorMatrixOne::VectorMatrixOne(int y,  int x){
    dimx = x ;
    dimy = y ;
    matrix.resize(x);
    for(int i = 0 ; i<x ; i++){
        matrix[i].resize(y);
        for(int j = 0 ; j<y ; j++){
            matrix[i][j] = 1;
        }
    }
}


int VectorMatrixOne::getdimx(){
    return dimx;
}
int VectorMatrixOne::getdimy(){
    return dimy;
}

int VectorMatrixOne::get(int x, int y){
    return matrix[x][y];
}

void VectorMatrixOne::set(int x , int y , int val){
    matrix[x][y] = val ;
}

void VectorMatrixOne::display(){
    for(int i = 0 ; i< dimx ; i++){
        for(int j = 0 ; j<dimy ; j++){
            cout<<matrix[i][j]<< "  ";
        }
        cout<<endl;

    }
    cout<<'\n';
}


VectorMatrixOne& VectorMatrixOne ::operator= ( VectorMatrixOne& M){
    for(int i =  0 ; i<dimx ; i++){
        for(int j = 0 ; j<dimy ; j++){
            matrix[i][j] = M.matrix[i][j];
        }
    }
    return *this;
}

//implementacion paralela funcionando correctamente
void helper(VectorMatrixOne &M1 , VectorMatrixOne &M2 , VectorMatrixOne &result , int inicial, int final){
    for(int i = inicial ; i<final ; i++){
        for(int j = 0 ; j<M2.getdimy() ; j++){
            int sum  = 0 ;
            for(int k = 0 ; k < M2.getdimx() ; k++){
                sum += M1.get(i,k) * M2.get(k,j) ;
            }
            result.set(i,j,sum);
            sum = 0;
        }
    }
}
VectorMatrixOne  operator*(VectorMatrixOne &M1 , VectorMatrixOne &M2){
    if(M1.getdimy() != M2.getdimx()){
        throw runtime_error("las dos matrices no se pueden multiplicar");
    }
    int xdim = M1.getdimx() ;
    int ydim = M2.getdimy();

    VectorMatrixOne result = VectorMatrixOne(xdim, ydim);

    thread thr1(helper , ref(M1) , ref(M2) , ref(result) , 0, xdim/2);

    helper(M1,M2,result,xdim/2,xdim);
    thr1.join();
    return result;

}
