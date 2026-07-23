/*
#include<stdio.h>
#include<mpi.h>
int main() {
	int np, pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD,&pid);

	int arr[48];
	if (pid == 0) {
		int temp[] = {6,4,3,7,5,6,7,8,3,7,7,8,7,5,4,3,3,5,
					  4,3,2,4,3,5,8,8,9,6,7,9,9,10,12,14,12,11,
						12,12,13,9,6,5,10,4,2,11,5,3};
		for (int i = 0; i < 48; i++) {
			arr[i] = temp[i];
		}
	}

	int p_arr[12],pol_arr[12],pol[48];

	MPI_Scatter(&arr,12,MPI_INT,&p_arr,12,MPI_INT,0,MPI_COMM_WORLD);

	printf("\nMy id is %d received matrix are ", pid);
	for (int i = 0; i < 12; i+=3) {
		printf("\n");
		for (int j = i; j < i + 3; j++) {
			printf("%d ", p_arr[j]);
		}
		pol_arr[i] = p_arr[i] + 5;
		pol_arr[i+1] = p_arr[i+1] + 6;
		pol_arr[i+2] = p_arr[i+2] + 7;
	}

	MPI_Gather(&pol_arr,12,MPI_INT,&pol,12,MPI_INT,0,MPI_COMM_WORLD);

	if (pid == 0) {
		printf("\nPolygon matrix are :");
		for (int i = 0; i < 48; i += 3) {
			printf("\n");
			for (int j = i; j < i + 3; j++) {
				printf("%d ", pol[j]);
			}
		}
	}
	
	MPI_Finalize();
	return 0;
}

*/

#include<stdio.h>
#include<mpi.h>
int main() {
	int np, pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	int arr[48];
	if (pid == 0) {
		int temp[] = { 6,4,3,7,5,6,7,8,3,7,7,8,7,5,4,3,3,5,
					  4,3,2,4,3,5,8,8,9,6,7,9,9,10,12,14,12,11,
						12,12,13,9,6,5,10,4,2,11,5,3 };
		for (int i = 0; i < 48; i++) {
			arr[i] = temp[i];
		}
	}

	int p_arr[3], pol_arr[3], pol[48];

	MPI_Scatter(arr, 3, MPI_INT, p_arr, 3, MPI_INT, 0, MPI_COMM_WORLD);

	printf("\nMy id is %d received matrix are ", pid);
	for (int i = 0; i < 3; i ++) {
		printf("%d ", p_arr[i]);
	}
	pol_arr[0] = p_arr[0] + 5;
	pol_arr[1] = p_arr[1] + 6;
	pol_arr[2] = p_arr[2] + 7;

	MPI_Gather(pol_arr, 3, MPI_INT, pol, 3, MPI_INT, 0, MPI_COMM_WORLD);

	if (pid == 0) {
		printf("\nPolygon coordinates are :");
		for (int i = 0; i < 48; i += 3) {
			printf("\n");
			for (int j = i; j < i + 3; j++) {
				printf("%d ", pol[j]);
			}
		}
	}

	MPI_Finalize();
	return 0;
}

/*
//ICA2 IT 2022
#include<stdio.h>
#include<mpi.h>

int main() {
	int np, pid;
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	int s1[64], s2[64];

	if (pid == 0) {
		int t1[] = { 1,1,0,0,0,0,1,1, 1,0,1,1,0,1,1,0, 0,1,0,0,0,0,0,1, 0,0,0,0,0,1,1,0, 
			1,1,1,1,0,1,0,1, 1,0,1,0,0,0,1,0, 0,1,0,1,0,1,0,1, 0,0,0,1,0,1,0,0
		};
		int t2[] = { 1,0,0,0,1,0,0,1, 1,1,0,1,1,1,0,0, 1,0,0,1,0,1,1,1, 0,1,0,0,0,1,1,0, 
			1,1,0,1,1,1,0,1, 1,1,1,0,1,0,1,1, 0,1,1,1,1,0,0,0, 1,0,1,1,1,0,1,1 };

		for (int i = 0; i < 64; i++) {
			s1[i] = t1[i];
			s2[i] = t2[i];
		}
	}

	int p_s1[8], p_s2[8],count=0,ha[8];
	MPI_Scatter(s1,8,MPI_INT,p_s1,8,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(s2,	8, MPI_INT, p_s2, 8, MPI_INT, 0, MPI_COMM_WORLD);

	printf("\nMy processor id is %d", pid);
	printf("\nReceived Data from sequence 1 is: ");
	for (int i = 0; i < 8; i++) {
		printf("%d ", p_s1[i]);
	}
	printf("\nReceived Data from sequence 2 is: ");
	for (int i = 0; i < 8; i++) {
		printf("%d ", p_s2[i]);
	}
	for (int i = 0; i < 8; i++) {
		if (p_s1[i] != p_s2[i]) {
			count++;
		}
	}
	printf("\nHamming Distances: %d",count);

	MPI_Gather(&count, 1, MPI_INT, ha, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (pid == 0) {
		int tot = 0;
		printf("\nHamming Distances are: ");
		for (int i = 0; i < 8; i++) {
			printf("%d ", ha[i]);
			tot += ha[i];
		}
		printf("\nTotal Hamming Distance: %d at PID: %d", tot, pid);
	}

	MPI_Finalize();
	return 0;
}
*/