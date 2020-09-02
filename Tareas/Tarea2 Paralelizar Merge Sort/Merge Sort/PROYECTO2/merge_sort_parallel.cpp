#include<iostream>
#include<vector>
#include<string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <omp.h>
#include <sys/time.h>
#include <fstream>

#include "generate_random.hpp"

using namespace std;

const int CONST = 100;

// Get Time
double gettime(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec + tp.tv_usec/(double)1.0e6;
}

// Display the array
void display(int *v, int size){
  for (unsigned i = 0; i < size; i++){
    cout << v[i] << " " ;
  }
  cout << endl;
}

// Generates a copy of an array
void deep_copy(const int *v, int *&temp, int size){
  for (int i = 0; i < size; i++){
    temp[i] = v[i];
  }
}

// Gets the size of the array
int get_size(string name){
    ifstream file;
    string line = "";
    string file_size = "";
    string file_size_num = "";
    bool read = false;

    if (file.fail()){
        cout << "Error" << endl;
        exit(1);
    }

    file.open(name,ios::in);
    getline(file,file_size);

    for(int i = 0; i < file_size.size();i++){
        if (read){
            file_size_num += file_size[i];
        }
        if (file_size[i] == ':'){
            read = true;
        }
    }
    int size = atof(file_size_num.c_str());
    return size;
}

// Writes the times in a txt
void Write(vector<double> t, string name, int reps){
    ofstream file;
    file.open(name, ios::out);

    if (file.fail()){
        cout << "Error" << endl;
        exit(1);
    }
    file << "Reps:"<< reps << endl;
    for (int i = 0; i < t.size(); i++){
        file << t[i] << endl;
    }
    file.close();
}


// Linear Search
bool linear_search(const int *copy, int size, int key){
  bool status = false;
  for (int i = 0; i < size; i ++){
    if (copy[i] == key){
      status = true;
    }
  }
  return status;
}

// Check 
bool check(const int *v, const int *copy, int size){
  bool status = true;
  int x = v[0];
  for (int i = 1; i < size; i++){
    int y = v[i];
    bool is_in = linear_search(copy, size, x);
    if (x >= y || is_in == false){ // if the array can have repetead numbers it is x > y
      status = false;
      break;
    }
    else{
      x = y;
    }
  }
  return status;
}

// Insertion Sort
void insertion_sort(int *&v, int ini, int fin){
   int i, key, j;  
    for (i = ini; i < fin; i++){  
      key = v[i];  
      j = i - 1;  
    while (j >= 0 && v[j] > key){  
        v[j + 1] = v[j];  
        j = j - 1;  
    }  
    v[j + 1] = key;  
  }  
}  

// Merge
void merge(int *&v, int *&temp, int ini, int fin){
  int mid = (ini+fin)/2;
  int pi = ini;
  int pm = mid;
  int pt = ini;

  while(pi < mid && pm < fin){
    if (v[pi] < v[pm]){
      temp[pt] = v[pi];
      pi ++;
      pt ++;
    }
    else{
      temp[pt] = v[pm];
      pm ++;
      pt ++;
    }
  }

  while(pi < mid){
    temp[pt] = v[pi];
    pi ++;
    pt ++;
  }

  while(pm < fin){
    temp[pt] = v[pm];
    pm ++;
    pt ++;
  }

  for (int i = ini; i < fin; i++){
    v[i] = temp[i];
  }
}

// Merge Sort Helper
void merge_sort_helper(int *&v, int *&temp, int ini, int fin){
  if ((fin - ini) <= CONST){
    insertion_sort(v,ini,fin);
  }
  else{
    int mid = (ini+fin)/2;
    if(ini < mid){
      #pragma omp task shared(v,temp)
      { 
        merge_sort_helper(v,temp,ini,mid); 
      }
      #pragma omp task shared(v,temp)
      { 
        merge_sort_helper(v,temp,mid,fin);
      }
      
      #pragma omp taskwait
      merge(v,temp,ini,fin);
    }
  }
}

// Merge Sort
void merge_sort(int *&v, int size){
  int *temp = new int[size];
  int ini = 0;
  int fin = size;
  #pragma omp parallel
  {
    #pragma omp single
    {
        merge_sort_helper(v,temp,ini,fin);
    }
  }
  delete[] temp;
}

// Main
int main(int argc, char** argv){
  int reps = atoi(argv[1]);

  vector<double> times;

  string name = "size.txt";
  int size = get_size(name);

  int *v = new int [size];
  int *copy = new int [size];

  read_vector(size,v);
  deep_copy(v,copy,size);

  
 
  for (int i = 0; i < reps; i++){
    double t_start = gettime();
    merge_sort(v,size);
    double t_stop = gettime();
    

  // Check 
  // -----------------------------------------------------------------
   bool r = check(v,copy,size);
   if (r == false){
     cout << "The vector is not organice" << endl;
     return 0;
   }
  // -----------------------------------------------------------------
     
    double t_execution = t_stop - t_start;
    times.push_back(t_execution);

    deep_copy(copy,v,size);
  }

  string Parallel = "Parallel_Data.txt";
  Write(times, Parallel, reps);

  delete[] v;
  delete[] copy;
  return 0;
}
