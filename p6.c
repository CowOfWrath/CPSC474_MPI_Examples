#include <stdio.h>

#include "mpi.h"

int main(int argc, char *argv[]) {

	int n = 100;
	int a[100];
	int i;

	for (i = 0; i < n; i++) a[i] = -1;

	int rank;
	int size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if ( rank == 0 )
		for ( i = 0; i < n; i++ ) a[i] = i;
	else {
		printf("Process %d, a[%d] = %d\n", rank, rank, a[rank]);
	}

	MPI_Bcast(&a, n, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank !=0) {
		printf("After broadcast, at process %d, a[%d] = %d\n", rank, rank, a[rank]);
	}

	MPI_Finalize();
	return 0;
}
