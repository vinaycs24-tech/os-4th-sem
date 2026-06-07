#include <stdio.h>

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], type[n];
    int ct[n], tat[n], wt[n];
    int completed = 0, time = 0;

    for(int i = 0; i < n; i++) {
        printf("Enter AT, BT and Type(1-High, 2-Low) for P%d: ", i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &type[i]);
        ct[i] = 0;
    }

    printf("\nExecution Order:\n");

    while(completed < n) {

        int selected = -1;

        /* Search High Priority Queue First */
        for(int i = 0; i < n; i++) {
            if(type[i] == 1 && at[i] <= time && ct[i] == 0) {
                selected = i;
                break;
            }
        }

        /* If no High Priority Process, Search Low Queue */
        if(selected == -1) {
            for(int i = 0; i < n; i++) {
                if(type[i] == 2 && at[i] <= time && ct[i] == 0) {
                    selected = i;
                    break;
                }
            }
        }

        if(selected == -1) {
            time++;
            continue;
        }

        printf("P%d ", selected + 1);

        time += bt[selected];
        ct[selected] = time;
        completed++;
    }

    printf("\n\n");

    float avgWT = 0, avgTAT = 0;

    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avgWT += wt[i];
        avgTAT += tat[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1,
               at[i],
               bt[i],
               ct[i],
               tat[i],
               wt[i]);
    }

    printf("\nAverage TAT = %.2f", avgTAT / n);
    printf("\nAverage WT  = %.2f\n", avgWT / n);

    return 0;
}
