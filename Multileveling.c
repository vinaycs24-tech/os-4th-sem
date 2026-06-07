#include <stdio.h>

struct Process {
    int pid, at, bt, temp_bt, ct, tat, wt, priority;
};

int main() {
    int n, i, temp, time = 0, count = 0, quantum;
    struct Process q1[10], q2[10];
    int n1 = 0, n2 = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        int p, arrival, burst;
        printf("\nEnter Arrival Time, Burst Time, and Queue (1-High, 2-Low) for P%d: ", i + 1);
        scanf("%d %d %d", &arrival, &burst, &p);
        
        if (p == 1) {
            q1[n1].pid = i + 1;
            q1[n1].at = arrival;
            q1[n1].bt = burst;
            q1[n1].temp_bt = burst;
            n1++;
        } else {
            q2[n2].pid = i + 1;
            q2[n2].at = arrival;
            q2[n2].bt = burst;
            q2[n2].temp_bt = burst;
            n2++;
        }
    }


    printf("\n--- Scheduling Result ---\n");

    for (i = 0; i < n1; i++) {
        if (time < q1[i].at) {
            time = q1[i].at;
        }
        time += q1[i].bt;
        q1[i].ct = time;
        q1[i].tat = q1[i].ct - q1[i].at;
        q1[i].wt = q1[i].tat - q1[i].bt;
    }

    for (i = 0; i < n2; i++) {
        if (time < q2[i].at) {
            time = q2[i].at;
        }
        time += q2[i].bt;
        q2[i].ct = time;
        q2[i].tat = q2[i].ct - q2[i].at;
        q2[i].wt = q2[i].tat - q2[i].bt;
    }

   
    printf("\nPID\tQueue\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n1; i++)
        printf("P%d\t1\t%d\t%d\t%d\t%d\t%d\n", q1[i].pid, q1[i].at, q1[i].bt, q1[i].ct, q1[i].tat, q1[i].wt);
    for (i = 0; i < n2; i++)
        printf("P%d\t2\t%d\t%d\t%d\t%d\t%d\n", q2[i].pid, q2[i].at, q2[i].bt, q2[i].ct, q2[i].tat, q2[i].wt);

    return 0;
}