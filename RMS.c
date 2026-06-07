#include <stdio.h>
#include <limits.h>

struct Task {
    int id;
    int execution;
    int period;
    int remaining;
};

void rateMonotonic(struct Task tasks[], int n, int simulationTime) {
    printf("\n--- Rate Monotonic Scheduling Simulation ---\n");

    for (int time = 0; time < simulationTime; time++) {

        /* Release new jobs */
        for (int i = 0; i < n; i++) {
            if (time > 0 && time % tasks[i].period == 0) {

                /* Check deadline miss */
                if (tasks[i].remaining > 0) {
                    printf("Time %2d: Deadline MISS by Task %d\n",
                           time, tasks[i].id);
                }

                tasks[i].remaining += tasks[i].execution;
            }
        }

        int highestPriority = -1;
        int minPeriod = INT_MAX;

        /* Select highest-priority ready task */
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0 &&
                tasks[i].period < minPeriod) {

                minPeriod = tasks[i].period;
                highestPriority = i;
            }
        }

        if (highestPriority != -1) {
            printf("Time %2d: Task %d is running\n",
                   time, tasks[highestPriority].id);

            tasks[highestPriority].remaining--;
        } else {
            printf("Time %2d: CPU is idle\n", time);
        }
    }
}

int main() {
    int n, simulationTime;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    struct Task tasks[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter execution time and period for Task %d: ", i + 1);
        scanf("%d %d", &tasks[i].execution, &tasks[i].period);

        tasks[i].id = i + 1;
        tasks[i].remaining = tasks[i].execution;   // first release at t=0
    }

    printf("\nEnter total simulation time: ");
    scanf("%d", &simulationTime);

    rateMonotonic(tasks, n, simulationTime);

    return 0;
}
