#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t id;
    int state;
    id = fork();
    if (id) { // in parent process id is the pid of the process that use this fork system call create.
        // wait 返回的值是 child 的
        pid_t cc = wait(&state); // wait child process finish
        printf("%d \t hello from parent process\n cc is %d  state is %d\n", id, cc, id);
    }
    if (!id) { // in child process id == 0
        int d;
        printf("%d \t hello from child process\n", id);
        scanf("%d", &d);
        printf("%d \t d from child process\n", d);
        // replace the code  both output not exec in child process
        execlp("/bin/ls", "ls", NULL);
        exit(10);
    }
    printf("both output"); // only print in p process
    return 0;
}
