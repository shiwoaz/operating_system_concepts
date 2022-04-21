#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TWO 2
#define GET_RANDOM (1.0 * rand() / (RAND_MAX / 2) - 1)

int in_circle = 0;
int total = 0;

pthread_mutex_t mutex;

int is_in_circle(float a, float b)
{
    if (pow(a, TWO) + pow(b, TWO) > 1)
        return 0;
    return 1;
}

void* runner()
{
    float x = GET_RANDOM;
    float y = GET_RANDOM;

    int in_c = is_in_circle(x, y);

    pthread_mutex_lock(&mutex);
    if (in_c)
        in_circle++;
    total++;
    pthread_mutex_unlock(&mutex);
    // printf("in circle is %d, totoal is %d\n", in_circle, total);

    pthread_exit(0);
}

int main()
{
    srand(time(NULL));

    int times;

    scanf("%d", &times);

    pthread_t* ids = (pthread_t*)malloc(sizeof(pthread_t) * times);

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < times; i++)
        pthread_create(ids + i, &attr, runner, NULL);

    for (int i = 0; i < times; i++)
        pthread_join(ids[i], NULL);

    pthread_mutex_destroy(&mutex);
    free(ids);

    printf("%f", 4 * (in_circle) / (float)(total));

    return 0;
}