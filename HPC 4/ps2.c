#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <omp.h>

#define PRODUCER_SLEEP 0
#define CONSUMER_SLEEP 0

int *buffer;
int buffer_size;
int num_items;

int count = 0;
int in = 0;
int out = 0;

void print_buffer() {
    printf("Buffer: [");
    for (int i = 0; i < buffer_size; i++) {
        if (i < count) {
            printf(" %d ", buffer[(out + i) % buffer_size]);
        } else {
            printf(" _ ");
        }
    }
    printf("] Count: %d\n\n", count);
}

int main() {
    printf("Enter the buffer size: ");
    scanf("%d", &buffer_size);

    printf("Enter the total number of items to produce/consume: ");
    scanf("%d", &num_items);

    if (buffer_size <= 0 || num_items <= 0) {
        printf("Buffer size and number of items must be positive.\n");
        return 1;
    }
    
    buffer = (int *)malloc(buffer_size * sizeof(int));
    
    printf("Buffer Size: %d, Total Items: %d\n\n", buffer_size, num_items);

    double start_time = omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            int produced_item = 0;
            for (int i = 0; i < num_items; i++) {
                produced_item = i + 1; 

                while (count == buffer_size) {
                }

                #pragma omp critical
                {
                    buffer[in] = produced_item;
                    in = (in + 1) % buffer_size;
                    printf("Producer produced item %d\n", produced_item);
                }
                
                #pragma omp atomic
                count++;
                
                sleep(PRODUCER_SLEEP); 
            }
        }

        #pragma omp section
        {
            int consumed_item;
            for (int i = 0; i < num_items; i++) {
                while (count == 0) {
                }

                #pragma omp critical
                {
                    consumed_item = buffer[out];
                    out = (out + 1) % buffer_size;
                    printf("Consumer consumed item %d\n", consumed_item);
                }
                
                #pragma omp atomic
                count--;

                sleep(CONSUMER_SLEEP); 
            }
        }
    }

    double end_time = omp_get_wtime();
    printf("Total time taken: %f seconds\n", end_time - start_time);
    
    free(buffer);
    
    return 0;
}