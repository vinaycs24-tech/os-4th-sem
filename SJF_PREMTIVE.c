#include <stdio.h>

int main() {
    int n = 4;
    int process[4] = {1,2,3,4};
    int arrival[4] = {0,1,2,3};
    int burst[4]   = {5,3,8,6};

    int remaining[4];
    int completion[4] = {0};
    int turnaround[4] = {0};
    int waiting[4] = {0};

    for(int i=0; i<n; i++) remaining[i] = burst[i];

    int completed = 0, current_time = 0, shortest = -1;
    float avg_wt = 0, avg_tat = 0;

    while(completed < n) {
        shortest = -1;

        // Find process with shortest remaining time among arrived ones
        for(int i=0; i<n; i++) {
            if(arrival[i] <= current_time && remaining[i] > 0) {
                if(shortest == -1 || remaining[i] < remaining[shortest]) {
                    shortest = i;
                }
            }
        }

        if(shortest == -1) {
            current_time++;
        } else {
            remaining[shortest]--;
            current_time++;

            if(remaining[shortest] == 0) {
                completion[shortest] = current_time;
                turnaround[shortest] = completion[shortest] - arrival[shortest];
                waiting[shortest] = turnaround[shortest] - burst[shortest];

                avg_wt += waiting[shortest];
                avg_tat += turnaround[shortest];
                completed++;
            }
        }
    }

    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0; i<n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               process[i], arrival[i], burst[i],
               completion[i], turnaround[i], waiting[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f", avg_tat/n);

    return 0;
}
