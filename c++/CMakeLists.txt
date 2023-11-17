cmake_minimum_required(VERSION 3.16.3)
project(main_stl_zsf)

add_subdirectory(stl_src)
add_subdirectory(multi-thread_src)

set(MAIN_FILE ./main.cpp)
add_executable(zsf_stl_main ${MAIN_FILE})
target_link_libraries(zsf_stl_main zsf_stl_src zsf_multi-thread_src)