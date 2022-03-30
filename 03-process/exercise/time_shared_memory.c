#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

#define MAX_LENGTH (sizeof(char) * 100)

// mircosecond -> second
float convert_micosecond_to_second(time_t time)
{
    return time / (float)1000000;
}

int main(int argc, char* argv[])
{
    // at least two args
    if (argc < 2) {
        fprintf(stdout, "need more arguments\n");
        exit(1);
    }

    // shared memory name
    char* NAME = "TIME_TRANSFER";

    int share_id;
    share_id = shm_open(NAME, O_CREAT | O_RDWR, 0666);

    ftruncate(share_id, MAX_LENGTH);

    char* share_head;
    share_head = (char*)mmap(NULL, MAX_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, share_id, 0);

    pid_t id;
    id = fork();
    if (id < 0) {
        fprintf(stdout, "process fork error\n");
        exit(1);
    } else if (id == 0) { // child process
        char command[MAX_LENGTH] = "";
        for (size_t i = 1; i < argc; i++) {
            strcat(command, argv[i]);
            if (i != argc - 1)
                strcat(command, " ");
        }
        printf("%s\n", command);

        struct timeval tv_start, tv_end;
        time_t start, end;

        gettimeofday(&tv_start, NULL);
        start = tv_start.tv_usec;
        system(command);
        gettimeofday(&tv_end, NULL);
        end = tv_end.tv_usec;

        int child_shared_id;
        child_shared_id = shm_open(NAME, O_RDWR, 0666);

        if(child_shared_id == -1) {
            printf("child process shared memory open fail\n");
            exit(1);
        }

        char *memory_ptr;
        memory_ptr = mmap(0, MAX_LENGTH, PROT_WRITE, MAP_SHARED, child_shared_id, 0);
        sprintf(memory_ptr, "%.6f", convert_micosecond_to_second(end - start));
    } else {
        wait(NULL);
        printf("the time usage is %s\n", share_head);
    }

    return 0;
}