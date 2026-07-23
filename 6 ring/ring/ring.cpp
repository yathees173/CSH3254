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
		int num = 99;
		MPI_Send(&num, 1, MPI_INT, 1, 50, MPI_COMM_WORLD);
		printf("I'm Master... My id is %d I send %d to id 1 \n", pid, num);
		int num1;
		MPI_Recv(&num1, 1, MPI_INT, np - 1, 50, MPI_COMM_WORLD, &sta);
		printf("I'm Maste... My id is %d I recive %d from id %d \n", pid, num1, np - 1);
	}

	else {
		
			int num;
			MPI_Recv(&num, 1, MPI_INT, pid - 1, 50, MPI_COMM_WORLD, &sta);
			printf("My id is %d I recive %d from id %d \n", pid,num,pid - 1);
			MPI_Send(&num, 1, MPI_INT, (pid + 1) % np, 50, MPI_COMM_WORLD);
			printf("My id is %d I sent %d to id %d \n", pid, num, (pid + 1) % np);

	}

	MPI_Finalize();
	return 0;
}