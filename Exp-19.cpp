#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Shared counter
int counter = 0;

// Mutex lock
pthread_mutex_t lock;

// Function to increment the counter
void* increment(void* arg) {
    for (int i = 0; i < 1000000; ++i) {
        // Lock the mutex before accessing the shared counter
        pthread_mutex_lock(&lock);
        ++counter;
        // Unlock the mutex after accessing the shared counter
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    // Initialize the mutex lock
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }

    pthread_t thread1, thread2;

    // Create two threads
    pthread_create(&thread1, NULL, increment, NULL);
    pthread_create(&thread2, NULL, increment, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutex lock
    pthread_mutex_destroy(&lock);

    // Print the final value of the counter
    printf("Final counter value: %d\n", counter);

    return 0;
}

