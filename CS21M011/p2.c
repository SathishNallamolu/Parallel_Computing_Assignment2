#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>


int main(int argc,char **argv){

	MPI_Init(&argc,&argv);
	
	int rank,size,length;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	MPI_Status status;

	int num=10;
	
	if(rank==0){
		//sending the data to next process
		printf("Value sent by process %d is %d\n",rank,num);
		MPI_Send(&num,1,MPI_INT,(rank+1)%size,rank,MPI_COMM_WORLD);


		//receiving the data from previous process
		MPI_Recv(&num,1,MPI_INT,size-1,size-1,MPI_COMM_WORLD,&status);
		printf("Value received by process %d from process %d is %d\n",rank,size-1,num);		
	}
	else{
		//receiving the data from the parent process
		MPI_Recv(&num,1,MPI_INT,rank-1,rank-1,MPI_COMM_WORLD,&status);
		printf("Value received by process %d from process %d is %d\n",rank,rank-1,num);
		printf("*--------------------------------------------------------------------------*\n");
		
		--num;
		
		//sending the data next process.if it is the last process,send it to parent process.
		printf("I'm process %d.I'm decrementing the value and send to process %d\n",rank,(rank+1)%size);
		printf("Value sent by process %d is %d\n",rank,num);
		MPI_Send(&num,1,MPI_INT,(rank+1)%size,rank,MPI_COMM_WORLD);		
	}
	
	MPI_Finalize();
	return 0;
}






