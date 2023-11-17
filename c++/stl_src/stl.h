#ifndef __STL_H__
#define __STL_H__

class stl_test {
public:
    /*字符串类*/ 
    void stl_base_string_test();
    /*位操作类*/
    void stl_bitset_test();
    /*顺序容器*/
    void stl_vecotr_deque_test(); 
    void stl_list_forwardlist_test();
    /*关联容器*/
    void stl_set_multiset_unorderedset_unorderedmultiset_test();
    void stl_map_multimap_unorderedmap_unorderedmultimap_test();
    /*容器适配器*/
    void stl_stack_queue_priorityqueue_test();
    /*函数对象/谓词/lambda表达式*/
    void functor_predicate_test();
    void functor_lambda_test();
};

#endif