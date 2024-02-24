#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

// Shared resource
int shared_data = 0;

// Semaphores
sem_t mutex;         // Controls access to shared_data
sem_t wrt_mutex;     // Controls access for writers

// Reader function
void *reader(void *arg) {
    int reader_id = *(int *)arg;

    while (1) {
        // Wait for permission to read
        sem_wait(&mutex);

        // Critical section: reading shared_data
        printf("Reader %d is reading: %d\n", reader_id, shared_data);

        // Release access to shared_data
        sem_post(&mutex);

        // Sleep to simulate reading time
        usleep(1000000);
    }
    pthread_exit(NULL);
}

// Writer function
void *writer(void *arg) {
    int writer_id = *(int *)arg;

    while (1) {
        // Wait for permission to write
        sem_wait(&wrt_mutex);

        // Critical section: writing to shared_data
        shared_data++;
        printf("Writer %d is writing: %d\n", writer_id, shared_data);

        // Release access to shared_data
        sem_post(&wrt_mutex);

        // Sleep to simulate writing time
        usleep(2000000);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t reader_threads[NUM_READERS];
    pthread_t writer_threads[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt_mutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]);
    }

    // Join reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt_mutex);

    return 0;
}

