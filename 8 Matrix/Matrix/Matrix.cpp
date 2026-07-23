
#include <mpi.h>
#include <stdio.h>

int main() {
	int np, pid;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;
	if (pid == 0) {
		int A[8][8] = {
			{2,4,6,8,1,3,5,7},
			{1,3,5,7,2,4,6,8},
			{9,11,13,15,2,4,6,8},
			{10,12,14,16,1,3,5,7},
			{5,7,9,11,3,6,8,2},
			{6,8,10,12,4,7,9,3},
			{13,15,17,19,5,8,10,4},
			{14,16,18,20,6,9,11,5}
		};

		int X[] = {1,2,3,4,5,6,7,8};

		for (int i = 1; i < np; i++) {
			MPI_Send(X,8,MPI_INT,i,50,MPI_COMM_WORLD);
			MPI_Send(A[i],8,MPI_INT,i,60,MPI_COMM_WORLD);
		}

		printf("My id is %d  values are ", pid);
		for (int i = 0; i < 8; i++) {
			printf("%d ", A[0][i]);
		}

		int val = 0;
		for (int i = 0; i < 8; i++) {
			val = val + X[i] * A[0][i];
		}
		
		//printf("\nvalue is %d ", val);
		int out[8];
		out[0] = val;

		for (int i = 1; i < 8; i++) {
			MPI_Recv(&out[i], 1, MPI_INT, i,70, MPI_COMM_WORLD, &sta);
		}

		printf("\nThe multiplication of A*X is : ");
		for (int i = 0; i < 8; i++) {
			printf("\n%d", out[i]);
		}

	}

	else {
		int X[8],A[8];
		MPI_Recv(X,8,MPI_INT,0,50,MPI_COMM_WORLD,&sta);
		MPI_Recv(A, 8, MPI_INT, 0, 60, MPI_COMM_WORLD,&sta);

		printf("My id is %d recevied values are ", pid);
		for (int i = 0; i < 8; i++) {
			printf("%d ", A[i]);
		}

		int val=0;
		for (int i = 0; i < 8; i++) {
			val = val + X[i] * A[i];
		}
		//printf("\nvalue is %d ", val);
		
		MPI_Send(&val, 1, MPI_INT, 0,70, MPI_COMM_WORLD);

	}

	MPI_Finalize();
	return 0;
}

/*

#include <mpi.h>
#include <stdio.h>

int main() {
	int np, pid;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	int A[8][8] = {
		{2,4,6,8,1,3,5,7},
		{1,3,5,7,2,4,6,8},
		{9,11,13,15,2,4,6,8},
		{10,12,14,16,1,3,5,7},
		{5,7,9,11,3,6,8,2},
		{6,8,10,12,4,7,9,3},
		{13,15,17,19,5,8,10,4},
		{14,16,18,20,6,9,11,5}
	};

	int X[8] = { 1,2,3,4,5,6,7,8 };
	int row[8];
	int partial = 0;
	int Y[8];

	MPI_Bcast(X, 8, MPI_INT, 0, MPI_COMM_WORLD);

	MPI_Scatter(A, 8, MPI_INT,
		row, 8, MPI_INT,
		0, MPI_COMM_WORLD);

	for (int j = 0; j < 8; j++) {
		partial += row[j] * X[j];
	}

	MPI_Gather(&partial, 1, MPI_INT,
		Y, 1, MPI_INT,
		0, MPI_COMM_WORLD);

	if (pid == 0) {
		printf("Final result vector: \n");
		for (int i = 0; i < 8; i++) {
			printf("%d \n", Y[i]);
		}
		printf("\n");
	}

	MPI_Finalize();
	return 0;
}

*/