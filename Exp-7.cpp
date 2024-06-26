#include <stdio.h>

struct Process {
    int id;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

void calculateWaitingTime(struct Process proc[], int n) {
    proc[0].waitingTime = 0;
    
    for (int i = 1; i < n; i++) {
        proc[i].waitingTime = proc[i - 1].waitingTime + proc[i - 1].burstTime;
    }
}

void calculateTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaroundTime = proc[i].waitingTime + proc[i].burstTime;
    }
}

void sortProcessesByBurstTime(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].burstTime > proc[j + 1].burstTime) {
                temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

void printGanttChart(struct Process proc[], int n) {
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < n; i++) {
        printf("| P%d ", proc[i].id);
    }
    printf("|\n");
    for (int i = 0; i < n; i++) {
        printf(" %d  ", proc[i].waitingTime);
    }
    printf("%d\n", proc[n - 1].waitingTime + proc[n - 1].burstTime);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &proc[i].burstTime);
    }

    sortProcessesByBurstTime(proc, n);
    calculateWaitingTime(proc, n);
    calculateTurnaroundTime(proc, n);

    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].burstTime, proc[i].waitingTime, proc[i].turnaroundTime);
    }

    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += proc[i].waitingTime;
        totalTurnaroundTime += proc[i].turnaroundTime;
    }
    
    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f", totalTurnaroundTime / n);

    printGanttChart(proc, n);

    return 0;
}

