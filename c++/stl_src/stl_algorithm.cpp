#include "stl.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <deque>
#include <functional>

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

/*注意点：
binary_search()算法可用于快速查找，这种算法只能用于有序容器(经过排序的容器)。
相比sort(), stable_sort()确保排序后元素的相对顺序保持不变。
*/
using namespace std;
string str("The for_each and strings");
vector<int> numsInVec{2017, 0, -1, 42, 10101, 25, 9, 9, 9};
list<int> numsInList{-1, 42, 10101};
vector<int> numsInVec1(3);
vector<int> numsInVec2(5);
vector<int> numsInVec3(numsInVec.size(), -1);
deque<int> sumInDeque(numsInVec.size(), -1);
vector<int> numsInVec4(numsInList.size() * 2);
list<string> names {"xiaoyi", "jack", "sill", "ann", "ao"};

template <typename T>
bool IsEven(const T& number)
{
    return ((number % 2) == 0);
}

template <typename T>
struct DisplayElementKeepcount
{
    int count;
    DisplayElementKeepcount(): count(0) {}

    void operator() (const T& element)
    {
        ++count;
        cout << element << " ";
    }
};

template <typename T>
void Display(const T& cont)
{
    for (auto ele = cont.cbegin(); ele != cont.cend(); ++ele)
        cout << *ele << endl;
    cout << endl;
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
    /*在有序集合中查找并插入元素*/
    names.sort();
    Display(names);
    auto minPos = lower_bound(names.begin(), names.end(), "brad");  //提供有序集合中的第一个位置
    cout << "insert pos: " << distance(names.begin(), minPos) << endl;
    names.insert(minPos, "brad");   //返回折半查找的位置
    Display(names);
    auto maxPos = upper_bound(names.begin(), names.end(), "brad");  //提供有序集合中的最后一个位置
    cout << "insert pos: " << distance(names.begin(), maxPos) << endl;
    names.insert(maxPos, "brad");
    Display(names);
    /*将容器中的元素初始化为指定值，注意这里没有使用常量迭代器cbegin/cend，这是因为常量迭代器禁止修改它们指向的元素，而这里需要修改容器中的元素*/
    fill(numsInVec1.begin(), numsInVec1.end(), 9);
    numsInVec1.resize(6);
    fill_n(numsInVec1.begin() + 3, 3, -9);
    random_shuffle(numsInVec1.begin(), numsInVec1.end()); //将值打乱
    for (size_t index = 0; index < numsInVec1.size(); ++index)
        cout << "Element [" << index << "] = " << numsInVec1.at(index) << endl << endl;
    /*将集合的内容设置为一元函数返回的值*/
    generate(numsInVec2.begin(), numsInVec2.end(), rand);   //generate_n(numsInVec2.begin(), 5, rand);
    for (size_t index = 0; index < numsInVec2.size(); ++index)
        cout << numsInVec2[index] << " ";
        cout << endl << endl;
    /*for_each()对指定范围内的每个元素执行指定的一元函数对象(当然也可以使用接受一个参数的lambda表达式代替一元函数对象)。该算法返回用于对指定范围内
    的每个元素进行处理的函数对象。那么这也就意味着如果使用结构或类作为函数对象来存储状态信息，就可在for_each执行完毕后查询这些状态信息。*/
    DisplayElementKeepcount<int> functor = for_each(numsInVec.cbegin(), numsInVec.cend(), DisplayElementKeepcount<int>());
    cout << endl;
    cout << " " << functor.count << " elements dispalyed" << endl;
    int numChars = 0;
    for_each(str.cbegin(), str.cend(), [&numChars](char c) {cout << c << " " ; ++numChars;});
    cout << endl;
    cout << "'" << numChars << "' characters displayed" << endl << endl;
    /*transform和for_each很像，都对源范围内的每个元素调用指定的函数对象。然而transform有两个版本，第一个版本接受一个一元函数，常用于将字符串转为大写
    或小写使用的一元函数分别是toupper()和tolower()；另一个版本接受一个二元函数，让transform能够处理一对来自两个不同范围的元素。不像for_each那样只处理
    一个范围，这两个版本的transform()都将指定变换函数的结果赋值给指定的目标范围*/ 
    string strLowerCaseCopy;
    strLowerCaseCopy.resize(str.size());
    transform(str.cbegin(), str.cend(), strLowerCaseCopy.begin(), ::tolower);
    cout << "\"" << strLowerCaseCopy << "\"" << endl;
    transform(numsInVec.cbegin(), numsInVec.cend(), numsInVec3.cbegin(), sumInDeque.begin(), plus<int>());
    for (size_t index = 0; index < numsInVec.size(); ++index)
        cout << index << " \t " << numsInVec[index] << "\t+ " << numsInVec3[index] << " \t = " << sumInDeque[index] << endl;
    cout << endl;
    /*拷贝和删除, 其中copy_back()是沿向反的方向将源范围的内容赋给目标范围*/
    auto lastElement = copy(numsInList.cbegin(), numsInList.cbegin(), numsInVec4.begin());
    copy_if(numsInList.cbegin(), numsInList.cend(), lastElement, [](int element) {return ((element % 2) != 0);});
    auto newEnd = remove(numsInVec4.begin(), numsInVec4.end(), 0); //删除所有为0的元素，返回指向容器末尾的迭代器，但此时容器大小不变
    numsInVec4.erase(newEnd, numsInVec4.end()); //resize vector using erase()
    newEnd = remove_if(numsInVec4.begin(), numsInVec4.end(), [](int element) {return ((element % 2) != 0);});
    numsInVec4.erase(newEnd, numsInVec4.end());
    newEnd = unique(numsInVec4.begin(), numsInVec4.end());
    numsInVec4.erase(newEnd, numsInVec4.end());
    /*替换值以及替换满足给定条件的元素*/
    replace(numsInVec.begin(), numsInVec.end(), 9, 8);   //replace 9 by 8
    replace_if(numsInVec.begin(), numsInVec.end(), [](int element) {return (element == 8);}, -1);
    /*分区: 将输入范围分为两部分，一部分满足一元谓词，另一部分不满足*/
    partition(numsInVec.begin(), numsInVec.end(), IsEven<int>);
    vector<int> vecCpy(numsInVec);
    stable_partition(vecCpy.begin(), vecCpy.end(), IsEven<int>);
}