#include "stl.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

/*
1) 虽然大多数算法都通过迭代器对容器进行操作，但并非所有算法都对容器进行操作，因此并非所有算法都需要迭代器。有一些算法接受一对值，
例如swap()将这对值交换。同样min()和max()也对值进行操作。
2) stl算法分为二大类：变序算法和非变序算法。非变序算法指的是不改变容器中元素的顺序和内容的算法，同理变序算法会改变其操作的序列的
元素顺序或内容。
3) 主要的非变序算法有：
    a. 计数算法：count()、count_if()
    b. 搜索算法：search()、search_n()、find()、find_if()、find_end()、find_first_of()、adjacent_find()
    c. 比较算法：equal()、mismatch()、lexicographical_compare()
4) 主要变序算法有：
    a. 初始化算法：fill()、fill_n()、generate()、generate_n()
    b. 修改算法：for_each()、transform()
    c. 复制算法：copy()、copy_backward()
    d. 删除算法：remove()、remove_if()、remove_copy()、remove_copy_if()、unique()、unique_copy()
    e. 替换算法：replace()、replace_if()
    f. 排序算法：sort()、stable_sort()、partial_sort()、partial_sort_copy()
    g. 分区算法：partition()、stable_partition()
    h. 可用于有序容器的算法：binary_search()、lower_bound()、upper_bound()
*/
using namespace std;
vector<int> numsInVec{2017, 0, -1, 42, 10101, 25, 9, 9, 9};
list<int> numsInList{-1, 42, 10101};
vector<int> numsInVec1(3);

template <typename T>
bool IsEven(const T& number)
{
    return ((number % 2) == 0);
}

void stl_test::stl_algorithm_test()
{
    /*查找与值配置或满足条件的元素*/
    auto element = find(numsInVec.cbegin(), numsInVec.cend(), 42);
    if (element != numsInVec.cend())
        cout << "Value " << *element << " found!" << endl;
    auto evenNum = find_if(numsInVec.cbegin(), numsInVec.cend(), [](int element) {return (element % 2) == 0;}); //需要提供一个一元谓词
    if (evenNum != numsInVec.cend())
        cout << "Number '" << *evenNum << "' found at position [" << distance(numsInVec.cbegin(), evenNum) << "]" << endl << endl;
    /*计算包含给定值或满足给定条件的元素数*/
    size_t numZeros = count(numsInVec.cbegin(), numsInVec.cend(), 0);
    cout << "Number of instances of '0': " << numZeros << endl;
    size_t numEvenNums = count_if(numsInVec.cbegin(), numsInVec.cend(), IsEven<int>); //需要一个一元谓词
    cout << "Number of even elements: " << numEvenNums << endl << endl;
    /*在集合中搜索元素或序列*/
    auto range = search(numsInVec.cbegin(), numsInVec.cend(), numsInList.cbegin(), numsInList.cend());
    if (range != numsInVec.end())
        cout << "Sequence in list found in vector at position: " << distance(numsInVec.cbegin(), range) << endl;
    auto partialRange = search_n(numsInVec.cbegin(), numsInVec.cend(), 3, 9);
    if (partialRange != numsInVec.end())
        cout << "Sequence{9, 9, 9} found in vector at position: " << distance(numsInVec.cbegin(), partialRange) << endl << endl;
    /*将容器中的元素初始化为指定值，注意这里没有使用常量迭代器cbegin/cend，这是因为常量迭代器禁止修改它们指向的元素，而这里需要修改容器中的元素*/
    fill(numsInVec1.begin(), numsInVec1.end(), 9);
    numsInVec1.resize(6);
    fill_n(numsInVec1.begin() + 3, 3, -9);
    for (size_t index = 0; index < numsInVec1.size(); ++index)
        cout << "Element [" << index << "] = " << numsInVec1.at(index) << endl << endl;
}