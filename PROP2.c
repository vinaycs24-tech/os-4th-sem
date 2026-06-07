#include <stdio.h>

#define TQ 10

typedef struct {
   int pid;
   int wt;
   int rem;
   int bt;
   int done;
} Tasks;

int main() {
     int n;


     printf("Enter number of processes: ");
     if (scanf("%d", &n) != 1 || n <= 0) return 1;

     Tasks t[n];
     int tot_wt = 0;


     for (int i = 0; i < n; i++) {
         t[i].pid = i + 1;
         printf("Enter burst time and weight for Process %d: ", t[i].pid);
         scanf("%d %d", &t[i].bt, &t[i].wt);

         t[i].rem = t[i].bt;
         t[i].done = 0;
         tot_wt += t[i].wt;
     }

     int comp = 0;
     printf("\n--- Starting Scheduler ---\nInitial Total Weight: %d\n\n", tot_wt);


     while (comp < n) {
        for (int i = 0; i < n; i++) {

            if (t[i].done == 0) {


                float exact_slice = ((float)t[i].wt / tot_wt) * TQ;
                int slice = (int)exact_slice;


                if (slice <= 0) {
                    slice = 1;
                }


                if (t[i].rem < slice) {
                    slice = t[i].rem;
                }

                printf("Process %d is running for %d units\n", t[i].pid, slice);


                t[i].rem -= slice;



                if (t[i].rem <= 0) {
                    t[i].done = 1;
                    comp++;
                    tot_wt -= t[i].wt;
                    printf(">> Process %d COMPLETED. New Total Weight: %d\n", t[i].pid, tot_wt);
                }
            }
        }
     }

     printf("\nAll processes finished.\n");
     return 0;
}
