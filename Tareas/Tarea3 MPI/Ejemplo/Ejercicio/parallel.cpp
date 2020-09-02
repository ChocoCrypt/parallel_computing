/*************************************
Parallel version of traffic_ser.cpp
The size of the grid must be divisible
by the number of processes
**********************************/

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <random>
#include <mpi.h>
using namespace std;

double gettime(){
  return MPI_Wtime();
}

int init_road(int *road, int size, float dens, long seed) {
  default_random_engine rng;
  rng.seed(seed);
  uniform_int_distribution<int> uniform(0,size-1);

  for(int i = 0; i < size; ++i)
    road[i] = 0;

  int Ncars = int(round(size*dens));
  int count = Ncars;
  while(count > 0){
    int position = uniform(rng);
    if(road[position] == 0){
      road[position] = 1;
      count--;
    }
  }
  return Ncars;
}

int update(int *old_road, int *road, int size) {
  int moved = 0;
  for(int i = 1; i < size+1; ++i){
    int prev = i-1;
    int next = i+1;
    if(old_road[i] == 0){
      if(old_road[prev] == 1)
	road[i] = 1;
      else
	road[i] = 0;
    }else{
      if(old_road[next] == 0){
	road[i] = 0;
	moved++;
      }else
	road[i] = 1;
    }
  }
  return moved;
}

float simulation(int size, float dens, long seed, int Niter) {
  //Find out rank, size
  int rank, nproc;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);

  //printf("%d %d\n",rank,size);
  
  //Print initial parameters if rank is 0------------------------
  if(rank == 0){
    printf("Length of road is %d\n", size);
    printf("Number of iterations is %d \n", Niter);
    printf("Target density of cars is %.3f \n", dens);
    printf("Running on %d processes\n", size);
  }
  //-------------------------------------------------------------
  
  //Get local number of cells and allocate memmory---------------
  int local_size = size / nproc;
  int *road1 = new int[local_size+2];
  int *road2 = new int[local_size+2];
  //-------------------------------------------------------------

  //initialize road if rank is 0---------------------------------
  int Ncars;
  int *road = nullptr;
  if(rank == 0){
    road = new int[size];
    printf("Initialising road ...\n");
    Ncars = init_road(road, size, dens, seed);
    printf("...done\n");
    printf("Actual density of cars is %f\n\n", float(Ncars)/size);
    // //
    // for(int i = 0; i < size; ++i)
    //   printf("%d ",road[i]);
    // printf("\n");
    // //
    printf("Scattering data...\n");
  }
  //------------------------------------------------------------

  // scatter data to all processes-------------------------------
  // Leave one space at the beginning and one at the end of old_road to
  // store the last element of previous process and the first element
  // of next process
  MPI_Scatter(road, local_size, MPI_INT, &road1[1], local_size, MPI_INT, 0, MPI_COMM_WORLD);
  if(rank == 0)
    printf("...done\n");
  
  float av_vel = 0;
  int *dummy;
  for(int i = 0; i < Niter; ++i){
    int prevproc = (rank-1 == -1) ? nproc-1 : rank-1;
    int nextproc = (rank+1 == nproc) ? 0 : rank+1; 
    
    //send / recieve first and last elements----------------------
    MPI_Status status;
    MPI_Sendrecv(&road1[local_size], 1, MPI_INT, nextproc, 1,
  		 &road1[0], 1, MPI_INT, prevproc, 1,
  		 MPI_COMM_WORLD, &status);
    MPI_Sendrecv(&road1[1], 1, MPI_INT, prevproc, 1,
  		 &road1[local_size+1], 1, MPI_INT, nextproc, 1,
  		 MPI_COMM_WORLD, &status);
    //------------------------------------------------------------

    // //
    // printf("%d: ",rank);
    // for(int i = 0; i <= local_size+1; ++i)
    //   printf("%d ",road1[i]);
    // printf("\n");
    // //
    
    int moved = update(road1, road2, local_size);

    int tot_moved;
    MPI_Allreduce(&moved, &tot_moved, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    // //
    // printf("moved: %d\n",moved);
    // //
    
    if(rank == 0){
      float vel = float(tot_moved) / Ncars;
      av_vel += vel;
    }

    //   // //
    //   // //printf("moved: %d\n",moved);
    //   // for(int i = 0; i < local_size; ++i)
    //   //   printf("%d ",road2[i]);
    //   // printf("\n");
    //   // //
    
    dummy = road1;
    road1 = road2;
    road2 = dummy;

    // //
    // MPI_Gather(&road1[1], local_size, MPI_INT, road, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    // if(rank == 0){
    //   for(int i = 0; i < size; ++i)
    // 	printf("%d ",road[i]);
    //   printf("\n");
    // }
    // //
  }

  MPI_Gather(&road1[1], local_size, MPI_INT, road, local_size, MPI_INT, 0, MPI_COMM_WORLD);
  if(rank == 0)
    av_vel /= Niter;

  
  
  
  if(rank == 0)
    delete[] road;
  
    
  // delete[] road1;
  // delete[] road2;

  return av_vel;
}

int main(int argc, char** argv) {
  int size = atoi(argv[1]);
  float dens = atof(argv[2]);
  long seed = 132;
  
  int Niter = 10;


  //initialize mpi environment and get rank/size-----------------
  MPI_Init(nullptr, nullptr);
  //-------------------------------------------------------------
  
  double t_start = gettime();
  float av_v = simulation(size, dens, seed, Niter);
  double t_stop = gettime();

  printf("Average velocity: %f\n",av_v);
  
  MPI_Finalize();

  printf("Time: %f s\n",t_stop-t_start);
  
  return 0;
}

