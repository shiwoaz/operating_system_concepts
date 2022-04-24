#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int* arr = NULL;
int i = 0;
int times;

void* get_number()
{
    for (int j = 0; j < times; j++)
        if (j == 0 || j == 1)
            arr[j] = j;
        else
            arr[j] = arr[j - 1] + arr[j - 2];
    pthread_exit(0);
}

int main()
{
    scanf("%d", &times);

    arr = (int*)malloc(sizeof(int) * times);

    pthread_t id;

    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_create(&id, &attr, get_number, NULL);
    pthread_join(id, NULL);

    for (int j = 0; j < times; j++)
        printf("%d ", arr[j]);

    free(arr);
    return 0;
}