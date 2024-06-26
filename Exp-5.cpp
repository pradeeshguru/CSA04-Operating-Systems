#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int priority;
    // Other fields like arrival_time, burst_time can be added as needed.
} Process;
#define MAX_PROCESSES 100

typedef struct {
    Process processes[MAX_PROCESSES];
    int size;
} PriorityQueue;

void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void push(PriorityQueue *pq, Process p) {
    if (pq->size == MAX_PROCESSES) {
        printf("Priority queue is full\n");
        return;
    }
    pq->processes[pq->size] = p;
    int i = pq->size;
    pq->size++;
    while (i > 0 && pq->processes[i].priority > pq->processes[(i - 1) / 2].priority) {
        swap(&pq->processes[i], &pq->processes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Process pop(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("Priority queue is empty\n");
        exit(1);
    }
    Process top = pq->processes[0];
    pq->processes[0] = pq->processes[pq->size - 1];
    pq->size--;
    int i = 0;
    while ((2 * i + 1) < pq->size) {
        int maxChild = 2 * i + 1;
        if ((2 * i + 2) < pq->size && pq->processes[2 * i + 2].priority > pq->processes[2 * i + 1].priority) {
            maxChild = 2 * i + 2;
        }
        if (pq->processes[i].priority >= pq->processes[maxChild].priority) {
            break;
        }
        swap(&pq->processes[i], &pq->processes[maxChild]);
        i = maxChild;
    }
    return top;
}

void initializePriorityQueue(PriorityQueue *pq) {
    pq->size = 0;
}
void schedule(PriorityQueue *pq) {
    while (pq->size > 0) {
        Process p = pop(pq);
        printf("Executing process ID %d with priority %d\n", p.id, p.priority);
        // Simulate process execution with a sleep or just print statement.
        // In a real system, you'd have more complex logic here.
    }
}

int main() {
    PriorityQueue pq;
    initializePriorityQueue(&pq);

    // Example processes
    Process p1 = {1, 3};
    Process p2 = {2, 1};
    Process p3 = {3, 2};
    Process p4 = {4, 4};

    push(&pq, p1);
    push(&pq, p2);
    push(&pq, p3);
    push(&pq, p4);

    schedule(&pq);

    return 0;
}

