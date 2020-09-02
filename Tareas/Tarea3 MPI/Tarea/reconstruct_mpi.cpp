#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <random>
#include "pgmio.hpp"
#include <sys/time.h>
#include <mpi.h>

using namespace std;

double gettime(){
  return MPI_Wtime();
}

int main(int argc, char** argv){
  string filename = "edge512x384.pgm";
  string filename2 = "edge512x384_re.pgm";

  int N = atoi(argv[1]);

  MPI_Init(nullptr,nullptr);

  int rank,Comm_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &Comm_size);

  int n, m;
  float* edge = nullptr;
  float* nuevo = nullptr;
  pgmsize(filename, n, m);
  float* buff = new float[n*m];
  if(rank==0){
    edge  = new float[(n+2)*(m+2)];
    nuevo = new float[(n+2)*(m+2)];

    for(int j = 0; j < m+2; j++){
      edge[0*(m+2)+j] = 255; edge[(n+1)*(m+2)+j] = 255;
      nuevo[0*(m+2)+j] = 255; nuevo[(n+1)*(m+2)+j] = 255;
    }
    for(int i = 1; i < n+1; i++){
      edge[i*(m+2)+0] = 255; edge[i*(m+2)+(m+1)] = 255;
      nuevo[i*(m+2)+0] = 255; nuevo[i*(m+2)+(m+1)] = 255;
    }

    pgmread(filename, buff, n, m);
    //aca copio el buff a edge
    for(int i = 0; i < n; i++){
      for(int j = 0; j < m; j++){
        edge[(i+1)*(m+2)+(j+1)] = buff[i*m+j];
      }
    }
  }

  int global_size = (n+2)*(m+2);

  int tamano = int(global_size/Comm_size);
  int local_n = int(tamano/(m+2));
  int local_m = m+2;
  int ultimafila = tamano%(m+2);


  float* new_b = new float[tamano];
  float* local_old_b = new float[tamano];
  float* local_edge  = new float[tamano];

  for(int i = 0; i < tamano; i++){
    local_old_b[i] = 255;
  }
  //aca hago los scatters para recorrer la matriz paralelamente
  MPI_Scatter(edge, tamano, MPI_FLOAT, local_edge, tamano, MPI_FLOAT, 0, MPI_COMM_WORLD);
  MPI_Scatter(nuevo, tamano, MPI_FLOAT, new_b, tamano, MPI_FLOAT, 0, MPI_COMM_WORLD);

  double tstart = gettime();

  int ini = rank*tamano;
  int fin = (rank+1)*tamano;

  int pos_ini = ini%local_m;
  int pos_fin = fin%local_m;

  int FronteraSup = local_m-pos_ini;
  int long_frontInf = pos_fin;

  int ini_frontsup = ini;
  int fin_frontsup = ini+(local_m-pos_ini);
  int ini_frontInf = fin-pos_fin;
  int fin_frontInf = fin;

  int FronteraInf = 0;
  if(long_frontInf==0){
    FronteraInf = local_m;
    ini_frontInf -= local_m;
    fin_frontInf -= 0;
  }else FronteraInf = long_frontInf;

  //check
  printf("frontera superior %d: [%d-%d] = %d \n", rank, ini_frontsup, fin_frontsup, FronteraSup);
  printf("frontera inferior%d: [%d-%d] = %d \n", rank, ini_frontInf, fin_frontInf, FronteraInf);

  int TamanoTrozoInf = FronteraInf;
  int TamanoTrozoSup = FronteraSup;

  MPI_Status status;
  float* nuevoVector = nullptr;
  if(rank==0){
    float* frontInf = new float[local_m];
    MPI_Sendrecv(&local_edge[tamano-1-local_m], local_m, MPI_FLOAT, rank+1, 1, frontInf, local_m, MPI_FLOAT, rank+1, 1, MPI_COMM_WORLD, &status);
    nuevoVector = new float[tamano+local_m];
    for(int i=0 ; i<tamano ; i++){
      nuevoVector[i] = local_edge[i];
    }
    for(int i=0 ; i<local_m ; i++){
      nuevoVector[tamano+i] = frontInf[i];
    }
  }else if(rank==Comm_size-1){
    float* frontsup = new float[local_m];
    MPI_Sendrecv(local_edge, local_m, MPI_FLOAT, rank-1, 1, frontsup, local_m, MPI_FLOAT, rank-1, 1, MPI_COMM_WORLD, &status);
    nuevoVector = new float[tamano+local_m];
    for(int i=0 ; i<local_m ; i++){
      nuevoVector[i] = frontsup[i];
    }
    for(int i=0 ; i<tamano ; i++){
      nuevoVector[local_m+i] = local_edge[i];
    }
  }else{
    float* frontsup = new float[local_m];
    float* frontInf = new float[local_m];
    int previo = rank-1;
    int sig = rank+1;
    MPI_Sendrecv(local_edge, local_m, MPI_FLOAT, previo, 1, frontsup, local_m, MPI_FLOAT, previo, 1, MPI_COMM_WORLD, &status);
    MPI_Sendrecv(&local_edge[tamano-1-local_m], local_m, MPI_FLOAT, sig, 1, frontInf, local_m, MPI_FLOAT, sig, 1, MPI_COMM_WORLD, &status);
    nuevoVector = new float[tamano+2*local_m];
    for(int i=0 ; i<local_m ; i++){
      nuevoVector[i] = frontsup[i];
  }
    for(int i=0 ; i<tamano ; i++){
      nuevoVector[258+i] = local_edge[i];
    }
    for(int i=0 ; i<local_m ; i++){
      nuevoVector[tamano+258+i] = frontInf[i];
    }
  }

  for(int it = 0; it < N; it++){
    if(rank==0){
      for(int i=1 ; i<local_n ; i++){
        for(int j=1 ; j<local_m ; j++){
          new_b[i*local_m+j] = (local_old_b[i*local_m+(j-1)]+local_old_b[i*local_m+(j+1)]+local_old_b[(i-1)*local_m+j]+local_old_b[(i+1)*local_m+j]-nuevoVector[i*local_m+j])/4;
        }
      }
      for(int i=1 ; i<ultimafila ; i++){
        new_b[local_n*local_m+i] = (local_old_b[(local_n-1)*local_m+i]+local_old_b[(local_n+1)*local_m+i]+local_old_b[local_n*local_m+(i-1)]+local_old_b[local_n*local_m+(i+1)]-nuevoVector[local_n*local_m+i])/4;
      }
    }else if(rank==Comm_size-1){
      for(int i=local_m-FronteraSup+1 ; i<local_m ; i++){
        new_b[i] = (local_old_b[local_m+i-1]+local_old_b[local_m+i+1]+local_old_b[2*local_m+i]+local_old_b[i+1]-nuevoVector[i])/4;
      }
      for(int i=1 ; i<local_n ; i++){
        for(int j=1 ; j<local_m ; j++){
          new_b[i*local_m+j] = (local_old_b[(i-1)*local_m+j]+local_old_b[(i+1)*local_m+j]+local_old_b[i*local_m+(j-1)]+local_old_b[i*local_m+(j+1)]-nuevoVector[i*local_m+j])/4;
        }
      }
    }else{
      for(int i=local_m-FronteraSup+1 ; i<local_m ; i++){
        new_b[local_m+i] = (local_old_b[(local_m-1)+i]+local_old_b[(local_m+1)+i]+local_old_b[local_m+(i-1)]+local_old_b[local_m+(i+1)]-nuevoVector[local_m+i])/4;
      }
      for(int i=1 ; i<local_n ; i++){
	for(int j=1 ; j<local_m ; j++){
          new_b[i*local_m+j] = (local_old_b[(i-1)*local_m+j]+local_old_b[(i+1)*local_m+j]+local_old_b[i*local_m+(j-1)]+local_old_b[i*local_m+(j+1)]-nuevoVector[i*local_m+j])/4;
        }
      }
      for(int i=1 ; i<local_m-FronteraInf ; i++){
        new_b[local_n*local_m+i] = (local_old_b[(local_n-1)*local_m+i]+local_old_b[(local_n+1)*local_m+i]+local_old_b[local_n*local_m+(i-1)]+local_old_b[local_n*local_m+(i+1)]-nuevoVector[local_n*local_m+i])/4;
      }
    }

    for(int i=1 ; i<local_n ; i++){
      for(int j=1 ; j<local_m ; j++){
        local_old_b[i*local_m+j] = new_b[i*local_m+j];
      }
    }
  }

  double tstop = gettime();
  printf("\nTime taken was  %f seconds\n", tstop-tstart);

  printf("tamano: %d ; GLOBAL_SIZE: %d\n", tamano, global_size);
  //aca junto los pedazos que separe en el scatter
  MPI_Gather(nuevoVector, tamano, MPI_FLOAT, nuevo, tamano, MPI_FLOAT, 0, MPI_COMM_WORLD);



  if(rank==0){
    pgmwrite(filename2, nuevo, n, m);
  }

  delete[] edge;
  delete[] nuevo;
  delete[] local_edge;
  delete[] local_old_b;
  delete[] new_b;
  delete[] buff;

  MPI_Finalize();

  return 0;
}
