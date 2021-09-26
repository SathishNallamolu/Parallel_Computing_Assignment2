#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>


int main(int argc,char **argv){

	MPI_Init(&argc,&argv);
	
	int rank,size,length;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	MPI_Status status;

	if(rank==0){
		int n,i,res=0;
		printf("enter no. of elemnts in vector:");
		scanf("%d",&n);
		int a[n];
		
		MPI_Send(&n,1,MPI_INT,1,1,MPI_COMM_WORLD);
		
		printf("enter elemnts in vector:\n");
		for(i=0;i<n;i++)
			scanf("%d",&a[i]);

		//sending array to the next process
		MPI_Send(a,n,MPI_INT,1,2,MPI_COMM_WORLD);
		
		//receiving the sum of elements from the previous process.
		MPI_Recv(&res,1,MPI_INT,1,3,MPI_COMM_WORLD,&status);
		
		printf("Product:%d\n",res);
		
		exit(0);
	}
	else{
		int n1,i;
		
		MPI_Recv(&n1,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);	
		
		int b[n1];
		
		//receiving the array from the parent process and computing the result
		MPI_Recv(b,n1,MPI_INT,0,2,MPI_COMM_WORLD,&status);
		
		int r=0;
		for(i=0;i<n1;i++)
			r+=b[i]*b[i];
		
		//sending the result to parent process
		MPI_Send(&r,1,MPI_INT,0,3,MPI_COMM_WORLD);
	}


	MPI_Finalize();
	
	return 0;
}
