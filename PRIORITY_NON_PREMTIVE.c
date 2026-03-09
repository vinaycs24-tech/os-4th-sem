#include <stdio.h>

int main() {
    int n = 5;
    int process[5]   = {1,2,3,4,5};
    int arrival[5]   = {0,2,3,4,6};
    int burst[5]     = {3,2,5,4,1};
    int priority[5]  = {2,1,4,3,5};

    int completion[5] = {0};
    int turnaround[5] = {0};
    int waiting[5]    = {0};
    int done[5]       = {0};

    int current_time = 0, completed = 0;
    float avg_wt = 0, avg_tat = 0;

    while(completed < n) {
        int highest = -1;

        for(int i=0; i<n; i++) {
            if(arrival[i] <= current_time && done[i] == 0) {
                if(highest == -1 || priority[i] < priority[highest]) {
                    highest = i;
                }
            }
        }

        if(highest == -1) {
            current_time++;
        } else {
            completion[highest] = current_time + burst[highest];
            turnaround[highest] = completion[highest] - arrival[highest];
            waiting[highest]    = turnaround[highest] - burst[highest];

            current_time = completion[highest];
            done[highest] = 1;
            completed++;

            avg_wt  += waiting[highest];
            avg_tat += turnaround[highest];
        }
    }

    printf("Process\tAT\tBT\tPri\tCT\tTAT\tWT\n");
    for(int i=0; i<n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               process[i], arrival[i], burst[i], priority[i],
               completion[i], turnaround[i], waiting[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f", avg_tat/n);

    return 0;
}
