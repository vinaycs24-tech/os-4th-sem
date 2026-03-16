#include <stdio.h>

int main()
{
    int n, tq;
    int AT[20], BT[20], RT[20];
    int CT[20], TAT[20], WT[20];

    int queue[100];
    int front = 0, rear = -1;

    int i, time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("Enter Arrival Time for P%d: ", i+1);
        scanf("%d", &AT[i]);

        printf("Enter Burst Time for P%d: ", i+1);
        scanf("%d", &BT[i]);

        RT[i] = BT[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int visited[20] = {0};

    while(completed < n)
    {
        for(i = 0; i < n; i++)
        {
            if(AT[i] <= time && visited[i] == 0)
            {
                rear++;
                queue[rear] = i;
                visited[i] = 1;
            }
        }

        if(front > rear)
        {
            time++;
            continue;
        }

        int p = queue[front];
        front++;

        if(RT[p] > tq)
        {
            time = time + tq;
            RT[p] = RT[p] - tq;

            for(i = 0; i < n; i++)
            {
                if(AT[i] <= time && visited[i] == 0)
                {
                    rear++;
                    queue[rear] = i;
                    visited[i] = 1;
                }
            }

            rear++;
            queue[rear] = p;
        }
        else
        {
            time = time + RT[p];
            RT[p] = 0;

            CT[p] = time;
            completed++;

            for(i = 0; i < n; i++)
            {
                if(AT[i] <= time && visited[i] == 0)
                {
                    rear++;
                    queue[rear] = i;
                    visited[i] = 1;
                }
            }
        }
    }

    for(i = 0; i < n; i++)
    {
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1, AT[i], BT[i], CT[i], TAT[i], WT[i]);
    }

    return 0;
}
