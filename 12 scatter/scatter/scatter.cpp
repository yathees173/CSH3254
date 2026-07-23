#include<mpi.h>
#include<stdio.h>
int main() {
	int np, pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	int sendbuf[4];
	int recvbuf;


	if (pid == 0) {
		int temp[4];
		for (int i = 1; i < 5; i++) {
			sendbuf[i - 1] = i * 10;
		}

		/*
		sendbuf[0] = 10 ;
		sendbuf[1] = { 20 };
		sendbuf[2] = { 30 };
		sendbuf[3] = { 40 };
		*/
	}

	MPI_Scatter(&sendbuf, 1, MPI_INT,
		&recvbuf, 1, MPI_INT,
		0, MPI_COMM_WORLD);

	printf("My Id is %d Recevied value is %d \n", pid, recvbuf);


	MPI_Finalize();
	return 0;
}
