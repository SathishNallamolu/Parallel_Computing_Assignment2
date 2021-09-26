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
		int n,np,i,sum=0;
		printf("enter array size:");
		scanf("%d",&n);
		np=atoi(argv[2]);
		int sizeof_each_array=n/np;
		int a[sizeof_each_array];


		MPI_Send(&n,1,MPI_INT,1,10,MPI_COMM_WORLD);
		
		for(i=0;i<sizeof_each_array;i++){
			a[i]=i;	
			sum+=a[i];
		}
		
		// we are seinding the data using the block distribution. here the array is treated as the block.
		MPI_Send(&i,1,MPI_INT,1,1,MPI_COMM_WORLD);
		
		//sending the sum for the next process.
		// first process sends the array(by usng block distribution) and sum to next process.
		MPI_Send(&sum,1,MPI_INT,1,0,MPI_COMM_WORLD);
		
		//receving the sum of the array from previous process. it is done by cyclic distribution.
		/* first process(p0) sends sum to next process(p1). then p1 sends to p2 and so on. 
		finally,the first process receives total sum.(cyclic distribution of data). */
		MPI_Recv(&sum,1,MPI_INT,size-1,size-1,MPI_COMM_WORLD,&status);
				
		printf("SUM:%d\n",sum);
	}
	else{
	
		int n1,j,k,sum1;
		int sizeof_each_array=n1/size;
		
		MPI_Recv(&n1,1,MPI_INT,0,10,MPI_COMM_WORLD,&status);
		
		MPI_Recv(&j,1,MPI_INT,rank-1,rank,MPI_COMM_WORLD,&status);	
		
		MPI_Recv(&sum1,1,MPI_INT,rank-1,rank-1,MPI_COMM_WORLD,&status);	
		
		int a[sizeof_each_array];
		for(;j<n1/size;j++){
			a[j]=j;
			sum1+=a[j];
		}	
		
		//sending the starting index number of next process.
		MPI_Send(&j,1,MPI_INT,rank+1,rank+1,MPI_COMM_WORLD);
		
		//sending sum to next process in a cyclic way.
		MPI_Send(&sum1,1,MPI_INT,(rank+1)%size,rank,MPI_COMM_WORLD);			
	}
	
	
	MPI_Finalize();
	
	return 0;
}




