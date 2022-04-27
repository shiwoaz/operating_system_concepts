#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MIN_PID 30
#define MAX_PID 50

unsigned int* pid_manager = NULL;
int i = -1; // pointer to the current position
sem_t mutex; // prevent varible i race condition

int allocate_map(void)
{
    pid_manager = (unsigned int*)malloc(sizeof(unsigned int) * (MAX_PID - MIN_PID));
    if (pid_manager) {
        for (int i = 0; i < MAX_PID - MIN_PID; i++)
            pid_manager[i] = 0;
        return 1;
    }
    return -1;
}

int allocate_pid(void)
{
    int next;
    sem_wait(&mutex);
    next = (i + 1) % (MAX_PID - MIN_PID);
    printf("next %d\n", next);
    while (next != i) {
        if (pid_manager[next] == 0) {
            pid_manager[next] = 1;
            break;
        } else
            next = (next + 1) % (MAX_PID - MIN_PID);
    }
    if (i == next) {
        printf("No free pid.\n");
        sem_post(&mutex);
        return -1;
    } else {
        i = next;
        sem_post(&mutex);
    }
    sem_post(&mutex);
    return next;
}

void release_pid(unsigned int pid)
{
    if (pid > MAX_PID - MIN_PID)
        return;
    pid_manager[pid] = 0;
}

void* routine()
{
    unsigned int pid = allocate_pid();

    if (pid == -1) {
        printf("No available pid\n");
    } else {
        printf("Get pid %d\n", pid);
        sleep(2);
        release_pid(pid);
        printf("Relese pid %d\n", pid);
    }
    pthread_exit(0);
}

int main()
{
    pthread_t ids[100];
    pthread_attr_t attr;

    if (allocate_map() == -1) {
        printf("Can't create a map\n");
        return 0;
    }

    sem_init(&mutex, 0, 1);

    pthread_attr_init(&attr);

    int pthread_num = 100;
    for (int i = 0; i < pthread_num; i++) {
        pthread_create(ids + i, &attr, routine, NULL);
    }

    for (int i = 0; i < pthread_num; i++) {
        pthread_join(ids[i], NULL);
    }

    sem_destroy(&mutex);

    return 0;
}