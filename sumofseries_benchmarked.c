#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int id;	
	int p;
	int num;
	int global_sum;	
	double elapsed_time;			

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Barrier(MPI_COMM_WORLD);
	elapsed_time = -MPI_Wtime();

	num  = id + 1;

	MPI_Reduce(&num, &global_sum,  1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	elapsed_time += MPI_Wtime();

	printf("Process %d is done\n", id);
	fflush (stdout);
	MPI_Finalize();

	if(id==0){
	printf("The sum of %d elements is %d \n",p,global_sum);
	printf("Cross check value is %d\n", p*(p+1)/2);
	printf("middle area time = %f\n ", elapsed_time);

	FILE *fptr;
	fptr = fopen("/home/soumick/MPI_codes/sum_benchmark.txt","a");
	fprintf(fptr,"%d  %f\n",p,elapsed_time);
	fclose(fptr);
    }

	return 0;
}