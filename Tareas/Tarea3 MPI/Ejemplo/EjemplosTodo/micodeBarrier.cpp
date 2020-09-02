#include <cstdio> 
#include <cstdlib> 
#include <cmath> 
#include <mpi.h> 

int main(int argc , char** argv){
	MPI_Init(&argc , &argv);
	int rank , size ;
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &size);

	if(rank == 0){
		printf("im busy \n");
		double res = 1.;
		for(int i = 0 ; i<1e6 ; i++){
			res *= cos(res)/res;
		}
		printf("ok now we can continue\n") ;
	}
	MPI_Barrier(comm);

	printf("hola mundo i am %d of %d \n " , rank, size);

	MPI_Finalize();

return 0;
	
}
