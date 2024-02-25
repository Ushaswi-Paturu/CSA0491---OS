#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg) {
    printf("Inside the thread function\n");
    sleep(3); // Simulate some work
    printf("Thread execution completed\n");
    pthread_exit(NULL);
}

int main() {
    // (i) create: Creating a Thread
    pthread_t tid;
    printf("Creating a new thread\n");
    pthread_create(&tid, NULL, thread_function, NULL);
    printf("Main thread continues execution\n");
    sleep(1); // Allow some time for the thread to start

    // (ii) join: Joining Threads
    printf("Main thread waits for the new thread to complete\n");
    pthread_join(tid, NULL); // Main thread waits for the new thread to finish
    printf("Main thread continues execution\n");

    // (iii) equal: Checking Thread Equality
    pthread_t tid1, tid2;
    printf("Creating two new threads\n");
    pthread_create(&tid1, NULL, thread_function, NULL);
    pthread_create(&tid2, NULL, thread_function, NULL);
    if (pthread_equal(tid1, tid2))
        printf("Threads are equal\n");
    else
        printf("Threads are not equal\n");

    // (iv) exit: Exiting Threads
    printf("Main thread exits without waiting for the new thread\n");
    pthread_exit(NULL); // Main thread exits

    return 0;
}

