#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
// matrix x vector
#define N 2000 

int main() {
    double **A;
    double *x, *y;
    int i, j;
    double start_time, end_time;
    int num_threads_to_use;

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads_to_use);

    A = (double **)malloc(N * sizeof(double *));
    for (i = 0; i < N; i++) {
        A[i] = (double *)malloc(N * sizeof(double));
    }
    x = (double *)malloc(N * sizeof(double));
    y = (double *)malloc(N * sizeof(double));

    for (i = 0; i < N; i++) {
        x[i] = i;
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
        }
    }
    
    start_time = omp_get_wtime();

    #pragma omp parallel for private(j) shared(A, x, y) num_threads(num_threads_to_use)
    for (i = 0; i < N; i++) {
        y[i] = 0.0;
        for (j = 0; j < N; j++) {
            y[i] += A[i][j] * x[j];
        }
    }

    end_time = omp_get_wtime();

    printf("Time taken %d threads: %f seconds\n", num_threads_to_use, end_time - start_time);

    for (i = 0; i < N; i++) {
        free(A[i]);
    }
    free(A);
    free(x);
    free(y);

    return 0;
}