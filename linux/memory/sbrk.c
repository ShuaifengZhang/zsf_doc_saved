#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
int brk(void *addr);
void *sbrk(intptr_t increment);
*/
#define MAX 1024

int main(int argc, char* argv[])
{
    int* p = sbrk(0);  //得到当前堆的首地址
    int* old = p;

    p = sbrk(MAX*MAX);
    if(p == (void*)(-1))
    {
        perror("sbrk error.\n");
        exit(EXIT_FAILURE);
    }

    printf("p = %p\told = %p\n", p, old);

    int *new = sbrk(0);
    printf("new = %p\n", new);

    sbrk(-MAX*MAX);

    printf("pid = %d\n", getpid());
    while(1);  //cat /proc/pid/maps

    return 0;
}