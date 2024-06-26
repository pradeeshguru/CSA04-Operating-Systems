#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMORY 100

struct MemoryBlock {
    int id;
    int size;
    int allocated;
};

void bestFit(struct MemoryBlock memory[], int numBlocks, int requestSize) {
    int bestFitIndex = -1;
    
    for (int i = 0; i < numBlocks; ++i) {
        if (!memory[i].allocated && memory[i].size >= requestSize) {
            if (bestFitIndex == -1 || memory[i].size < memory[bestFitIndex].size) {
                bestFitIndex = i;
            }
        }
    }
    
    if (bestFitIndex == -1) {
        printf("Memory allocation failed: No suitable block found.\n");
    } else {
        memory[bestFitIndex].allocated = 1;
        printf("Memory allocated successfully at block %d.\n", bestFitIndex + 1);
    }
}

int main() {
    struct MemoryBlock memory[MAX_MEMORY];
    int numBlocks, requestSize;

    printf("Enter number of memory blocks: ");
    scanf("%d", &numBlocks);

    printf("Enter details for each memory block:\n");
    for (int i = 0; i < numBlocks; ++i) {
        printf("Block %d: ID, Size: ", i + 1);
        scanf("%d %d", &memory[i].id, &memory[i].size);
        memory[i].allocated = 0;
    }

    printf("\nEnter size of memory to allocate: ");
    scanf("%d", &requestSize);

    bestFit(memory, numBlocks, requestSize);

    return 0;
}

