//Many to one communication
/*
#include <mpi.h>
#include <stdio.h>

int main() {
    int np, pid;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    MPI_Status sta;

    if (pid == 0) {
        int num;
        for (int i = 1; i < np; i++) {
            MPI_Recv(&num, 1, MPI_INT, i, 50, MPI_COMM_WORLD, &sta);
            printf("My processor id is %d and I'm receiver. Message from %d is %d\n", pid, i, num);
        }
    }
    else {
        int num = 50;
        MPI_Send(&num, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
        printf("My processor id is %d and I'm sender. Sent message %d\n", pid, num);
    }

    MPI_Finalize();
    return 0;
}
*/
#include <mpi.h>
#include <stdio.h>

int main() {
    int np, pid;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    MPI_Status sta;

    if (pid == 0) {
        int num[8];
        for (int i = 1; i < np; i++) {
            MPI_Recv(&num[i], 1, MPI_INT, i, 50, MPI_COMM_WORLD, &sta);

        }
        for (int i = 1; i < np; i++) {
            printf("Array values: %d \n", num[i]);
        }
    }
    else {
        int num = pid * 10;
        MPI_Send(&num, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
        printf("My processor id is %d and I'm sender. Sent message %d\n", pid, num);
    }

    MPI_Finalize();
    return 0;
}

