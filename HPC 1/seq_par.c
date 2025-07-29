#include<stdio.h>
#include<omp.h>

int main(){
	int n;
	printf("Enter no of threads: ");
	scanf("%d",&n);

	omp_set_num_threads(n);
	
	printf("Sequential\n\n");
	for(int i =0; i< n;i++){
		printf("Sequential Hi %d\n", i);
	}
	
	printf("Parallel\n\n");
	#pragma omp parallel
	{
	    int thread= omp_get_thread_num();
	    printf("Parallel Hi %d\n", thread);
	}
	
	return 0;
} 
