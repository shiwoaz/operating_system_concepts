#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
    const char* NAME = "OS";
    const int SIZE = 4096;

    const char* MESSAGE_0 = "HellO ";
    const char* MESSAGE_1 = "Consumer!";

    printf("message length : %d %d\n", strlen(MESSAGE_0), strlen(MESSAGE_1));

    int fd; // shared memory file descriptor
    char* ptr; // pointer to shared memory object

    fd = shm_open(NAME, O_CREAT | O_RDWR, 0666); // create shared memory object
    if(fd == -1)
        exit(1);

    printf("shared memory object fd is %d\n", fd);

    ftruncate(fd, SIZE);

    ptr = (char*)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    char* temp = ptr;

    printf("shared memory object ptr is %p\n", ptr);

    // write to shared memory object
    sprintf(ptr, "%s", MESSAGE_0);
    ptr += strlen(MESSAGE_0);
    // ptr++; // strlen not calc \0 as a len
    sprintf(ptr, "%s", MESSAGE_1);
    ptr += strlen(MESSAGE_1);

    while(*temp) 
        printf("%c", *temp++);

    printf("\nProducor end\n");
    return 0;
}