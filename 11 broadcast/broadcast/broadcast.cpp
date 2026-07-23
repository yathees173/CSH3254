#include<mpi.h>
#include<stdio.h>
int main() {
	int np, pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	int num;
	int arr[5];

	if (pid == 0) {
		num = 5;
		for (int i = 0; i < 5; i++) {
			arr[i] = (i + 1) * 10;
		}
		
	}

	MPI_Bcast(&num, 1, MPI_INT, 0, MPI_COMM_WORLD);
	printf("My Id is %d Recevied value is %d \n", pid, num);

	MPI_Bcast(&arr, 5, MPI_INT, 0, MPI_COMM_WORLD);
	printf("My Id is %d Recevied value is ", pid);
	for (int i = 0; i < 5; i++) {
		printf(" %d", arr[i]);
	}

	MPI_Finalize();
	return 0;
}
