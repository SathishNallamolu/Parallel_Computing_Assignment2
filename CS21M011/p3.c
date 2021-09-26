#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc,char **argv){
	MPI_Init(&argc,&argv);
	
	int rank,size,length;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	MPI_Status status;
	
	
	if(!rank){
		int n,i,sum=0;
		printf("enter array size:");
		scanf("%d",&n);
		//np=atoi(argv[2]);
		int sizeof_each_array=n/size;  //calcualting the size of each array. total elements/total processes
		int a[sizeof_each_array];

		MPI_Send(&n,1,MPI_INT,1,10,MPI_COMM_WORLD);    //send array size to process1
		
		//finding the sum of the array allocated to parent process.
		for(i=0;i<sizeof_each_array;i++){
			a[i]=i;	
			sum+=a[i];
		}
		
		//sending the start index of the array to next process
		MPI_Send(&i,1,MPI_INT,1,1,MPI_COMM_WORLD);
		
		//sending sum to next process. this varaible is resposnsible for storing the final sum
		MPI_Send(&sum,1,MPI_INT,1,0,MPI_COMM_WORLD);
		
		// receving the final sum from the last process
		MPI_Recv(&sum,1,MPI_INT,size-1,size-1,MPI_COMM_WORLD,&status);
				
		printf("SUM:%d\n",sum);
	}
	else{
	
		int n1,j,k,sum1;
		int sizeof_each_array=n1/size;
		
		MPI_Recv(&n1,1,MPI_INT,0,10,MPI_COMM_WORLD,&status);
		
		// receiving of the start index of the array to compute sum
		MPI_Recv(&j,1,MPI_INT,rank-1,rank,MPI_COMM_WORLD,&status);	
		
		// receving the sum computed by the previous process. adds that sum to the calcuated sum and sends to next process.
		MPI_Recv(&sum1,1,MPI_INT,rank-1,rank-1,MPI_COMM_WORLD,&status);	
		
		int a[sizeof_each_array];
		for(;j<n1/size;j++){
			a[j]=j;
			sum1+=a[j];
		}	
		
		//sending the start index of the array to next process
		MPI_Send(&j,1,MPI_INT,rank+1,rank+1,MPI_COMM_WORLD);
		
		//sending sum to next process. 
		MPI_Send(&sum1,1,MPI_INT,(rank+1)%size,rank,MPI_COMM_WORLD);			
	}
	
	
	MPI_Finalize();
	
	return 0;
}




