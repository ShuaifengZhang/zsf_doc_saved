#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void threadfunc1()
{
    sleep(1);
    int policy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(), &policy, &param);

    if(policy == SCHED_OTHER)
        printf("SCHED_OTHER.\n");

    if(policy == SCHED_RR)
        printf("SCHED_RR.\n");

    if(policy == SCHED_FIFO)
        printf("SCHED_FIFO.\n");

    for (int i = 1; i<=10; ++i)
    {
        for (int j = 1; j < 400000; ++j) {}
        printf("threadfunc1\n");
    }
    printf("threadfunc1 exit\n");
}

void threadfunc2()
{
    sleep(1);
    int policy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(), &policy, &param);

    if(policy == SCHED_OTHER)
        printf("SCHED_OTHER.\n");

    if(policy == SCHED_RR)
        printf("SCHED_RR.\n");

    if(policy == SCHED_FIFO)
        printf("SCHED_FIFO.\n");

    for (int i = 1; i<=10; ++i)
    {
        for (int j = 1; j < 400000; ++j) {}
        printf("threadfunc2\n");
    }
    printf("threadfunc2 exit\n");   
}

void threadfunc3()
{
    sleep(1);
    int policy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(), &policy, &param);

    if(policy == SCHED_OTHER)
        printf("SCHED_OTHER.\n");

    if(policy == SCHED_RR)
        printf("SCHED_RR.\n");

    if(policy == SCHED_FIFO)
        printf("SCHED_FIFO.\n");

    for (int i = 1; i<=10; ++i)
    {
        for (int j = 1; j < 400000; ++j) {}
        printf("threadfunc3\n");
    }
    printf("threadfunc3 exit\n");  
}


int main(int argc, char* argv[])
{
    int i = getuid();
    if (i == 0)
        printf("the current user is root\n");

    pthread_t ppid1, ppid2, ppid3;
    struct sched_param param;

    pthread_attr_t attr1, attr2, attr3;
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);

    param.sched_priority = 51;
    pthread_attr_setschedpolicy(&attr3, SCHED_RR);
    pthread_attr_setschedparam(&attr3, &param);
    pthread_attr_setinheritsched(&attr3, PTHREAD_EXPLICIT_SCHED);

    param.sched_priority = 22;
    pthread_attr_setschedpolicy(&attr2, SCHED_RR);
    pthread_attr_setschedparam(&attr2, &param);
    pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);

    pthread_create(&ppid3, &attr1, (void*)threadfunc3, NULL);
    pthread_create(&ppid2, &attr2, (void*)threadfunc2, NULL);
    pthread_create(&ppid1, &attr3, (void*)threadfunc1, NULL);

    pthread_join(ppid3, NULL);
    pthread_join(ppid2, NULL);
    pthread_join(ppid1, NULL);

    pthread_attr_destroy(&attr3);
    pthread_attr_destroy(&attr2);
    pthread_attr_destroy(&attr1);


    return 0;
}