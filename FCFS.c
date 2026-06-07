#include<stdio.h>

struct process{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int st;
};

int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    struct process p[n];
    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        printf("Enter Arrival Time of P%d: ", p[i].pid);
        scanf("%d",&p[i].at);
        printf("Enter Burst Time of P%d: ", p[i].pid);
        scanf("%d",&p[i].bt);
    }
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(p[j].at>p[j+1].at){
                struct process temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    int time=0;
    for(int i=0;i<n;i++){
        if(time<p[i].at){
            time=p[i].at;
        }
        p[i].st=time;
        p[i].rt=p[i].st-p[i].at;
        time+=p[i].bt;
        p[i].ct=time;
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
    }
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    }
}