cmake_minimum_required(VERSION 3.16.3)
project(src_multi-thread_zsf)

set(C++_FILE_LIST
    ./thread_pool.cpp
    ./async_packaged_task_promise.cpp)

add_library(zsf_multi-thread_src SHARED ${C++_FILE_LIST})