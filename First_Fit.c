#include <stdio.h>

int main() {
    int bsize[10], psize[10], bno, pno, allocation[10];

    // Initialize all allocations to -1 (means unallocated)
    for(int i = 0; i < 10; i++) {
        allocation[i] = -1;
    }

    printf("Enter no. of blocks: ");
    scanf("%d", &bno);
    printf("Enter size of each block:\n");
    for(int i = 0; i < bno; i++) {
        scanf("%d", &bsize[i]);
    }

    printf("Enter no. of processes: ");
    scanf("%d", &pno);
    printf("Enter size of each process:\n");
    for(int i = 0; i < pno; i++) {
        scanf("%d", &psize[i]);
    }

    // First-Fit Logic
    for(int i = 0; i < pno; i++) {
        for(int j = 0; j < bno; j++) {
            if(bsize[j] >= psize[i]) {
                allocation[i] = j; // Assign block j to process i
                bsize[j] -= psize[i]; // Reduce available block size
                break; // Move to the next process immediately
            }
        }
    }

    // Display Output
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < pno; i++) {
        printf("%d\t\t%d\t\t", i + 1, psize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
    return 0;
}