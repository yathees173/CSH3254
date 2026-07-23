#include<mpi.h>
#include<stdio.h>
int main() {
	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	MPI_Status sta;
	/*
	if (pid==0) {
		int num[400];
		for (int i = 0; i < 400; i++) {
			num[i] = i + 1;
		}

		if (400%np==0) {
			int d = 400 / np;
			for (int i = 1; i <= np; i++) {
				for (int j = 1; j <= d; j++) {
					MPI_Send();
				}

			}
		}
		else {
			printf("P should be divisible by 400");
			return 0;
		}
	}
	....................

	if (pid==0) {
		int a1[] = { 1,2,3,4,5,6,7,8 };
		int a2[] = { 9,10,11,12,13,14,15,16 };
		for (int i = 1; i <= 8; i++) {
			int num[] = { a1[i-1],a2[i-1] };
			MPI_Send(num, 2, MPI_INT, i, i, MPI_COMM_WORLD);
		}

		int totsum = 0;
		for (int i = 1; i <= 8; i++) {
			int sum;
			MPI_Recv(&sum, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
			totsum = totsum + sum;
		}

		printf("Total Sum is %d", totsum);

	}

	else {
			int sum = 0;
			int num[2];
			MPI_Recv(&num, 2, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
			sum = num[0]+ num[1];
			MPI_Send(&sum, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
		}

	*/
	if (pid == 0) {
		int num = 33;
		for (int i = 1; i < np; i++) {
			MPI_Send(&num, 1, MPI_INT, i, 50, MPI_COMM_WORLD);
			printf("My process id is % d and I'm the sender to pid %d. \n", pid, i);
		}
	}

	else {
		int num;
		MPI_Recv(&num, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		printf("My process id is %d  I'm the receiver. Message is %d", pid, num);
	}

	MPI_Finalize();
	return 0;
}
