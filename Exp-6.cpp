#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int id;
    int burstTime;
    int remainingTime;
    int priority;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
    bool isCompleted;
} Process;

void sortByArrivalTime(Process p[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(p[j].arrivalTime > p[j+1].arrivalTime) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

int main() {
    int n, currentTime = 0, completed = 0, prev = -1;
    Process p[MAX];
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time and priority of process %d: ", i+1);
        scanf("%d %d %d", &p[i].arrivalTime, &p[i].burstTime, &p[i].priority);
        p[i].id = i+1;
        p[i].remainingTime = p[i].burstTime;
        p[i].waitingTime = 0;
        p[i].turnaroundTime = 0;
        p[i].isCompleted = false;
    }
    
    sortByArrivalTime(p, n);

    while(completed != n) {
        int idx = -1;
        int minPriority = __INT_MAX__;
        
        for(int i = 0; i < n; i++) {
            if(p[i].arrivalTime <= currentTime && !p[i].isCompleted) {
                if(p[i].priority < minPriority) {
                    minPriority = p[i].priority;
                    idx = i;
                }
                if(p[i].priority == minPriority) {
                    if(p[i].arrivalTime < p[idx].arrivalTime) {
                        idx = i;
                    }
                }
            }
        }
        
        if(idx != -1) {
            if(prev != idx) {
                printf("At time %d, process %d is selected for execution\n", currentTime, p[idx].id);
                prev = idx;
            }
            p[idx].remainingTime--;
            currentTime++;
            
            if(p[idx].remainingTime == 0) {
                p[idx].isCompleted = true;
                completed++;
                p[idx].turnaroundTime = currentTime - p[idx].arrivalTime;
                p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
                
                printf("Process %d completed at time %d\n", p[idx].id, currentTime);
            }
        } else {
            currentTime++;
        }
    }

    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].arrivalTime, p[i].burstTime, p[i].priority, p[i].waitingTime, p[i].turnaroundTime);
    }

    return 0;
}

