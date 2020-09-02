#include "matrixOne.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;
//*************************METODOS BASICOS********************************

MatrixOne ::MatrixOne(int m, int n){
    array = new int[m*n];
    dimx = m;
    dimy = n;
    //voy a llenar la matriz de unos a ver como funciona
    cout<<"la matriz de creó exitosamente y se lleno de 1's \n";
    for(int i = 0 ; i<m*n ; i++){
        array[i] = 1 ;
    }
}

MatrixOne ::~MatrixOne(){
    delete[] array;
}

int MatrixOne ::get_dimx(){
    return dimx;
}

int MatrixOne ::get_dimy(){
    return dimy;
}

int  MatrixOne ::get(int x , int y){
    return(array[y*dimx +x]);
}

void MatrixOne ::set(int x , int y , int val){
    array[y*dimx + x] = val ;
}


void MatrixOne ::display(){
    cout<<"***************************\n";
    for( int i = 0  ; i<dimy ; i++){
        cout<<endl;
        for(int j = 0 ; j<dimx ; j++){
            cout<< array[ (i* dimx) + j] << " ";
        }
    }
    cout<<"\n \n*************************** \n";
}
//*************************OPERADORES********************************


MatrixOne& MatrixOne ::operator = ( MatrixOne& M){
    if(dimx =! M.dimx || dimy != M.dimy){
        throw runtime_error("las matrices tienen que ser de las mismas dimenciones");
    }

    for(int i = 0 ; i< dimy ; i++){
        for(int j = 0 ; j<dimx ; j++){
            array[(i*dimx)+j] = M.array[(i*dimx) +j];
        }
    }
    return *this;
}

MatrixOne MatrixOne ::operator *(MatrixOne& M){
    MatrixOne res =  MatrixOne(dimx , M.dimy);
    for(int i = 0 ; i< dimy ;  i++){
        for(int k = 0 ; k<dimx ; k++){

        }
    }






    return res;
}
MatrixOne operator ++(MatrixOne & M){
    MatrixOne res  = MatrixOne(10 , 10);//tentativo mientras le pregunto a carlos
    return res;
}
