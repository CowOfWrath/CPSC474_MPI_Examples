#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int electing = 1;
	int msg = -1;
	int nummsg = 0;

	MPI_Send(&rank, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

	while (electing) {
		if (rank != 0) {
			MPI_Recv(&msg, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Process rank %d >> Received msg = %d from process rank %d\n", rank, msg, rank - 1);
			nummsg += 1;
		}
	
		if (rank == 0) {
			MPI_Recv(&msg, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Process rank %d >> Received msg = %d from process rank %d\n", rank, msg, size - 1);
			nummsg += 1;
		}
	
		if (msg == rank) {
			printf("Process rank %d >> I am the leader\n", rank);
			electing = 0;
		}
		else if (msg > rank) {
			MPI_Send(&msg, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
			printf("Process rank %d >> Election finished\n", rank);
			electing = 0;
		}
		else {
			//do nothing
		}
	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	printf("Process rank %d >> I recieved %d messages\n", rank, nummsg);
	if (rank != msg && rank != 0) {
		MPI_Recv(&msg, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		nummsg += msg;
	}
	else if(rank != msg && rank == 0){
		MPI_Recv(&msg, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		nummsg += msg;
	}
	MPI_Send(&nummsg, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

	if (rank == msg) {
		MPI_Recv(&msg, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process rank %d >> Total number of messages = %d\n", rank, msg);
	}

	MPI_Finalize();
	return 0;
}	
