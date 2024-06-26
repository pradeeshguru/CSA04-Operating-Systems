#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of the shared memory segment

int main() {
    // Create a key for the shared memory segment
    key_t key = ftok("shmfile", 65);

    // Create the shared memory segment
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Fork the process to create a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        // Attach to the shared memory segment
        char *shared_memory = (char *)shmat(shmid, NULL, 0);
        if (shared_memory == (char *)(-1)) {
            perror("shmat failed");
            exit(1);
        }

        // Read data from shared memory
        printf("Child process read: %s\n", shared_memory);

        // Detach from the shared memory segment
        if (shmdt(shared_memory) == -1) {
            perror("shmdt failed");
            exit(1);
        }

        // Exit the child process
        exit(0);
    } else {
        // Parent process
        // Attach to the shared memory segment
        char *shared_memory = (char *)shmat(shmid, NULL, 0);
        if (shared_memory == (char *)(-1)) {
            perror("shmat failed");
            exit(1);
        }

        // Write data to shared memory
        const char *message = "Hello from parent process!";
        strncpy(shared_memory, message, SHM_SIZE);

        // Wait for the child process to complete
        wait(NULL);

        // Detach from the shared memory segment
        if (shmdt(shared_memory) == -1) {
            perror("shmdt failed");
            exit(1);
        }

        // Remove the shared memory segment
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl failed");
            exit(1);
        }

        printf("Parent process completed.\n");
    }

    return 0;
}

