#include <iostream>
#include <omp.h>
#include <vector>
#include <fstream>
#include <functional>
using namespace std;
//este metodo lee el archivo vector.dat que genera el generador de vectores y genera un vector de longiud n
vector<long int> readfile(long int n){
    vector<long int> datos ;
    int x;
    long int top = 0;//esta fue la forma que se me ocurrio para no llenar todo el vector
    ifstream inFile;
    inFile.open("vector.dat");
    if (!inFile) {
        cout << "no se pudo abrir el archivo de vectores"<<endl;
        exit(1); // terminate with error
    }
    while (inFile >> x && top < n) {
        datos.push_back(x);
        top++;
    }
    inFile.close();
    return datos;
}
//metodo para generar un vector grande
vector<long int> GenerarVectorNelementos(long int n){
    vector<long int> tmp ;
    for(long int i = n ; i>=0 ; i--){
        tmp.push_back(i);
    }
    return tmp;
}
void check(vector<long int> &vec){
    long int chunk = vec.size()/4 ;
    if(vec[chunk] == chunk && vec[chunk*2] == chunk*2 && vec[chunk*3] == chunk*3 && vec[chunk*4] == chunk*4){
        cout<<"EL VECTOR ESTA CORRECTAMENTE ORDENADO!"<<endl;
    }
    else{
        cout<<"PAILAS, EL VECTOR NO ESTA ORDENADO"<<endl;
    }
}

bool RealCheck(vector<long int> &vec){
    for(unsigned long int i = 0 ; i<vec.size() -1 ; i++){
        if(vec[i] > vec[i+1]){
            return false;
        }
    }
    return true;
}
//metodo para general un vector temporal
vector<long int> vectortemporal(vector<long int> &vec){
    vector<long int> tmp;
    for(unsigned long int i =0 ; i<vec.size() ; i++){
        tmp.push_back(0);
    }
    return tmp;
}
//metodo para imprimir los vectores y poder saber que estoy haciendo
void printvector(vector<long int> &vec){
    for(unsigned long int i = 0 ; i<vec.size(); i++){
        cout<<vec[i]<<" ";
    }
    cout<<endl;
}

//metodo dado por el profesor
void Merge(vector<long int> &vec , long int ini , long int fin, vector<long int> &tmp){
    long int mid = (fin +ini)/2;
    long int p1 = ini ;
    long int p2 = mid ;
    long int pt = ini;
    while(p1<mid && p2<fin){
        if(vec[p1] < vec[p2]){
            tmp[pt] = vec[p1];
            pt++;
            p1++;
        }
        else{
            tmp[pt] = vec[p2];
            pt++;
            p2++;
        }
    }
    while(p1 <mid ){
        tmp[pt] = vec[p1];
        pt++;
        p1++;
    }
    while(p2<fin){
        tmp[pt] = vec[p2];
        pt++;
        p2++;
    }

    for(long int i = ini ; i<fin ; i++){
        vec[i] = tmp[i];
    }

}
//algoritmo de merge paralelo
void ParalelMerge(vector<long int> &vec , long int ini , long int fin, vector<long int> &tmp){

}
//algoritmo de mergesort serial
void T_MergeSort(vector<long int> &vec , long int ini , long int fin , vector<long int> &tmp){
    long int mid = (fin+ini)/2;
    if(ini<mid){
        T_MergeSort(vec , ini, mid, tmp);
        T_MergeSort(vec , mid , fin , tmp);
        Merge(vec,ini,fin , tmp);
    }
}
void MergeSort(vector<long int> &vec){
    int ini = 0;
    int fin = vec.size();
    vector<long int> tmp = vectortemporal(vec);
    T_MergeSort(ref(vec),ini,fin , ref(tmp));

}
//Algoritmo de MergeSort Paralelo hecho para la clase
void T_MergeSortParalelo(vector<long int> &vec , long int ini , long int fin , vector<long int> &tmp ){
    if((fin - ini )<= 1000){
        T_MergeSort(ref(vec) , ini , fin , ref(tmp));
    }
    else{
        int mid = (ini +fin)/2 ;
        if(ini<fin){
            #pragma omp task shared(vec,tmp)
            {
                T_MergeSortParalelo(ref(vec),ini,mid, ref(tmp));
            }
            #pragma omp task shared(vec , tmp)
            {
                T_MergeSortParalelo(ref(vec),mid,fin, ref(tmp));
            }
            #pragma omp taskwait
            Merge(ref(vec), ini, fin, ref(tmp));
        }
    }
}
void MergeSortParalelo(vector<long int> &vec){
    vector<long int> tmp = vectortemporal(vec);
    double t_start = omp_get_wtime();
    int ini = 0 ;
    int fin = vec.size();
    #pragma omp parallel
    {
        #pragma omp single
        {
            T_MergeSortParalelo(ref(vec),ini,fin , tmp);
        }
    }
    double t_stop = omp_get_wtime();
    cout<<t_stop-t_start <<endl;

}



int main(int argc , char **argv ){
    long int tamvector = atoi(argv[1]);
    vector<long int> vec = readfile(tamvector);

    MergeSortParalelo(vec);


    if(RealCheck(vec)){
        //no hago nada
    }
    else{
        cout<<"failed"<<endl;
    }

return 0 ;
}
