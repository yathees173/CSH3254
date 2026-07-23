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
		int a[] = { 10,20,30,40,50,60 };
		for (int i = 1; i < 6; i++) {
			MPI_Send(&a[i], 1, MPI_INT, i, 50, MPI_COMM_WORLD);
			printf("I'm Master... My id is %d I sent %d to id %d \n", pid, a[i], i);
		}


		int num2;
		MPI_Recv(&num2, 1, MPI_INT, 1, 50, MPI_COMM_WORLD, &sta);
		printf("I'm Master My id is %d I receive %d from id 1 \n", pid,num2);

		int num3;
		MPI_Recv(&num3, 1, MPI_INT, 3, 50, MPI_COMM_WORLD, &sta);
		printf("I'm Master My id is %d I receive %d from id 3 \n", pid,num3);

		int sum = a[0] + num2 + num3;
		printf("Sum is %d", sum);
	}

	else if (pid == 1) {
		int num,num1,num2;
		MPI_Recv(&num, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		printf("My id is %d I receive %d from id 0 \n", pid, num);
		MPI_Recv(&num1, 1, MPI_INT, 2, 50, MPI_COMM_WORLD, &sta);
		printf("My id is %d I receive %d from id 2 \n", pid, num1);

		num2 = num + num1;
		MPI_Send(&num2, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
		printf("My id is %d I send %d to id 0 \n", pid, num2);
		
	}

	else if (pid == 2) {
		int num;
		MPI_Recv(&num, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		printf("My id is %d I receive %d from id 0 \n", pid, num);
		MPI_Send(&num, 1, MPI_INT, 1, 50, MPI_COMM_WORLD);
		printf("My id is %d I send %d to id 1 \n", pid, num);
	}

	else if (pid == 3) {
		int num1,num2,num3;
		MPI_Recv(&num1, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		printf("My id is %d I receive %d from id 0 \n", pid, num1);
		MPI_Recv(&num2, 1, MPI_INT, 4, 50, MPI_COMM_WORLD, &sta);
		printf("My id is %d I receive %d from id 4 \n", pid, num1);
		num3 = num1 + num2;
		MPI_Send(&num3, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
		printf("My id is %d I send %d to id 0 \n", pid, num3);

	}
	

	else if (pid == 4) {
		int num1,num2,num3;
		MPI_Recv(&num1, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		printf("My id is %d I receive %d from id 0 \n", pid, num1);
		MPI_Recv(&num2, 1, MPI_INT, 5, 50, MPI_COMM_WORLD, &sta);
		printf("My id is %d I receive %d from id 5 \n", pid, num2);
		num3 = num1 + num2;
		MPI_Send(&num3, 1, MPI_INT, 3, 50, MPI_COMM_WORLD);
		printf("My id is %d I send %d to id 0 \n", pid, num3);

	}

	else {
		int num;
		MPI_Recv(&num, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		printf("My id is %d I receive %d from id 3 \n", pid, num);
		MPI_Send(&num, 1, MPI_INT, 4, 50, MPI_COMM_WORLD);
		printf("My id is %d I send %d to id 4 \n", pid, num);
	}

	MPI_Finalize();
	return 0;
}