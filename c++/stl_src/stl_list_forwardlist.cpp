#include "stl.h"
#include <list>
#include <vector>
#include <iostream>

using namespace std;

/*
1) list是双向链表，从C++11开始，还可以使用单向链表forward_list
2) list类的STL实现允许在开头、末尾和中间插入元素，且所需时间都固定。
3) C++11开始引入forward_list，它是一种单向链表，只允许沿着一个方向遍历(只能沿着一个方向移动迭代器)，且
插入元素时只能使用push_front，而不能使用push_back；当然总是可以使用insert及其重载版本在指定位置插入。
4) 对于要使用list等STL容器存储其对象的类，别忘了在其中实现运算符<和==,以提供默认的排序(sort)和删除(remove)
谓词（如果不想根据默认标准进行删除和排序，别忘了给sort和remove提供一个谓词函数）。
*/
template <typename T>
void show_element(const T& container)
{
    for (auto element = container.cbegin(); element != container.cend(); ++element)
        cout << *element << " " << endl;
}

bool sort_predicate_descending(const int& lhs, const int& rhs)
{
    return (lhs > rhs);
}

void stl_test::stl_list_forwardlist_test()
{
    vector<int> my_array(10, 2023);
    list<int> my_list(my_array.cbegin(), my_array.cend());
    my_list.push_front(1);
    my_list.push_back(1);
    show_element(my_list);

    list<int> my_list1;
    my_list1.insert(my_list1.begin(), my_list.begin(), my_list.end());
    show_element(my_list1);

    list<int> my_array2{1, 4, 3, -111};
    auto iterator = my_array2.insert(my_array2.begin(), 10);
    my_array2.erase(iterator);
    show_element(my_array2);

    /*排序：成员函数sort()有两个版本，其中一个没有参数，使用默认的排序谓词std::less<T>；另一个接受一个自
    定义二元谓词函数作为参数，让您能够指定排序标准。sort_predicate_descending是一个二元谓词，帮助sort()
    判断一个元素是否比另一个元素小，如果不是，则交换这两个元素的位置。换句话说，你告诉了list如果解释小于，
    就这里而言，小于的含义是第一个参数大于第二个参数。这个谓词仅在第一个值比第二个值大时返回true。也就是说，
    使用该谓词时，仅当第一个元素的数字值比第二个元素大时，sort才认为第一个元素比第二个元素小。基于这种解释，
    sort()交换元素的位置，以满足谓词指定的指标。
    */
    my_array2.sort(sort_predicate_descending);
    show_element(my_array2);
    /*如果list的元素为类，而不是int这种简单类型，如何排序呢？有两种方法，一种是在类中实现运算符<，另一种
    是提供一个一个二元谓词(接受两个输入值，并返回第一个布尔值，指出第一个值是否比第二个值小)*/

}