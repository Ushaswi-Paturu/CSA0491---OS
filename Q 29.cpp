#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 3
#define NUM_ITEMS 10

sem_t empty, full, mutex;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void *producer(void *arg) {
    int i, item;
    for (i = 0; i < NUM_ITEMS; i++) {
        item = rand() % 100; // Generate a random item
        sem_wait(&empty); // Wait if the buffer is full
        sem_wait(&mutex); // Acquire the lock
        buffer[in] = item;
        printf("Producer %d produced item: %d\n", *((int *)arg), item);
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&mutex); // Release the lock
        sem_post(&full); // Increment the full count
        // Simulate some work
        sleep(1);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int i, item;
    for (i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full); // Wait if the buffer is empty
        sem_wait(&mutex); // Acquire the lock
        item = buffer[out];
        printf("Consumer %d consumed item: %d\n", *((int *)arg), item);
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&mutex); // Release the lock
        sem_post(&empty); // Increment the empty count
        // Simulate some work
        sleep(2);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_threads[NUM_PRODUCERS], consumer_threads[NUM_CONSUMERS];
    int i, producer_ids[NUM_PRODUCERS], consumer_ids[NUM_CONSUMERS];

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create producer threads
    for (i = 0; i < NUM_PRODUCERS; i++) {
        producer_ids[i] = i + 1;
        pthread_create(&producer_threads[i], NULL, producer, (void *)&producer_ids[i]);
    }

    // Create consumer threads
    for (i = 0; i < NUM_CONSUMERS; i++) {
        consumer_ids[i] = i + 1;
        pthread_create(&consumer_threads[i], NULL, consumer, (void *)&consumer_ids[i]);
    }

    // Join producer threads
    for (i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producer_threads[i], NULL);
    }

    // Join consumer threads
    for (i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}

