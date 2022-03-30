#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    pid_t id;
    id = fork();

    if(id < 0) {
        fprintf(stdout, "process fork error\n");
        exit(1);
    } else if(id == 0) {
        sleep(10);
        fprintf(stdout, "child process id is %d\n", getpid());
    } else {
        system("ps -l");
        pid_t pid = getpid();
        fprintf(stdout, "parent process id is %d\n", pid);
        char command[20] = "kill -9 ";
        char pid_str[5] = "";
        sprintf(pid_str, "%d", pid);
        printf("%s\n", strcat(command, pid_str));
        // system(command);
    }
    return 0;
}