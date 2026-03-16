#include <stdio.h>

int main()
{
    int n;
    int PID[20], AT[20], BT[20], TYPE[20];
    int CT[20], TAT[20], WT[20], START[20];

    int systemQ[20], userQ[20];
    int sysCount = 0, userCount = 0;

    int time = 0;
    int i, j, temp;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("\nEnter Process ID: ");
        scanf("%d", &PID[i]);

        printf("Enter Arrival Time: ");
        scanf("%d", &AT[i]);

        printf("Enter Burst Time: ");
        scanf("%d", &BT[i]);

        printf("Enter Type (0-System, 1-User): ");
        scanf("%d", &TYPE[i]);
    }

    for(i = 0; i < n; i++)
    {
        if(TYPE[i] == 0)
        {
            systemQ[sysCount] = i;
            sysCount++;
        }
        else
        {
            userQ[userCount] = i;
            userCount++;
        }
    }

    for(i = 0; i < sysCount-1; i++)
    {
        for(j = i+1; j < sysCount; j++)
        {
            if(AT[systemQ[i]] > AT[systemQ[j]])
            {
                temp = systemQ[i];
                systemQ[i] = systemQ[j];
                systemQ[j] = temp;
            }
        }
    }


    for(i = 0; i < userCount-1; i++)
    {
        for(j = i+1; j < userCount; j++)
        {
            if(AT[userQ[i]] > AT[userQ[j]])
            {
                temp = userQ[i];
                userQ[i] = userQ[j];
                userQ[j] = temp;
            }
        }
    }


    for(i = 0; i < sysCount; i++)
    {
        int p = systemQ[i];

        if(time < AT[p])
            time = AT[p];

        START[p] = time;
        time = time + BT[p];
        CT[p] = time;

        TAT[p] = CT[p] - AT[p];
        WT[p] = TAT[p] - BT[p];
    }

    for(i = 0; i < userCount; i++)
    {
        int p = userQ[i];

        if(time < AT[p])
            time = AT[p];

        START[p] = time;
        time = time + BT[p];
        CT[p] = time;

        TAT[p] = CT[p] - AT[p];
        WT[p] = TAT[p] - BT[p];
    }

    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        PID[i], AT[i], BT[i], TYPE[i], CT[i], TAT[i], WT[i]);
    }

    return 0;
}
