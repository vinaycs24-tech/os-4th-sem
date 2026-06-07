#include <stdio.h>
#include <stdlib.h>

struct Task {
    int id;
    int execution;
    int period;
    int remaining;
    int deadline;
};


int checkSchedulability(struct Task tasks[], int n) {
    double utilization = 0.0;

    for (int i = 0; i < n; i++) {
        utilization += (double)tasks[i].execution / tasks[i].period;
    }

    printf("\n--- Schedulability Check ---\n");
    printf("Total CPU Utilization (U): %.4f\n", utilization);

    if (utilization > 1.0) {
        printf("[WARNING] U > 1.0. The task set is NOT schedulable under EDF!\n");
        return 0; // Not schedulable
    } else {
        printf("[SUCCESS] U <= 1.0. The task set is theoretically schedulable under EDF.\n");
        return 1;
    }
}

void earliestDeadlineFirst(struct Task tasks[], int n, int simulationTime) {
    int time = 0;
    printf("\n--- Earliest Deadline First (EDF) Simulation ---\n");

    while (time < simulationTime) {

        for (int i = 0; i < n; i++) {
            if (time > 0 && time % tasks[i].period == 0) {

                if (tasks[i].remaining > 0) {
                    printf("[ALERT] Time %2d: Task %d missed its deadline!\n", time, tasks[i].id);
                }


                tasks[i].remaining = tasks[i].execution;
                tasks[i].deadline = time + tasks[i].period;
            }
        }


        int selectedTask = -1;
        int minDeadline = 10000;

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {
                if (tasks[i].deadline < minDeadline) {
                    minDeadline = tasks[i].deadline;
                    selectedTask = i;
                }
            }
        }

        if (selectedTask != -1) {
            printf("Time %2d: Task %d is running (Absolute Deadline: %2d)\n",
                   time, tasks[selectedTask].id, tasks[selectedTask].deadline);
            tasks[selectedTask].remaining--;
        } else {
            printf("Time %2d: CPU is idle\n", time);
        }

        time++;
    }
}

int main() {
    int n, simulationTime;

    printf("Enter number of tasks: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    struct Task tasks[n];
    for (int i = 0; i < n; i++) {
        printf("\nEnter execution time and period for Task %d: ", i + 1);
        if (scanf("%d %d", &tasks[i].execution, &tasks[i].period) != 2) return 1;

        tasks[i].id = i + 1;
        tasks[i].remaining = tasks[i].execution;
        tasks[i].deadline = tasks[i].period;
    }

    printf("\nEnter total simulation time: ");
    if (scanf("%d", &simulationTime) != 1) return 1;


    checkSchedulability(tasks, n);


    earliestDeadlineFirst(tasks, n, simulationTime);

    return 0;
}

