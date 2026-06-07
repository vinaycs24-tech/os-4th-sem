#include <stdio.h>

struct process
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int st;
    int completed;
};

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct process p[n];
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and burst time of P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].completed = 0;
    }
    int time = 0, completedCount = 0;
    float totalWT = 0, totalRT = 0;
    while (completedCount < n)
    {
        int idx = -1;
        int mainBT = 999999;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && p[i].completed == 0)
            {
                if (p[i].bt < mainBT)
                {
                    mainBT = p[i].bt;
                    idx = i;
                }
            }
        }
        if (idx == -1)
        {
            time++;
        }
        else
        {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].rt = p[idx].wt; // In non-preemp􀆟ve SJF, RT = WT
            p[idx].completed = 1;
            completedCount++;
            totalWT += p[idx].wt;
            totalRT += p[idx].rt;
        }
    }
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }
    printf("Average Waiting Time: %.2f\n", totalWT / n);
    printf("Average Response Time: %.2f\n", totalRT / n);
    return 0;
}