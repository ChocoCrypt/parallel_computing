#include <iostream>
#include <unistd.h>
#include <mpi.h>
#include <sched.h>

int main(int argc , char**argv){
    MPI_Init(&argc,&argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD , &rank);
    MPI_Comm_size(MPI_COMM_WORLD , &size);

    if(size <2){
        printf("debe ser mas grande que 1/n");
        MPI_Abort(MPI_COMM_WORLD , 1);
    }
    int number;
    if(rank == 0){
        number = -1 ;
        MPI_Send(&number , 1 , MPI_INT , 1 , 0 , MPI_COMM_WORLD );
        printf("Process 1 recived %d " , number);
    }
    MPI_Finalize();
    return 0;
}
