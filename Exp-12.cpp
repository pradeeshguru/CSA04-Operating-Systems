#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        usleep(rand() % 1000000);

        printf("Philosopher %d is hungry.\n", id);

        pthread_mutex_lock(&forks[id]);
        pthread_mutex_lock(&forks[(id + 1) % NUM_PHILOSOPHERS]);

        printf("Philosopher %d is eating.\n", id);
        usleep(rand() % 1000000);

        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id + 1) % NUM_PHILOSOPHERS]);

        printf("Philosopher %d is done eating.\n", id);
    }

    return NULL;
}

int main() {
    int i;
    int ids[NUM_PHILOSOPHERS];

    // Initialize mutexes
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

