#include "stl_src/stl.h"
#include "multi-thread_src/multi-thread.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[])
{
    stl_test test;
    //test.stl_base_string_test();
    //test.stl_bitset_test();
    //test.stl_vecotr_deque_test();
    //test.stl_list_forwardlist_test();
    //test.stl_set_multiset_unorderedset_unorderedmultiset_test();
    //test.stl_map_multimap_unorderedmap_unorderedmultimap_test();
    //test.stl_stack_queue_priorityqueue_test();
    //test.functor_predicate_test();
    //test.functor_lambda_test();
    test.stl_algorithm_test();
   
    /*多线程测试*/
    //multi_thread_test thread;
    //thread.thread_pool_test();
    //thread.async_packaged_task_promise_test();

    return 0;
}