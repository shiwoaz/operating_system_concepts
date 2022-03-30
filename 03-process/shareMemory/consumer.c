#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
    const char* NAME = "OS";
    const int SIZE = 4096;

    int fd;
    char* ptr;

    fd = shm_open(NAME, O_RDONLY, 0666);
    if(fd == -1) {
        printf("consumer shared memery worry\n");
        exit(1);
    }
    printf("shared memory object fd is %d\n", fd);

    ptr = (char*)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    printf("shared memory object ptr is %p\n", ptr);

    printf("%s", (char*)ptr);

    shm_unlink(NAME);
    return 0;
}