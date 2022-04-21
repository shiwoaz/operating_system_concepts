#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum;

void* runner(void* p)
{
	int i, upper = atoi(p);
	sum = 0;
	for (i = 1; i <= upper; i++)
		sum += i;
	pthread_exit(0);
}

int main(int argc, char* argv[])
{
	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, runner, argv[1]);

	pthread_join(tid, NULL);

	printf("the sum is %d\n", sum);
	return 0;
}
