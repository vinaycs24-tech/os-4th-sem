#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int at;
    int bt;
    int remaining_bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int pr;
    int completed;
};

int main() {
    int n, choice;
    printf("1. Non-preemptive Priority\n2. Preemptive Priority\nEnter choice: ");
    scanf("%d", &choice);

    printf("Enter number of processes: ");
    scanf("%d", &n);
   
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d [Arrival, Burst, Priority]: ", p[i].pid);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].remaining_bt = p[i].bt;
        p[i].completed = 0;
        p[i].rt = -1;
    }

    int time = 0, completed = 0;
    float totalWT = 0, totalRT = 0, totalTAT = 0;

    while (completed < n) {
        int idx = -1;
        int minPr = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !p[i].completed) {
                if (p[i].pr < minPr) {
                    minPr = p[i].pr;
                    idx = i;
                }
                else if (p[i].pr == minPr) {
                    if (p[i].at < p[idx].at) idx = i;
                }
            }
        }

        if (idx != -1) {
            if (p[idx].rt == -1) {
                p[idx].rt = time - p[idx].at;
                totalRT += p[idx].rt;
            }

            if (choice == 1) { 
                time += p[idx].bt;
                p[idx].remaining_bt = 0;
                p[idx].completed = 1;
            } else { 
                p[idx].remaining_bt--;
                time++;
                if (p[idx].remaining_bt == 0) {
                    p[idx].completed = 1;
                }
            }

            if (p[idx].completed) {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                totalWT += p[idx].wt;
                totalTAT += p[idx].tat;
                completed++;
            }
        } else {
            time++;
        }
    }

    printf("\n%-7s %-3s %-3s %-3s %-3s %-4s %-3s %-3s\n", "Process", "AT", "BT", "PR", "CT", "TAT", "WT", "RT");
    for (int i = 0; i < n; i++) {
        printf("P%-6d %-3d %-3d %-3d %-3d %-4d %-3d %-3d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAvg Waiting Time: %.2f", totalWT / n);
    printf("\nAvg Turnaround Time: %.2f", totalTAT / n);
    printf("\nAvg Response Time: %.2f\n", totalRT / n);

    return 0;
}