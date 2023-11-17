#include "stl.h"
#include <set>
#include <unordered_set>
#include <iostream>

using namespace std;
/*
1) 集合类set和multiset用于存储一组经过排序的元素，其查找方法的复杂度为对数，而unordered集合的插入和查找
时间是固定的。
2) 容器set和multiset可让程序员能够在容器中查找键，键是存储在一维容器中的值。set和multiset之间的区别在于
后者可以存储重复的值(可以通过multiset::count(元素值)确定包含多少个这样的元素)，而前者只能存储唯一的值。
要使用set或multiset类，需要包含头文件<set>。
3) 鉴于set和multiset都是在插入时对元素进行排序的容器，如果您没有指定排序标准，它们将使用默认谓词std::less，
确保包含的元素按升序排列。要创建二元排序谓词，可在类中定义一个operator()，让它接受两个参数(其类型与集合存储
的数据类型相同)，并且根据排序标准返回true。下面是一个这样的排序谓词，它按降序排列元素：
    template <typename T>
    struct sortDescending
    {
        bool operator()(const T& lhs, const T& rhs) const
        {
            return (lhs > rhs);
        }
    };
    然后在实例化set或multiset时指定该谓词，如下所示:
    multiset<int, sortDescending<int>> msetInts;
4) 注意下面的实例化方式：使用一个set来实例化另一个set，使用set的特定范围内的元素来实例化multiset。这里
也可以使用vector、list或其他任何STL容器类，只要它能通过cbegin()和cend()返回描述边界的迭代器。
    set<int> setInt；
    set<int> setInt2(setInt)
    multiset<int> setInt1(setInt.cbegin(), setInt.cend())
5) 从C++11起，STL提供的unordered_set/unordered_multiset是基于散列的集合(使用时需要包含头文
件<unordered_set>)。即使用散列函数来计算排序索引。将元素插入散列集合时，首先使用散列函数计算出一个唯一的索引，再根据该索引决定将元素放到哪个桶(bucker)中。
使用方法与set/multiset差不多，然后unordered_set/unordered_multiset有一个重要特种是：有一个负责确定排列
顺序的散列函数：
    unordered_set<int>::hasher HFn = usetInt.hash_function();
6) 对于对象存储在set、multiset等容器中的类，别忘了在其中实现运算符<和==。前者将成为排序谓词，而后者将用于
set::find等函数。
*/
template <typename T>
void DispalyUnorderedset(const T& cont)
{
    for (auto element = cont.cbegin(); element != cont.cend(); ++element)
        cout << *element << " ";
    cout << endl;
    cout << "Number of elements, size() = " << cont.size() << endl;
    cout << "Bucked count = " << cont.bucket_count() << endl;
    cout << "Max load factor = " << cont.max_load_factor() << endl;
    cout << "Load factor = " << cont.load_factor() << endl;
}

void stl_test::stl_set_multiset_unorderedset_unorderedmultiset_test()
{
    multiset<int> msetInts {2, 3, 5, 5, 9, 4, 5, 1};
    for (auto element = msetInts.cbegin(); element != msetInts.cend(); ++element)
        cout << *element << endl;
    /*查找*/
    auto elementFound = msetInts.find(5);
    if (elementFound != msetInts.cend())
        cout << "Element " << *elementFound << " Found!" << endl;
    else
        cout << "Not Found!" << endl;

    /*基于散列的set*/
    unordered_set<int> usetInt{1, 3, 2017, 300, -1, 989, -300, 9};
    DispalyUnorderedset(usetInt);
    usetInt.insert(999);
    DispalyUnorderedset(usetInt);
}