#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employees.dat"

typedef struct {
    int id;
    char name[50];
    float salary;
} Employee;

void addEmployee(FILE *file) {
    Employee emp;
    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Employee Name: ");
    scanf("%s", emp.name);
    printf("Enter Employee Salary: ");
    scanf("%f", &emp.salary);
    
    fseek(file, 0, SEEK_END); // Move to the end of the file
    fwrite(&emp, sizeof(Employee), 1, file); // Write the employee record to the file
    printf("Employee added successfully.\n");
}

void displayEmployees(FILE *file) {
    Employee emp;
    fseek(file, 0, SEEK_SET); // Move to the start of the file
    while(fread(&emp, sizeof(Employee), 1, file)) {
        printf("Employee ID: %d\n", emp.id);
        printf("Employee Name: %s\n", emp.name);
        printf("Employee Salary: %.2f\n\n", emp.salary);
    }
}

void searchEmployee(FILE *file) {
    int id;
    Employee emp;
    printf("Enter Employee ID to search: ");
    scanf("%d", &id);
    
    fseek(file, 0, SEEK_SET); // Move to the start of the file
    while(fread(&emp, sizeof(Employee), 1, file)) {
        if(emp.id == id) {
            printf("Employee found:\n");
            printf("Employee ID: %d\n", emp.id);
            printf("Employee Name: %s\n", emp.name);
            printf("Employee Salary: %.2f\n", emp.salary);
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}

int main() {
    FILE *file;
    int choice;
    
    file = fopen(FILENAME, "rb+");
    if(file == NULL) {
        file = fopen(FILENAME, "wb+");
        if(file == NULL) {
            printf("Unable to open file.\n");
            return 1;
        }
    }
    
    while(1) {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee by ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addEmployee(file);
                break;
            case 2:
                displayEmployees(file);
                break;
            case 3:
                searchEmployee(file);
                break;
            case 4:
                fclose(file);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}

