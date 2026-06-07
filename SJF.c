#include<stdio.h>

struct Process{
    int id;
    int at;
    int bt;
    int rt;
    int ct;
    int wt;
    int tat;
    int completed;
};

void nonPreemtiveSJF(struct Process p[],int n){
    int completed=0,currentTime=0;
    while(completed!=n){
        int idx=-1;
        int min_Burst=999999;
        for(int i=0;i<n;i++){
            if(p[i].at<=currentTime&&!p[i].completed){
                if(p[i].bt<min_Burst){
                    min_Burst=p[i].bt;
                    idx=i;
                }
                if(p[i].bt==min_Burst){
                    if(p[i].at<p[idx].at)
                        idx=i;
                }
            }
        }
        if(idx!=-1){
            currentTime+=p[idx].bt;
            p[idx].ct=currentTime;
            p[idx].completed=1;
            completed++;
        }
        else{
            currentTime++;
        }
    }
}

void preemptiveSJF(struct Process p[],int n){
    int completed=0,currentTime=0;
    int min_remaining=999999;
    int shortest=0;
    int found=0;
    while(completed!=n){
        for(int i=0;i<n;i++){
            if((p[i].at<=currentTime)&&(p[i].rt<min_remaining)&&p[i].rt>0){
                min_remaining=p[i].rt;
                shortest=i;
                found=1;
            }
        }
        if(!found){
            currentTime++;
            continue;
        }
        p[shortest].rt--;
        min_remaining=p[shortest].rt;
        if(min_remaining==0)
            min_remaining=999999;
        if(p[shortest].rt==0){
            completed++;
            found=0;
            p[shortest].ct=currentTime+1;
        }
        currentTime++;
    }
}

int main(){
    int n,choice;
    printf("Enter the number of Processes");
    scanf("%d",&n);
    struct Process p[n];
    for(int i=0;i<n;i++){
        p[i].id=i+1;
        printf("Enter Arrival Time nad Burst Time for p%d:",i+1);
        scanf("%d %d",&p[i].at,&p[i].bt);
        p[i].rt=p[i].bt;
        p[i].completed=0;
    }
    printf("Choose Scheduling Algorithm:\n1.Non-Preemptive SJF\n2.Preemtive SJF\n");
    scanf("%d",&choice);
    switch(choice){
        case 1: nonPreemtiveSJF(p,n);
                break;
        case 2: preemptiveSJF(p,n);
                break;
        default:printf("Invalid Choice");
                return 0;
    }
    float total_wt = 0, total_tat = 0;
    printf("\nID\tArrival\tBurst\tExit\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    return 0;
}