#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Function to be executed by the threads
void *print_message(void *threadid) {
    long tid;
    tid = (long)threadid;
    printf("Hello from thread #%ld!\n", tid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t threads[2];
    int rc;
    long t;

    // Create two threads
    for(t = 0; t < 2; t++) {
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, print_message, (void *)t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Wait for the threads to complete
    for(t = 0; t < 2; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("Main: program exiting.\n");
    pthread_exit(NULL);
}

