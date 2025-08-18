#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define THRESHOLD 15 

long long fib_parallel(int n);

int main() {
    int n;
    int num_threads_to_use; 
    long long result;
    double start_time, end_time;

    printf("Enter n for Fibonacci calculation: ");
    scanf("%d", &n);

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads_to_use);

    if (n < 0) {
        printf("Please insert a positive number.\n");
        return 1;
    }

    start_time = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads_to_use)
    {
        #pragma omp single
        {
            result = fib_parallel(n);
        }
    }

    end_time = omp_get_wtime();

    printf("Fibonacci(%d) = %lld\n", n, result);
    printf("Used %d threads and took %f seconds\n", num_threads_to_use, end_time - start_time);

    return 0;
}

long long fib_parallel(int n) {
    if (n < 2) {
        return n;
    }

    if (n < THRESHOLD) {
        return fib_parallel(n - 1) + fib_parallel(n - 2);
    } 
    else {
        long long x, y;

        #pragma omp task shared(x) final(n - 1 < THRESHOLD)
        x = fib_parallel(n - 1);

        #pragma omp task shared(y) final(n - 2 < THRESHOLD)
        y = fib_parallel(n - 2);

        #pragma omp taskwait

        return x + y;
    }
}
