#ifndef _MATRIXONE_HPP
#define _MATRIXONE_HPP
#include <iostream>
#include <cstdlib>

using namespace std;

class MatrixOne{

private:
    int *array;
    int dimx;
    int dimy;

public:
    //*************************METODOS BASICOS********************************

    MatrixOne(int m , int n);
    ~MatrixOne();

    int get_dimx();
    int get_dimy();
    int get(int x , int y);

    void set(int x , int y , int val);


    void display();


    //*************************OPERADORES********************************
    MatrixOne& operator = ( MatrixOne& M);
    MatrixOne operator * ( MatrixOne& M);
    MatrixOne operator ++(MatrixOne & M); //multiplicacion paralela

};

#include "matrixOne.cpp"
#endif
