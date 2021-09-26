#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>


int main(int argc,char **argv){

	MPI_Init(&argc,&argv);
	
	int rank,size,length;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	MPI_Status status;

	// the barrier statement will controlled by this array. the barrier will be opened when all the elemtns of the array are >0.
	int a[size]; //every process fills the array element with it's rank+1. 
	int num=10;
	
	if(rank==0){
		a[rank]=rank+1;
		printf("I'm rank %d and my value is %d.",rank,num);
		printf("I reached the barrier and waiting for the completion of next processes\n");
		
		//sending to the next process
		MPI_Send(&num,1,MPI_INT,(rank+1)%size,rank,MPI_COMM_WORLD);
		
		//receving from the last process
		MPI_Recv(&num,1,MPI_INT,size-1,size-1,MPI_COMM_WORLD,&status);
		
		/* reaching this point means that all the processes are executed completely. the gates to enter this statement will only open after the execution of all 				the processes. */
		printf("\n\nAll the processes reached the barrier.Barrier is opened.\n\n");
	}
	else{
		a[rank]=rank+1;
		printf("I'm rank %d and my value is %d.",rank,num);
		num--;
		
		printf("I reached the barrier and waiting for the completion of next processes\n");
		printf("*--------------------------------------------------------------------------------------------------------*\n");
		
		MPI_Send(&num,1,MPI_INT,(rank+1)%size,rank,MPI_COMM_WORLD);		
	}
	
	MPI_Finalize();
	return 0;
}






