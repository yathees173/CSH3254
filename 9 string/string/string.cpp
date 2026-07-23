
#include<mpi.h>
#include<stdio.h>
int main() {
	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	if (pid == 0) {
		char a[] =  "I am from UOV" ;
		MPI_Send(a, sizeof(a), MPI_CHAR, 1, 50, MPI_COMM_WORLD);
	}

	else if (pid == 1) {
		char a[40];
		MPI_Recv(&a, 40, MPI_CHAR, 0, 50, MPI_COMM_WORLD, &sta);
		printf("I am the receiver my id %d received value is %s", pid,a);
		
	}

	MPI_Finalize();
	return 0;
}

//MPI_Send(&a[i], 1, MPI_INT, i, 50, MPI_COMM_WORLD);
//MPI_Recv(&num2, 1, MPI_INT, 1, 50, MPI_COMM_WORLD, &sta);
