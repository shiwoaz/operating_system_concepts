#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

/*
 *  export OMP_NUM_THREADS=10
 *  OMP lectures: https://www.youtube.com/watch?v=Ka3rBhwMgXg
 * 
 *  compile: cc -fopenmp omp.c && ./a.out
 */

#define TWO 2
#define GET_RANDOM (1.0 * rand() / (RAND_MAX / 2) - 1)

int in_circle = 0;
int total = 0;

int is_in_circle(float a, float b)
{
    if (a * a + b * b > 1)
        return 0;
    return 1;
}

int main()
{
    int times;
    scanf("%d", &times);

    omp_lock_t mutex;
    omp_init_lock(&mutex);

#pragma omp parallel for
    for (int i = 0; i < times; i++) {
        float x = GET_RANDOM;
        float y = GET_RANDOM;

        int in_c = is_in_circle(x, y);

        omp_set_lock(&mutex);
        if (in_c)
            in_circle++;
        total++;
        omp_unset_lock(&mutex);
    }

    printf("%f", 4 * (in_circle) / (float)(total));

    return 0;
}