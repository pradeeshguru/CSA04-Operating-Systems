#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define maximum number of files and file name length
#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 100

// Structure to represent a file
typedef struct {
    char name[MAX_FILENAME_LENGTH];
} File;

// Array to hold files in the directory
File directory[MAX_FILES];
int file_count = 0;

// Function to create a file
void create_file() {
    if (file_count >= MAX_FILES) {
        printf("Directory is full. Cannot create more files.\n");
        return;
    }

    char filename[MAX_FILENAME_LENGTH];
    printf("Enter the name of the file to create: ");
    scanf("%s", filename);

    // Check if file already exists
    for (int i = 0; i < file_count; i++) {
        if (strcmp(directory[i].name, filename) == 0) {
            printf("File already exists.\n");
            return;
        }
    }

    // Create the file
    strcpy(directory[file_count].name, filename);
    file_count++;
    printf("File created successfully.\n");
}

// Function to list all files
void list_files() {
    if (file_count == 0) {
        printf("No files in the directory.\n");
        return;
    }

    printf("Files in the directory:\n");
    for (int i = 0; i < file_count; i++) {
        printf("%s\n", directory[i].name);
    }
}

// Function to delete a file
void delete_file() {
    if (file_count == 0) {
        printf("No files to delete.\n");
        return;
    }

    char filename[MAX_FILENAME_LENGTH];
    printf("Enter the name of the file to delete: ");
    scanf("%s", filename);

    // Find the file and delete it
    for (int i = 0; i < file_count; i++) {
        if (strcmp(directory[i].name, filename) == 0) {
            // Shift remaining files
            for (int j = i; j < file_count - 1; j++) {
                strcpy(directory[j].name, directory[j + 1].name);
            }
            file_count--;
            printf("File deleted successfully.\n");
            return;
        }
    }

    printf("File not found.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\nSingle-Level Directory\n");
        printf("1. Create File\n");
        printf("2. List Files\n");
        printf("3. Delete File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_file();
                break;
            case 2:
                list_files();
                break;
            case 3:
                delete_file();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

