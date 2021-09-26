#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include<time.h>

int main(int argc,char **argv){

	MPI_Init(&argc,&argv);
	
	int rank,size,length;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	MPI_Status status;
	
	srand(time(0));
	
	if(rank==0){
		int x,n,i,m;
	
		printf("enter no. of iterations:");
		scanf("%d",&m);
		
		MPI_Send(&m,1,MPI_INT,1,2,MPI_COMM_WORLD);

		printf("enter no. of elements:");
		scanf("%d",&n);
		
		MPI_Send(&n,1,MPI_INT,1,1,MPI_COMM_WORLD);
		
		int a[n];
		for(i=0;i<n;i++)
			a[i]=i+1;
			
		//generating a random number(process) to send the array
		x=rand()%size;
		
		//if same rank is generated,we will send the array to next process by default.
		if(x==rank){
			x+=1;
			x=x%size;
		}
		printf("\nI'm process %d and sending array to process %d\n",rank,x);
		
		//sending the array to the randomly genearted process
		MPI_Send(a,n,MPI_INT,x,rank,MPI_COMM_WORLD);
	}
	
	else{
		int x1,n1,m1;
		
		MPI_Recv(&m1,1,MPI_INT,0,2,MPI_COMM_WORLD,&status);
		
		MPI_Recv(&n1,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		int b[n1];
		
		MPI_Recv(b,n1,MPI_INT,status.MPI_SOURCE,status.MPI_SOURCE,MPI_COMM_WORLD,&status);	
		printf("\nI'm process %d and received array from process %d\n",rank,status.MPI_SOURCE);
		
		if(m1>0){
			//generating a random number(process) to send the array
			x1=rand()%size;
			
			//if same rank is generated,we will send the array to next process by default.
			if(x1==rank){
				x1=x1+1;
				x1=x1%size;
			}
			printf("\nI'm process %d and sending array to process %d\n",rank,x1);
			
			//sending the array to the randomly genearted process
			MPI_Send(b,n1,MPI_INT,x1,rank,MPI_COMM_WORLD);
			m1--;	
		}
	}
	
	MPI_Finalize();
	
	return 0;
}

