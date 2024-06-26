#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILENAME "example.txt"
#define BUFFER_SIZE 1024

int main() {
    int fd;
    ssize_t bytes_written, bytes_read;
    char write_buffer[] = "Hello, UNIX system calls!";
    char read_buffer[BUFFER_SIZE];

    // Create a new file (or open it if it already exists) with read and write permissions
    fd = open(FILENAME, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    // Write data to the file
    bytes_written = write(fd, write_buffer, strlen(write_buffer));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Wrote %ld bytes to %s\n", bytes_written, FILENAME);

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file after writing");
        exit(EXIT_FAILURE);
    }

    // Open the file for reading
    fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    // Read data from the file
    bytes_read = read(fd, read_buffer, BUFFER_SIZE - 1);
    if (bytes_read == -1) {
        perror("Error reading from file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Null-terminate the read buffer to make it a proper string
    read_buffer[bytes_read] = '\0';

    printf("Read %ld bytes from %s: %s\n", bytes_read, FILENAME, read_buffer);

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file after reading");
        exit(EXIT_FAILURE);
    }

    // Delete the file
    if (unlink(FILENAME) == -1) {
        perror("Error deleting file");
        exit(EXIT_FAILURE);
    }

    printf("Deleted %s\n", FILENAME);

    return 0;
}

