#include <stdio.h>

// Define a structure to hold process information
struct Process {
    int id;         // Process ID
    int burstTime;  // Burst time of the process
    int waitingTime; // Waiting time of the process
    int turnaroundTime; // Turnaround time of the process
};

// Function to calculate waiting time for each process
void calculateWaitingTime(struct Process processes[], int n) {
    processes[0].waitingTime = 0; // First process has no waiting time

    // Calculate waiting time for each process
    for (int i = 1; i < n; i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}

// Function to calculate turnaround time for each process
void calculateTurnaroundTime(struct Process processes[], int n) {
    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

// Function to calculate average waiting time and average turnaround time
void calculateAverageTimes(struct Process processes[], int n) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    // Calculate and print average waiting time and average turnaround time
    float averageWaitingTime = (float) totalWaitingTime / n;
    float averageTurnaroundTime = (float) totalTurnaroundTime / n;
    printf("Average Waiting Time: %.2f\n", averageWaitingTime);
    printf("Average Turnaround Time: %.2f\n", averageTurnaroundTime);
}

// Function to print process information
void printProcessInfo(struct Process processes[], int n) {
    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");

    // Print information for each process
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burstTime,
               processes[i].waitingTime, processes[i].turnaroundTime);
    }
}

int main() {
    int n;

    // Ask the user for the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Get burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter burst time for process %d: ", processes[i].id);
        scanf("%d", &processes[i].burstTime);
    }

    // Calculate waiting time and turnaround time for each process
    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);

    // Print process information
    printProcessInfo(processes, n);

    // Calculate and print average waiting time and average turnaround time
    calculateAverageTimes(processes, n);

    return 0;
}

