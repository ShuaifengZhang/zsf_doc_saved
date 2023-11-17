#include "stl.h"
#include <vector>
#include <iostream>

using namespace std;

/*
1) 动态数组：无需在编写应用程序时就知道数组的长度，因此在不知道要存储多少个元素时可以使用。
2) 大小为实际存储的元素数，可使用成员函数size()；其小于等于容量(可使用成员函数capacity())。
3) 成员函数reserve(number)为动态数组的内部缓冲区分配/预留内存空间，这样在插入元素时，vector/deqeu就需要
重新分配缓冲区并复制现有内容；这样可以提高性能。
4) deque与vector非常类似，但支持在数组开头(push_front和pop_front)和末尾插入或删除元素。
*/
template <typename T>
void display_vector(const vector<T>& invec)
{
    auto element = invec.cbegin();
    while (element != invec.cend()) {
        size_t index = distance(invec.cbegin(), element);
        cout << "Element at position" << index << " is: " << *element << endl;
        ++element;
    }
}

void stl_test::stl_vecotr_deque_test()
{
    vector<int> my_array {1, 2, 3};
    vector<int> my_array1 (2, 10);
    my_array.push_back(4); //删除可用pop_back()
    my_array.insert(my_array.begin() + 1, my_array1.begin(), my_array1.end());  //在任意位置插入
    my_array1.clear(); //清空所有元素
    /*使用下标[]访问元素比较危险，因此可使用at()，它会在运行阶段检查容器大小，如果索引超出边界将引发异常*/
    cout << my_array.at(1) << endl; 
    /*使用指针语法访问*/
    display_vector(my_array);
}