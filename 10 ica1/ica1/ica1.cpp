#include<mpi.h>
#include<stdio.h>
#include<math.h>
int main() {
	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	if (pid == 0) {
		int seqA[] = { 12, 25, 37, 44, 59, 63, 71, 82, 91, 10, 22, 35, 48, 50, 67, 73, 85, 90, 14, 18, 21, 
			27, 33, 39, 46, 52, 60, 66, 75, 88, 95, 99 };
		int seqB[] = { 11, 20, 35, 40, 55, 60, 70, 80, 90, 15, 25, 30, 45, 55, 65, 70, 80, 85, 10, 20, 22, 
			28, 30, 38, 48, 50, 62, 68, 72, 85, 90, 100 };

		for (int i = 1; i < np; i++) {
			MPI_Send(&seqA[i * 8], 8, MPI_INT, i, 50, MPI_COMM_WORLD);
			MPI_Send(&seqB[i * 8], 8, MPI_INT, i, 60, MPI_COMM_WORLD);
		}

		printf("\nMy ID is % d from A my values are ", pid);
		for (int i = 0; i < 8; i++) {
			printf(" %d", seqA[i]);
		}

		printf("\nMy ID is % d from B my values are ", pid);
		for (int i = 0; i < 8; i++) {
			printf(" %d", seqB[i]);
		}

		int part_dotM = 0;
		for (int i = 0; i < 8; i++) {
			part_dotM = part_dotM + seqA[i] * seqB[i];
		}

		int paSuSq_MA = 0;
		int paSuSq_MB = 0;
		for (int i = 0; i < 8; i++) {
			paSuSq_MA = paSuSq_MA + pow(seqA[i],2);//seqA[i] * seqA[i];
			paSuSq_MB = paSuSq_MB + seqB[i] * seqB[i];
		}

		int part_dot, part_sum_sqrA, part_sum_sqrB;
		for (int i = 1; i < np; i++) {
			MPI_Recv(&part_dot, 1, MPI_INT, i, 70, MPI_COMM_WORLD, &sta);
			part_dotM = part_dotM + part_dot;
			MPI_Recv(&part_sum_sqrA, 1, MPI_INT, i, 80, MPI_COMM_WORLD, &sta);
			paSuSq_MA = paSuSq_MA + part_sum_sqrA;
			MPI_Recv(&part_sum_sqrB, 1, MPI_INT, i, 90, MPI_COMM_WORLD, &sta);
			paSuSq_MB = paSuSq_MB + part_sum_sqrB;

		}

		printf("\nTotal dot product is %d", part_dotM);
		printf("\nTotal sum of squares A is %d ", paSuSq_MA);
		printf("\nTotal sum of squares B is %d ", paSuSq_MB);

		double cosine = part_dotM / (sqrt(paSuSq_MA) * sqrt(paSuSq_MB));
		printf("\n Cosine Similarity is %2f", cosine);

	}

	else {
		int subA[8],subB[8];
		MPI_Recv(subA,8,MPI_INT,0,50,MPI_COMM_WORLD,&sta);
		MPI_Recv(subB, 8, MPI_INT, 0, 60, MPI_COMM_WORLD, &sta);

		printf("\nMy ID is % d from A my received values are ", pid);
		for (int i = 0; i < 8; i++) {
			printf(" %d", subA[i]);
		}

		printf("\nMy ID is % d from B my received values are ", pid);
		for (int i = 0; i < 8; i++) {
			printf(" %d", subB[i]);
		}

		int part_dot = 0;
		for (int i = 0; i < 8; i++) {
			part_dot = part_dot + (subA[i] * subB[i]);
		}

		printf("\nMy ID is % d my part dot is %d", pid,part_dot);

		MPI_Send(&part_dot, 1, MPI_INT, 0, 70, MPI_COMM_WORLD);


		int part_sum_sqrA = 0;
		int part_sum_sqrB = 0;
		for (int i = 0; i < 8; i++) {
			part_sum_sqrA = part_sum_sqrA + (subA[i] * subA[i]);
			part_sum_sqrB = part_sum_sqrB + (subB[i] * subB[i]);
		}

		printf("\nMy ID is % d my sum square A is %d",pid, part_sum_sqrA);
		printf("\nMy ID is % d my sum square B is %d",pid, part_sum_sqrB);

		MPI_Send(&part_sum_sqrA, 1, MPI_INT, 0, 80, MPI_COMM_WORLD);
		MPI_Send(&part_sum_sqrB, 1, MPI_INT, 0, 90, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}

//MPI_Send(&a[i], 1, MPI_INT, i, 50, MPI_COMM_WORLD);
//MPI_Recv(&num2, 1, MPI_INT, 1, 50, MPI_COMM_WORLD, &sta);