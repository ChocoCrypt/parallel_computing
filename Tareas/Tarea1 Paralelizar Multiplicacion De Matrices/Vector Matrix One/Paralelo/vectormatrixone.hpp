#ifndef _VECTORMATRIXONE_HPP_
#define _VECTORMATRIXONE_HPP_
#include <iostream>
#include <vector>

using namespace std;

class VectorMatrixOne{
private:
    vector<vector<int>> matrix;
    int dimx ;
    int dimy ;
public:
    VectorMatrixOne(int y , int x);
    ~VectorMatrixOne(){}
        //no hace nada porque ya los vectores se eliminan solos
    int getdimx();
    int getdimy();
    int get(int x , int y);

    void set(int x , int y , int val);

    void display();



VectorMatrixOne& operator= ( VectorMatrixOne& M);
//serial


};
VectorMatrixOne  operator*(VectorMatrixOne &M1 , VectorMatrixOne &M2);


#include "vectormatrixone.cpp"
#endif
