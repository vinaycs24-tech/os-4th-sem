#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int pid;        
    int shares;     
} Process;

int schedule_next_process(Process proc_list[], int count) {
    int total_shares = 0;
    for (int i = 0; i < count; i++) {
        total_shares += proc_list[i].shares;
    }
    if (total_shares == 0) return -1;
    int ticket = rand() % total_shares;
    int cumulative = 0;
    for (int i = 0; i < count; i++) {
        cumulative += proc_list[i].shares;
        if (ticket < cumulative) {
            return proc_list[i].pid;
        }
    }
    return -1;
}

int main() {
    srand(time(NULL));
    Process table[] = {
        {101, 50}, 
        {102, 30}, 
        {103, 20}  
    };
    int count = sizeof(table) / sizeof(table[0]);
    printf("Simulating 10 CPU scheduling cycles:\n");
    printf("------------------------------------\n");
    for (int i = 0; i < 10; i++) {
        int winner = schedule_next_process(table, count);
        printf("Cycle %d: CPU allocated to PID %d\n", i + 1, winner);
    }
    return 0;
}