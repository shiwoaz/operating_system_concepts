#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 256
#define READ_END 0
#define WRITER_END 1

// mircosecond -> second
float convert_micosecond_to_second(struct timeval* end, struct timeval* start)
{
    return (end->tv_usec = start->tv_usec) / (float)1000000;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, "need more args");
        exit(1);
    }

    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        fprintf(stderr, "pipe init failed");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        fprintf(stdout, "process fork error\n");
        exit(1);
    } else if (pid == 0) { // child process
        char command[BUFFER_SIZE] = "";
        for (size_t i = 1; i < argc; i++) {
            strcat(command, argv[i]);
            if (i != argc - 1)
                strcat(command, " ");
        }

        struct timeval tv_start, tv_end;
        gettimeofday(&tv_start, NULL);
        system(command);
        gettimeofday(&tv_end, NULL);

        char buffer[BUFFER_SIZE] = "";
        sprintf(buffer, "%.6f", convert_micosecond_to_second(&tv_end, &tv_start));

        close(fd[READ_END]);
        write(fd[WRITER_END], buffer, strlen(buffer) + 1);
        close(fd[WRITER_END]);
    } else { // parent process
        char read_buffer[BUFFER_SIZE] = "";
        close(fd[WRITER_END]);
        read(fd[READ_END], read_buffer, BUFFER_SIZE);
        close(fd[READ_END]);

        printf("time use is %s", read_buffer);
    }

    return 0;
}