#include <stdio.h>

int main() {
    int bsize[10], psize[10], bno, pno, allocation[10];

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

    // Worst-Fit Logic
    for(int i = 0; i < pno; i++) {
        int worstIdx = -1;
        for(int j = 0; j < bno; j++) {
            if(bsize[j] >= psize[i]) {
                // If it's the first matching block or larger than the previous worst block
                if(worstIdx == -1 || bsize[worstIdx] < bsize[j]) {
                    worstIdx = j;
                }
            }
        }

        // If a fitting block was found
        if(worstIdx != -1) {
            allocation[i] = worstIdx;
            bsize[worstIdx] -= psize[i];
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