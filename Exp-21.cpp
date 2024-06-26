#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTITIONS 50

struct MemoryPartition {
    int size;
    int allocated;
};

void worstFit(int blockSize[], int m, int processSize[], int n) {
    struct MemoryPartition partitions[MAX_PARTITIONS];
    int allocation[MAX_PARTITIONS];
    
    // Initialize memory partitions
    for (int i = 0; i < m; i++) {
        partitions[i].size = blockSize[i];
        partitions[i].allocated = -1; // -1 means not allocated
    }

    // Process each process
    for (int i = 0; i < n; i++) {
        // Find the worst fit partition
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (partitions[j].allocated == -1 && partitions[j].size >= processSize[i]) {
                if (worstIdx == -1 || partitions[j].size > partitions[worstIdx].size) {
                    worstIdx = j;
                }
            }
        }

        // Allocate memory if we found a partition
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            partitions[worstIdx].allocated = i;
        } else {
            allocation[i] = -1; // No suitable partition found
        }
    }

    // Print the allocation result
    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1); // +1 to display block number starting from 1
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};

    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    worstFit(blockSize, m, processSize, n);

    return 0;
}

