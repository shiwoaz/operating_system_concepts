// 4.22
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREADS_NUMBER 3
#define INPUT_NMBER 10

float average;
int minimun, maximun;

typedef struct {
    int* array;
    int count;
} Arg;

void* calc_average(void* arg)
{
    int sum = 0;
    int count = ((Arg*)arg)->count;
    int* arr = ((Arg*)arg)->array;
    for (int i = 0; i < count; i++) {
        sum += arr[i];
        printf("[average] -- %d\n", arr[i]);
    }
    average = sum / (float)count;
    pthread_exit(0);
}

void* calc_minimum(void* arg)
{
    int min = INT32_MAX;
    int count = ((Arg*)arg)->count;
    int* arr = ((Arg*)arg)->array;
    for (int i = 0; i < count; i++) {
        min = arr[i] < min ? arr[i] : min;
        printf("[min] -- %d\n", arr[i]);
    }
    minimun = min;
    pthread_exit(0);
}

void* calc_maximun(void* arg)
{
    int max = -1;
    int count = ((Arg*)arg)->count;
    int* arr = ((Arg*)arg)->array;
    for (int i = 0; i < count; i++) {
        max = arr[i] > max ? arr[i] : max;
        sleep(2);
        printf("[max] -- %d\n", arr[i]);
    }
    maximun = max;
    pthread_exit(0);
}

int in(int* x)
{
    scanf("%d", x);
    return *x;
}

int main()
{
    pthread_t ids[THREADS_NUMBER];

    int count = 0;
    int input[INPUT_NMBER] = { 0 };

    int* p_input = input;

    // scanf number from console, stopped by 0
    while (in(p_input + count) != 0)
        count++;

    // create thread
    pthread_attr_t p_attr;
    pthread_attr_init(&p_attr);

    void* (*p_functions[])(void*) = {
        calc_average,
        calc_maximun,
        calc_minimum,
    };

    Arg arg = { .array = input, .count = count };

    for (int i = 0; i < THREADS_NUMBER; i++) {
        pthread_create(ids + i, &p_attr, p_functions[i], &arg);
    }

    for (int i = 0; i < THREADS_NUMBER; i++) {
        pthread_join(ids[i], NULL);
    }

    printf("The average value is %.2f\n", average);
    printf("The minimum value is %d\n", minimun);
    printf("The maximum value is %d\n", maximun);

    return 0;
}
