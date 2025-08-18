#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
//prefix sum
#define N 10000000

int main() {
    int *in, *out;
    double start_time, end_time;
    int num_threads_to_use;
    int actual_threads = 0;

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads_to_use);

    in = (int *)malloc(N * sizeof(int));
    out = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        in[i] = 1;
    }

    start_time = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads_to_use)
    {
        int i;
        int thread_id = omp_get_thread_num();
        
        #pragma omp single
        {
            actual_threads = omp_get_num_threads();
        }
        
        static int *partials = NULL; 

        #pragma omp single
        {
            partials = (int *)malloc(actual_threads * sizeof(int));
        }

        int chunk_size = (N + actual_threads - 1) / actual_threads;
        int start = thread_id * chunk_size;
        int end = start + chunk_size;
        if (end > N) end = N;

        if (start < end) {
            out[start] = in[start];
            for (i = start + 1; i < end; i++) {
                out[i] = out[i - 1] + in[i];
            }
            partials[thread_id] = out[end - 1];
        }

        #pragma omp barrier

        #pragma omp single
        {
            for (i = 1; i < actual_threads; i++) {
                partials[i] += partials[i - 1];
            }
        }

        #pragma omp barrier

        if (thread_id > 0) {
            int offset = partials[thread_id - 1];
            for (i = start; i < end; i++) {
                out[i] += offset;
            }
        }

        #pragma omp single
        {
            free(partials);
        }
    }

    end_time = omp_get_wtime();
    printf("Time taken with %d threads: %f seconds\n", actual_threads, end_time - start_time);
    free(in);
    free(out);
    return 0;
}