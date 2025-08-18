#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
//matrix x scalar
#define N 1000 
int main() {
    double **A, **B;
    double scalar = 3.5;
    int i, j;
    double start_time, end_time;
    int num_threads_to_use;

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads_to_use);

    A = (double **)malloc(N * sizeof(double *));
    B = (double **)malloc(N * sizeof(double *));
    for (i = 0; i < N; i++) {
        A[i] = (double *)malloc(N * sizeof(double));
        B[i] = (double *)malloc(N * sizeof(double));
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
        }
    }

    start_time = omp_get_wtime();

    #pragma omp parallel for private(j) shared(A, B, scalar) num_threads(num_threads_to_use)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            B[i][j] = scalar * A[i][j];
        }
    }

    end_time = omp_get_wtime();

    printf("Time taken %d threads: %f seconds\n", num_threads_to_use, end_time - start_time);

    for (i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
    }
    free(A);
    free(B);

    return 0;
}