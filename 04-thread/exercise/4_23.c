#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int input;

void* runner()
{
    for (int i = 2; i <= input; i++) {
        int flag = 1;
        for (int j = 2; j <= sqrt(i); j++) {
            if (i % j == 0) {
                flag = 0;
                break;
            }
        }
        if (flag)
            printf("%d ", i);
    }
    pthread_exit(0);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Need the input number!\n");
        return 0;
    }

    input = atoi(argv[1]);

    pthread_t id;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_create(&id, &attr, runner, NULL);

    pthread_join(id, NULL);
}