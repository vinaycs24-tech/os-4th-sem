#include <stdio.h>

int main() {
    int incomingStream[] = {4, 1, 2, 4, 5};
    int frames[10], nf, np;
    int pageFaults = 0, index = 0;

    printf("Enter number of frames: ");
    scanf("%d", &nf);
    printf("Enter number of pages: ");
    scanf("%d", &np);

    int pages[np];
    printf("Enter the reference string (space-separated):\n");
    for(int i = 0; i < np; i++) {
        scanf("%d", &pages[i]);
    }

    // Initialize frames with -1 (empty)
    for(int i = 0; i < nf; i++) {
        frames[i] = -1;
    }

    printf("\nRef String\t Frames\n");
    for(int i = 0; i < np; i++) {
        int s = 0;

        // Check if page is already in memory
        for(int j = 0; j < nf; j++) {
            if(pages[i] == frames[j]) {
                s++;
                pageFaults--; // Compensation for the auto-increment later
            }
        }
        pageFaults++;

        // If page is not in memory and frames are either empty or full
        if((pageFaults <= nf) && (s == 0)) {
            frames[index] = pages[i];
            index = (index + 1) % nf; // Move to the next frame spot circularly
        } else if(s == 0) {
            frames[index] = pages[i];
            index = (index + 1) % nf;
        }

        // Print current state
        printf("%d\t\t", pages[i]);
        for(int j = 0; j < nf; j++) {
            if(frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    return 0;
}