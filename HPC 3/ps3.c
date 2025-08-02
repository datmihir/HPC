#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 200
#define THREADS 4

int main() {
    double *v = malloc(sizeof(double) * N);
    double scalar = 3.14;
    int chunks[]   = {1, 2, 5, 10, 20, 50, 100, 200};
    int nchunks    = sizeof(chunks)/sizeof(chunks[0]);

    for (int i = 0; i < N; i++) 
        v[i] = (double)i;

    printf("STATIC schedule, varying chunk sizes\n");
    for (int ci = 0; ci < nchunks; ci++) {
        int ch = chunks[ci];
        omp_set_num_threads(THREADS);
        double t0 = omp_get_wtime();

        #pragma omp parallel for schedule(static, ch)
        for (int i = 0; i < N; i++) {
            v[i] += scalar;
        }

        double t1 = omp_get_wtime();
        printf("chunk=%3d -> time = %.6f s\n", ch, t1 - t0);
    }
   
    for (int i = 0; i < N; i++) 
        v[i] = (double)i;

    printf("\nDYNAMIC schedule, varying chunk sizes\n");
    for (int ci = 0; ci < nchunks; ci++) {
        int ch = chunks[ci];
        omp_set_num_threads(THREADS);
        double t0 = omp_get_wtime();

        #pragma omp parallel for schedule(dynamic, ch)
        for (int i = 0; i < N; i++) {
            v[i] += scalar;
        }

        double t1 = omp_get_wtime();
        printf("chunk=%3d -> time = %.6f s\n", ch, t1 - t0);
    }

    for (int i = 0; i < N; i++) 
        v[i] = (double)i;

    printf("\nnowait clause\n");
    omp_set_num_threads(THREADS);
    double t0 = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < N; i++)
            v[i] *= 2.0;   

        #pragma omp for
        for (int i = 0; i < N; i++)
            v[i] += 1.0;   
    }

    double t1 = omp_get_wtime();
    printf("two loops with nowait -> total time = %.6f s\n", t1 - t0);

    free(v);
    return 0;
}
