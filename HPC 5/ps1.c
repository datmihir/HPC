#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
// matrix x matrix
#define N 500 

int main() {
    double **A, **B, **C;
    int i, j, k;
    double start_time, end_time;
    int num_threads_to_use;

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads_to_use);

    A = (double **)malloc(N * sizeof(double *));
    B = (double **)malloc(N * sizeof(double *));
    C = (double **)malloc(N * sizeof(double *));
    for (i = 0; i < N; i++) {
        A[i] = (double *)malloc(N * sizeof(double));
        B[i] = (double *)malloc(N * sizeof(double));
        C[i] = (double *)malloc(N * sizeof(double));
    }

    #pragma omp parallel for private(j) num_threads(num_threads_to_use)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i;
            B[i][j] = j;
            C[i][j] = 0;
        }
    }

    start_time = omp_get_wtime();

    #pragma omp parallel for private(j, k) shared(A, B, C) num_threads(num_threads_to_use)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    end_time = omp_get_wtime();

    printf("Time taken with %d threads: %f seconds\n", num_threads_to_use, end_time - start_time);

    for (i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}