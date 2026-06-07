#include <stdio.h>


int findFutureIndex(int page, int pages[], int current_pos, int total_pages) {
    for (int k = current_pos + 1; k < total_pages; k++) {
        if (pages[k] == page) {
            return k;
        }
    }
    return 9999;
}

int main() {
    int nf, np, pageFaults = 0;

    printf("Enter number of frames: ");
    if (scanf("%d", &nf) != 1 || nf <= 0) return 1;
    printf("Enter number of pages: ");
    if (scanf("%d", &np) != 1 || np <= 0) return 1;

    int pages[np];
    int frames[nf];

    printf("Enter the reference string (space-separated):\n");
    for (int i = 0; i < np; i++) {
        if (scanf("%d", &pages[i]) != 1) return 1;
    }


    for (int i = 0; i < nf; i++) {
        frames[i] = -1;
    }

    printf("\nRef String\t Frames\n");
    for (int i = 0; i < np; i++) {
        int page = pages[i];
        int hit = 0;


        for (int j = 0; j < nf; j++) {
            if (frames[j] == page) {
                hit = 1;
                break;
            }
        }

        // Step 2: Handle Page Fault
        if (!hit) {
            pageFaults++;
            int replaced = 0;

            // Try to find an empty slot first
            for (int j = 0; j < nf; j++) {
                if (frames[j] == -1) {
                    frames[j] = page;
                    replaced = 1;
                    break;
                }
            }

            // Step 3: Frames are full, calculate who to evict
            if (!replaced) {
                int farthest_use = -1;
                int index_to_replace = 0;

                for (int j = 0; j < nf; j++) {
                    int next_use = findFutureIndex(frames[j], pages, i, np);

                    // Choose the frame whose page is needed farthest in the future
                    if (next_use > farthest_use) {
                        farthest_use = next_use;
                        index_to_replace = j;
                    }
                }
                frames[index_to_replace] = page;
            }
        }

        // Print current frame state
        printf("%d\t\t", page);
        for (int j = 0; j < nf; j++) {
            if (frames[j] != -1) printf("%d ", frames[j]);
            else printf("- ");
        }
        printf("%s\n", hit ? "(Hit)" : "");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    return 0;
}
