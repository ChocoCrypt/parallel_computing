#include <cstdio>
#include <unistd.h>
#include <sched.h>
#include <mpi.h>

int main(int argc , char* argv[]){
    int rank , size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD , &size);
    printf("I'm MPI Process %d of %d I'm at core %d \n" , rank, size, sched_getcpu());
    sleep(1);
    MPI_Finalize();
    return 0;
}
