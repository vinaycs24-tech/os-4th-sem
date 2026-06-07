#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int rem_bt;
    int first_exec;
};


struct Queue {
    int items[100];
    int front, rear;
};

void initQueue(struct Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(struct Queue *q) {
    return q->front == -1;
}

void enqueue(struct Queue *q, int value) {
    if (q->rear == 99) return;
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

int dequeue(struct Queue *q) {
    if (isEmpty(q)) return -1;
    int val = q->items[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return val;
}

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rem_bt = p[i].bt;
        p[i].first_exec = -1;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    struct Queue ready;
    initQueue(&ready);

    int time = 0, completed = 0;
    float totalWT = 0, totalRT = 0;

    for (int i = 0; i < n; i++) {
        if (p[i].at == 0) {
            enqueue(&ready, i);
        }
    }

    while (completed < n) {
        if (!isEmpty(&ready)) {
            int idx = dequeue(&ready);

            if (p[idx].first_exec == -1) {
                p[idx].first_exec = time;
            }

            if (p[idx].rem_bt > tq) {
                time += tq;
                p[idx].rem_bt -= tq;
            } else {
                time += p[idx].rem_bt;
                p[idx].rem_bt = 0;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                p[idx].rt = p[idx].first_exec - p[idx].at;
                totalWT += p[idx].wt;
                totalRT += p[idx].rt;
                completed++;
            }

            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && p[i].rem_bt > 0) {
                    int alreadyInQueue = 0;
                    for (int j = ready.front; j <= ready.rear; j++) {
                        if (ready.items[j] == i) {
                            alreadyInQueue = 1;
                            break;
                        }
                    }
                    if (!alreadyInQueue && i != idx) {
                        enqueue(&ready, i);
                    }
                }
            }

            if (p[idx].rem_bt > 0) {
                enqueue(&ready, idx);
            }
        } else {
            time++;
            for (int i = 0; i < n; i++) {
                if (p[i].at == time) {
                    enqueue(&ready, i);
                }
            }
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct,
               p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Response Time: %.2f\n", totalRT / n);

    return 0;
}
