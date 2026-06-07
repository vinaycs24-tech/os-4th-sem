#include <stdio.h>

int main() {
    int n, quantum;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    int at[n], bt[n], rem[n];
    int ct[n], tat[n], wt[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Task %d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);

        rem[i] = bt[i];
        ct[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    int queue[1000];
    int front = 0, rear = 0;

    int visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    int time = 0;
    int completed = 0;

    // Add first arriving processes
    for (int i = 0; i < n; i++) {
        if (at[i] <= time && !visited[i]) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    printf("\nExecution Log:\n");

    while (completed < n) {

        if (front == rear) {
            time++;

            for (int i = 0; i < n; i++) {
                if (at[i] <= time && !visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int p = queue[front++];

        int slice = (rem[p] > quantum) ? quantum : rem[p];

        printf("Time %d-%d : Task %d\n",
               time, time + slice, p + 1);

        rem[p] -= slice;
        time += slice;

        // Add newly arrived processes
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (rem[p] > 0) {
            queue[rear++] = p;
        } else {
            completed++;
            ct[p] = time;
        }
    }

    float avgTAT = 0, avgWT = 0;

    printf("\nTask\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avgTAT += tat[i];
        avgWT += wt[i];

        printf("T%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage TAT = %.2f", avgTAT / n);
    printf("\nAverage WT  = %.2f\n", avgWT / n);

    return 0;
}
