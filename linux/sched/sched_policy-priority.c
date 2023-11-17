#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <assert.h>

static int get_thread_policy(pthread_attr_t* attr)
{
    int plicy;
    int rs = pthread_attr_getschedpolicy(attr, &plicy);  //得到线程调度策略
    
    assert(rs == 0);

    switch(plicy)
    {
    case SCHED_FIFO:
        printf("policy = SCHED_FIFO\n");
        break;
    case SCHED_RR:
        printf("policy = SCHED_RR\n");
        break;
    case SCHED_OTHER:
        printf("policy = SCHED_OTHER\n");
        break;
    default:
        printf("policy = UNKNOW\n");
        break;
    }

    return plicy;
}

static void show_thread_priority(pthread_attr_t* attr, int policy)
{
    int priority = sched_get_priority_max(policy);  //获取实时优先级的最大值
    assert(priority != -1);
    printf("max_priority = %d\n", priority);

    priority = sched_get_priority_min(policy);  //获取实时优先级的最小值
    assert(priority != -1);
    printf("min_priority = %d\n", priority);
}

static int get_thread_priority(pthread_attr_t* attr)
{
    struct sched_param param;
    int rs = pthread_attr_getschedparam(attr, &param); //得到线程的优先级
    assert(rs == 0);

    printf("priority = %d\n", param.sched_priority);

    return param.sched_priority;
}

static void set_thread_policy(pthread_attr_t* attr, int policy)
{
    int rs = pthread_attr_setschedpolicy(attr, policy); //设置线程调度策略
    assert(rs == 0);
    get_thread_policy(attr);
}

int main()
{
    pthread_attr_t attr;
    struct sched_param sched;

    int rs = pthread_attr_init(&attr);
    assert(0  == rs);
    int plicy = get_thread_policy(&attr);
    printf("output current configuration of priority.\n");
    show_thread_priority(&attr, plicy);

    printf("output SCHED_FIFO of priority.\n");
    show_thread_priority(&attr, SCHED_FIFO);

    printf("output SCHED_RR of priority.\n");
    show_thread_priority(&attr, SCHED_RR);

    int priority = get_thread_priority(&attr);
    set_thread_policy(&attr, SCHED_FIFO);
    set_thread_policy(&attr, SCHED_RR);
    set_thread_policy(&attr, plicy);

    rs = pthread_attr_destroy(&attr);
    assert(rs == 0);

    return 0;
}