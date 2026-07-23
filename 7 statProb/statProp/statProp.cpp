#include<mpi.h>
#include<stdio.h>
int main() {
	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	//MPI_Recv(&num, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
	//MPI_Send(&a[i], 1, MPI_INT, i, 50, MPI_COMM_WORLD);

	if (pid == 0) {
		int seq1[] = { 45, 41, 92, 79, 11, 83, 97, 91, 98, 67, 53, 34, 68, 72, 76, 12,
						78, 59, 64, 06, 89, 62, 26, 23, 17, 35, 36, 18, 25, 55, 43, 56 };

		int seq2[] = { 05, 18, 96, 63, 23, 10, 42, 34, 58, 84, 35, 61, 51, 41, 01, 13,
						45, 22, 53, 44, 56, 96, 62, 71, 67, 72, 78, 46, 83, 91, 97, 98 };

		for (int i = 1; i < np; i++) {
			MPI_Send(&seq1, 32, MPI_INT, i, 50, MPI_COMM_WORLD);
			MPI_Send(&seq2[i * 8], 8, MPI_INT, i, 60, MPI_COMM_WORLD);
		}

		printf("My id is %d Received numbers are ", pid);
		for (int i = 0; i < 8; i++) {
			printf("%d ", seq2[i]);
		}

		int recev_sum, sum_inter = 0;
		for (int i = 1; i < np; i++) {
			MPI_Recv(&recev_sum, 1, MPI_INT, i, 70, MPI_COMM_WORLD, &sta);
			sum_inter = sum_inter + recev_sum;
		}

		int count = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 32; j++) {
				if (seq2[i] == seq1[j]) {
					count++;
					break;
				}
			}
		}

		printf("\nMy id is %d Intersection Count is %d", pid, count);

		int final_int_sum = sum_inter + count;

		printf("\nMy id is %d Total Intersection Count is %d", pid, final_int_sum);

		double Dice_Coefficient = (2.0 * final_int_sum) / (32 * 2);

		printf("\nDice Coefficeient is %.2f", Dice_Coefficient);

		double similarity = Dice_Coefficient * 100;

		printf("\nSimilar is %.2f", similarity);


	}

	else {
		int seq1[32];
		MPI_Recv(&seq1, 32, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		int seq2[8];
		MPI_Recv(&seq2, 8, MPI_INT, 0, 60, MPI_COMM_WORLD, &sta);

		printf("My id is %d Received numbers are ", pid);
		for (int i = 0; i < 8; i++) {
			printf("%d ", seq2[i]);
		}

		int count = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 32; j++) {
				if (seq2[i] == seq1[j]) {
					count++;
					//break;
				}
			}
		}

		printf("\nMy id is %d Intersection Count is %d", pid, count);

		MPI_Send(&count, 1, MPI_INT, 0, 70, MPI_COMM_WORLD);

	}


	MPI_Finalize();
	return 0;
}