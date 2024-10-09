#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 4  // Size of the matrix
#define NUM_THREADS 5  // Number of threads
pthread_mutex_t mutex;

int **A, **B, **C;  // Global matrices

// Information holder for each thread
typedef struct {
    int thread_id;
    int num_rows;  
} thread_data_t;

// Entry function for each thread
void* matrixMultiplyThread(void* arg) {
    // Extract thread info from the passes argument
    const thread_data_t thread_data = *(thread_data_t*)arg;
    // Calculate the start and ending row chunck for each thread to handle
    const int start = thread_data.thread_id * (N / NUM_THREADS);

    int end;
    if (thread_data.thread_id  == NUM_THREADS - 1) {
        end = N;
    } else {
        end = (thread_data.thread_id  + 1) * (N / NUM_THREADS);
    }

    // Loop through the start and end row assigned to the thread and compute matrix multiplication
    for (int i = start; i < end; i++) {
        for (int j = 0; j < N; j++) {
            pthread_mutex_lock(&mutex);
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
            pthread_mutex_unlock(&mutex);
        }
    }

    pthread_exit(NULL);
}

void displayMatrix(int **Matrix, const int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%d ", Matrix[i][j]);
        }
        printf("\n");
    }
}