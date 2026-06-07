#include <stdio.h>

int main() {
    int n, m, i, j, k;


    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int allocation[n][m], request[n][m];
    int available[m];

    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    int work[m], finish[n];

    for(i = 0; i < m; i++) {
        work[i] = available[i];
    }

    for(i = 0; i < n; i++) {
        int zero = 1;

        for(j = 0; j < m; j++) {
            if(allocation[i][j] != 0) {
                zero = 0;
                break;
            }
        }

        if(zero)
            finish[i] = 1;
        else
            finish[i] = 0;
    }

    int found;

    do {
        found = 0;

        for(i = 0; i < n; i++) {

            if(finish[i] == 0) {

                int possible = 1;

                for(j = 0; j < m; j++) {
                    if(request[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                if(possible) {

                    for(k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

    } while(found);

    int deadlock = 0;

    printf("\nDeadlocked Processes:\n");

    for(i = 0; i < n; i++) {
        if(finish[i] == 0) {
            printf("P%d ", i);
            deadlock = 1;
        }
    }

    if(deadlock == 0) {
        printf("No Deadlock Detected");
    }

    return 0;
}