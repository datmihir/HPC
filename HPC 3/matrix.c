#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void fill_matrix(double *M, int N) {
    for (int i = 0; i < N * N; i++)
        M[i] = drand48();
}

int main() {
    int sizes[]    = {250, 500, 750, 1000, 2000};
    int n_sizes    = sizeof(sizes) / sizeof(sizes[0]);
    int threads[]  = {1, 2, 4, 8};
    int n_threads  = sizeof(threads) / sizeof(threads[0]);

    printf("size,\tthreads,time\n");

    for (int si = 0; si < n_sizes; si++) {
        int N = sizes[si];
        double *A = malloc(sizeof(double) * N * N);
        double *B = malloc(sizeof(double) * N * N);
        double *C = malloc(sizeof(double) * N * N);

        fill_matrix(A, N);
        fill_matrix(B, N);

        for (int ti = 0; ti < n_threads; ti++) {
            int T = threads[ti];
            omp_set_num_threads(T);

            double t0 = omp_get_wtime();
            #pragma omp parallel for schedule(static)
            for (int i = 0; i < N * N; i++) {
                C[i] = A[i] + B[i];
            }
            double t1 = omp_get_wtime();

            printf("%d,\t%d,\t%.6f\n", N, T, t1 - t0);
        }

        free(A);
        free(B);
        free(C);
    }
    return 0;
}
