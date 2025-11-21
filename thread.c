#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_COUNT 4
#define SIZE 20

int arr[SIZE] = {
    5, 3, 8, 10, 2,
    7, 9, 4, 6, 1,
    11, 12, 13, 14, 15,
    16, 17, 18, 19, 20
};

void* sum_part(void* arg) {
    int id = *(int*)arg;
    int start = id * (SIZE / THREAD_COUNT);
    int end   = start + (SIZE / THREAD_COUNT);

    long* result = malloc(sizeof(long));
    *result = 0;

    for (int i = start; i < end; i++)
        *result += arr[i];

    printf("Thread %d → sum = %ld\n", id, *result);
    return result;
}

int main() {
    pthread_t threads[THREAD_COUNT];
    int ids[THREAD_COUNT];
    long total = 0;

    for (int i = 0; i < THREAD_COUNT; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, sum_part, &ids[i]);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        long* thread_result;
        pthread_join(threads[i], (void**)&thread_result);
        total += *thread_result;
        free(thread_result);
    }

    printf("Total sum = %ld\n", total);
    return 0;
}
