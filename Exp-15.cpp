#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_USERS 10
#define MAX_FILES 20
#define MAX_FILENAME 100
#define MAIN_DIR "main_directory"

// Function prototypes
void createMainDirectory();
void createUserDirectory(char* userName);
void createFile(char* userName, char* fileName);
void listFiles(char* userName);
void deleteFile(char* userName, char* fileName);

int main() {
    createMainDirectory();
    
    int choice;
    char userName[50];
    char fileName[MAX_FILENAME];
    
    while (1) {
        printf("\n1. Create User Directory\n");
        printf("2. Create File\n");
        printf("3. List Files\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter username: ");
                scanf("%s", userName);
                createUserDirectory(userName);
                break;
            case 2:
                printf("Enter username: ");
                scanf("%s", userName);
                printf("Enter file name: ");
                scanf("%s", fileName);
                createFile(userName, fileName);
                break;
            case 3:
                printf("Enter username: ");
                scanf("%s", userName);
                listFiles(userName);
                break;
            case 4:
                printf("Enter username: ");
                scanf("%s", userName);
                printf("Enter file name: ");
                scanf("%s", fileName);
                deleteFile(userName, fileName);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void createMainDirectory() {
    struct stat st = {0};
    
    if (stat(MAIN_DIR, &st) == -1) {
        mkdir(MAIN_DIR, 0700);
        printf("Main directory created.\n");
    } else {
        printf("Main directory already exists.\n");
    }
}

void createUserDirectory(char* userName) {
    char path[150];
    snprintf(path, sizeof(path), "%s/%s", MAIN_DIR, userName);
    struct stat st = {0};
    
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
        printf("User directory '%s' created.\n", userName);
    } else {
        printf("User directory '%s' already exists.\n", userName);
    }
}

void createFile(char* userName, char* fileName) {
    char path[200];
    snprintf(path, sizeof(path), "%s/%s/%s", MAIN_DIR, userName, fileName);
    FILE* file = fopen(path, "w");
    
    if (file) {
        fprintf(file, "This is a file for user %s.\n", userName);
        fclose(file);
        printf("File '%s' created for user '%s'.\n", fileName, userName);
    } else {
        printf("Error creating file '%s'.\n", fileName);
    }
}

void listFiles(char* userName) {
    char path[150];
    snprintf(path, sizeof(path), "%s/%s", MAIN_DIR, userName);
    DIR* dir = opendir(path);
    
    if (dir) {
        struct dirent* entry;
        printf("Files for user '%s':\n", userName);
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG) {
                printf("%s\n", entry->d_name);
            }
        }
        closedir(dir);
    } else {
        printf("User directory '%s' does not exist.\n", userName);
    }
}

void deleteFile(char* userName, char* fileName) {
    char path[200];
    snprintf(path, sizeof(path), "%s/%s/%s", MAIN_DIR, userName, fileName);
    
    if (remove(path) == 0) {
        printf("File '%s' deleted for user '%s'.\n", fileName, userName);
    } else {
        printf("Error deleting file '%s'.\n", fileName);
    }
}

