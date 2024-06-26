#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMORY 100

struct MemoryBlock {
    int id;
    int size;
    int allocated;
};

void firstFit(struct MemoryBlock memory[], int numBlocks, int requestSize) {
    for (int i = 0; i < numBlocks; ++i) {
        if (!memory[i].allocated && memory[i].size >= requestSize) {
            memory[i].allocated = 1;
            printf("Memory allocated successfully at block %d.\n", memory[i].id);
            return;
        }
    }
    printf("Memory allocation failed: No suitable block found.\n");
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

    firstFit(memory, numBlocks, requestSize);

    return 0;
}

