#include <stdio.h>

#include "mpi.h"

int main( int argc, char *argv[] )

{

int rank, size;

MPI_Init( &argc, &argv );

MPI_Comm_rank( MPI_COMM_WORLD, &rank );

MPI_Comm_size( MPI_COMM_WORLD, &size );

int number;
number = 100;

MPI_Request ireq;

MPI_Status istatus;

if (rank == 0) {

number = -1;

MPI_Isend(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &ireq);

printf("Process 0 sent number %d to process 0\n", number);

//MPI_Wait(&ireq, &istatus);

} else if (rank == 1) {

MPI_Irecv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &ireq);

//MPI_Wait(&ireq, &istatus);

printf("Process 1 received number %d from process 0\n", number);

}

MPI_Finalize();

return 0;

}
