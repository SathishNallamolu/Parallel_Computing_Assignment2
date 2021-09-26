#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char **argv){

	MPI_Init(&argc,&argv);
	
	int rank,size,length;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	MPI_Status status;
	
	if(rank==0){
		int n,sum=0,i;
		printf("enter no. of elemnts:");
		scanf("%d",&n);
		
		MPI_Send(&n,1,MPI_INT,1,3,MPI_COMM_WORLD);
		
		int a[n];
		printf("enter elemnts of the array:\n");
		for(i=0;i<n;i++)
			scanf("%d",&a[i]);

		//sending array to the next process
		MPI_Send(a,n,MPI_INT,1,1,MPI_COMM_WORLD);
		
		//receiving the sum of elements from the previous process.
		MPI_Recv(&sum,1,MPI_INT,1,2,MPI_COMM_WORLD,&status);
		
		//sleep(2);
		printf("SUM:%d\n",sum);
		exit(0);
	}
	else{
		int i,sum=0,n1;
		
		MPI_Recv(&n1,1,MPI_INT,0,3,MPI_COMM_WORLD,&status);
		
		int b[n1];


		//receiving the array from parent process and storing in array b.
		MPI_Recv(b,n1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		printf("I'm rank %d and received the array from rank %d.I'm calculating the sum\n",rank,status.MPI_SOURCE);

		//calculating the sum
		for(i=0;i<n1;i++)
			sum=sum+b[i];
		
		//send the result to parent process..
		printf("I'm rank %d and calcualted the sum as %d.Now,I am sending this to process %d(my source)\n",rank,sum,status.MPI_SOURCE);
		MPI_Send(&sum,1,MPI_INT,0,2,MPI_COMM_WORLD);
		
	}
	
	MPI_Finalize();
	
	return 0;
}


