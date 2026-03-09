#include <stdio.h>

int main()
{
    int n = 4;

    int process[4] = {1,2,3,4};
    int arrival[4] = {0,1,2,3};
    int burst[4]   = {5,3,8,6};

    int waiting[4] = {0};
    int turnaround[4] = {0};
    int completion[4] = {0};
    int done[4] = {0};

    int completed = 0;
    int current_time = 0;
    int i, shortest;
    float avg_wt = 0, avg_tat = 0;

    while(completed < n)
    {
        shortest = -1;

         for(i = 0; i < n; i++)
        {
            if(arrival[i] <= current_time && done[i] == 0)
            {
                if(shortest == -1 || burst[i] < burst[shortest])
                {
                    shortest = i;
                }
            }
        }

        if(shortest == -1)
        {
            current_time++;
        }
        else
        {
            completion[shortest] = current_time + burst[shortest];
            turnaround[shortest] = completion[shortest] - arrival[shortest];
            waiting[shortest] = turnaround[shortest] - burst[shortest];

            current_time = completion[shortest];
            done[shortest] = 1;
            completed++;

            avg_wt += waiting[shortest];
            avg_tat += turnaround[shortest];
        }
    }

    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        process[i], arrival[i], burst[i],
        completion[i], turnaround[i], waiting[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f", avg_tat/n);

    return 0;
}
