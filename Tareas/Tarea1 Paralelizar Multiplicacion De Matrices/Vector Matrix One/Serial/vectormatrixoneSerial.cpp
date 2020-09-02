#include "vectormatrixoneSerial.hpp"
#include <iostream>
#include <vector>

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

//implementacion serial ya funcionando bien
VectorMatrixOne  operator*(VectorMatrixOne M1 , VectorMatrixOne M2){
    VectorMatrixOne result = VectorMatrixOne(M1.dimx , M2.dimy);
    if(M1.dimy != M2.dimx){
        throw runtime_error("las dos matrices no se pueden multiplicar");
    }
    for(int i = 0 ; i<M1.dimx ; i++){
        for(int j = 0 ; j<M2.dimy ; j++){
            int sum  = 0 ;
            for(int k = 0 ; k < M2.dimx ; k++){
                sum += M1.matrix[i][k] * M2.matrix[k][j] ;  
            }
            result.matrix[i][j] = sum;
            sum = 0;
        }
    }
    return result;
}



