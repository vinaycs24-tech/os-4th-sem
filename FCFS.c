#include <stdio.h>

int main()
{
    int n = 4;

    int process[4] = {1,2,3,4};
    int arrival[4] = {0,1,2,3};
    int burst[4]   = {5,3,8,6};

    int waiting[4], turnaround[4], completion[4];

    int i, j, temp;
    int current_time = 0;
    float avg_wt = 0, avg_tat = 0;

    // Sort by Arrival Time
    for(i = 0; i < n; i++)
    {
        for(j = i+1; j < n; j++)
        {
            if(arrival[i] > arrival[j])
            {
                temp = arrival[i];
                arrival[i] = arrival[j];
                arrival[j] = temp;

                temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;

                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    for(i = 0; i < n; i++)
    {
        if(current_time < arrival[i])
        {
            current_time = arrival[i];
        }

        completion[i] = current_time + burst[i];
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];

        current_time = completion[i];

        avg_wt += waiting[i];
        avg_tat += turnaround[i];
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
