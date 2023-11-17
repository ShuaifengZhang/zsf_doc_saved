cmake_minimum_required(VERSION 3.16.3)
project(src_stl_zsf)

set(C++_FILE_LIST
    ./stl_base_string.cpp
    ./stl_bitset.cpp
    ./stl_vector_deque.cpp
    ./stl_list_forwardlist.cpp
    ./stl_set_multiset_unorderedset_unorderedmultiset.cpp
    ./stl_map_multimap_unorderedmap_unorderedmultimap.cpp
    ./stl_stack_queue_priorityqueue.cpp
    ./functor_predicate.cpp
    ./functor_lambda.cpp)

add_library(zsf_stl_src SHARED ${C++_FILE_LIST})