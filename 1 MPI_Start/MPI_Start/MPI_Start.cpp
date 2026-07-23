#include <mpi.h>
#include <stdio.h>
int main()
{
	int np;
	int pid;
	MPI_Init(NULL, NULL); // initialize mpi environment
	MPI_Comm_size(MPI_COMM_WORLD, &np); //number of proceesing element
	MPI_Comm_rank(MPI_COMM_WORLD, &pid); // assign unique id
	printf("\n Hello world . . . \n My pid= %d \n No_of_process= %d", pid, np);
	MPI_Finalize();
	return 0;
}