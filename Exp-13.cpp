#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

typedef struct {
    int size;
    int is_allocated;
} MemoryBlock;

void first_fit(MemoryBlock blocks[], int n, int process_size) {
    for (int i = 0; i < n; i++) {
        if (!blocks[i].is_allocated && blocks[i].size >= process_size) {
            blocks[i].is_allocated = 1;
            printf("Process allocated in block %d\n", i + 1);
            return;
        }
    }
    printf("No suitable block found for the process.\n");
}

void best_fit(MemoryBlock blocks[], int n, int process_size) {
    int best_idx = -1;
    for (int i = 0; i < n; i++) {
        if (!blocks[i].is_allocated && blocks[i].size >= process_size) {
            if (best_idx == -1 || blocks[i].size < blocks[best_idx].size) {
                best_idx = i;
            }
        }
    }
    if (best_idx != -1) {
        blocks[best_idx].is_allocated = 1;
        printf("Process allocated in block %d\n", best_idx + 1);
    } else {
        printf("No suitable block found for the process.\n");
    }
}

void worst_fit(MemoryBlock blocks[], int n, int process_size) {
    int worst_idx = -1;
    for (int i = 0; i < n; i++) {
        if (!blocks[i].is_allocated && blocks[i].size >= process_size) {
            if (worst_idx == -1 || blocks[i].size > blocks[worst_idx].size) {
                worst_idx = i;
            }
        }
    }
    if (worst_idx != -1) {
        blocks[worst_idx].is_allocated = 1;
        printf("Process allocated in block %d\n", worst_idx + 1);
    } else {
        printf("No suitable block found for the process.\n");
    }
}

void print_memory_blocks(MemoryBlock blocks[], int n) {
    printf("Memory Blocks:\n");
    for (int i = 0; i < n; i++) {
        printf("Block %d: Size = %d, %s\n", i + 1, blocks[i].size, blocks[i].is_allocated ? "Allocated" : "Free");
    }
}

int main() {
    int n;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &n);

    MemoryBlock blocks[MAX_BLOCKS];
    for (int i = 0; i < n; i++) {
        printf("Enter size of block %d: ", i + 1);
        scanf("%d", &blocks[i].size);
        blocks[i].is_allocated = 0;
    }

    int choice, process_size;
    while (1) {
        printf("\nMemory Allocation Strategies:\n");
        printf("1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Print Memory Blocks\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 5) {
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter the size of the process: ");
                scanf("%d", &process_size);
                first_fit(blocks, n, process_size);
                break;
            case 2:
                printf("Enter the size of the process: ");
                scanf("%d", &process_size);
                best_fit(blocks, n, process_size);
                break;
            case 3:
                printf("Enter the size of the process: ");
                scanf("%d", &process_size);
                worst_fit(blocks, n, process_size);
                break;
            case 4:
                print_memory_blocks(blocks, n);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}

