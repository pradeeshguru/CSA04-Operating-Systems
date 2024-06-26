#include <stdio.h>

struct Process {
    int pid;       // Process ID
    int burstTime; // Burst Time
    int waitingTime; // Waiting Time
    int turnaroundTime; // Turnaround Time
};

void calculateWaitingTime(struct Process processes[], int n) {
    processes[0].waitingTime = 0; // Waiting time for first process is 0

    for (int i = 1; i < n; i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}

void calculateTurnaroundTime(struct Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].burstTime + processes[i].waitingTime;
    }
}

void sortProcessesByBurstTime(struct Process processes[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].burstTime > processes[j].burstTime) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void printProcesses(struct Process processes[], int n) {
    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].pid = i + 1;
    }

    // Sort processes by burst time
    sortProcessesByBurstTime(processes, n);

    // Calculate waiting time for all processes
    calculateWaitingTime(processes, n);

    // Calculate turnaround time for all processes
    calculateTurnaroundTime(processes, n);

    // Print all processes with their burst time, waiting time and turnaround time
    printProcesses(processes, n);

    return 0;
}

