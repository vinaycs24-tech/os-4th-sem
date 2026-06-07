#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
sem_t room;   // Controls entry

void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        // Allow only 4 philosophers at a time
        sem_wait(&room);

        // Pick forks
        sem_wait(&forks[id]);
        sem_wait(&forks[(id + 1) % N]);

        printf("Philosopher %d is eating\n", id);
        sleep(2);

        // Release forks
        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);

        // Leave room
        sem_post(&room);

        printf("Philosopher %d finished eating\n", id);
    }
}

int main() {
    pthread_t phil[N];
    int ids[N];

    // Initialize fork semaphores
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // Only 4 philosophers allowed
    sem_init(&room, 0, N - 1);

    // Create threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &ids[i]);
    }

    // Join threads
    for (int i = 0; i < N; i++) {
        pthread_join(phil[i], NULL);
    }

    return 0;
}