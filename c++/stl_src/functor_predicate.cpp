#include "stl.h"
#include <algorithm>
#include <vector>
#include<iostream>
#include <string>

using namespace std;


/*
可将谓词理解成一种特殊的函数对象(谓词总是返回布尔值)。而C++11开始引入的lambda是匿名函数对象。
1) 从概念上说函数对象(functor)是用作函数的对象，但是从实现上说函数对象是实现了operator()的类对象。虽
然函数和函数指针也可归纳为函数对象，但实现了operator()的类对象才能保存状态(即类的成员属性的值)，才能用
于STL算法。C++程序员常将用于STL算法的函数对象分为下面两类：
    a. 一元函数：接受一个参数的函数，如果一元函数返回一个布尔值，则该函数称为一元谓词。
    b. 二元函数：接受两个参数的函数，如果二元函数返回一个布尔值，则该函数称为二元谓词。
2) 返回布尔类型的函数对象通常用于需要进行判断的算法，如find()、sort()。组合两个函数对象的函数对象称为
自适应函数对象。
3) 一元函数，比如：
    template<typename elementType>
    void DisplayElement(const elementType& element)
    {
        cout << element << ' ';
    }
该函数接受一个类型为模板化类型elementType的参数，该函数也可以采用另一种表现形式，即其实现包含在class
或struct的operator()中：
    template<typename elementType>
    struct Displayelement
    {
        void operator() (const elementType& element) const
        {
            cout << element << ' ';
        }
    };
以上这两种实现都可以用于STL算法for_each()
*/

template<typename elementType>  //一元函数
struct DisplayelementKeepCount
{
    int count;
    DisplayelementKeepCount(): count(0) {}

    void operator() (const elementType& element)
    {
        ++count;
        cout << element << ' ';
    }
};

template<typename numberType>   //一元谓词
struct IsMultiple
{
    numberType Divisor;
    IsMultiple(const numberType& divisor)
    {
        Divisor = divisor;
    }
    bool operator()(const numberType& element) const
    {
        return ((element % Divisor) == 0);
    }
};

template <typename elementType> //二元函数
class Multiply
{
public:
    elementType operator()(const elementType& elem1, const elementType& elem2)
    {
        return (elem1 * elem2);
    }
};

class CompareStringNoCase   //二元谓词
{
public:
    bool operator()(const string& str1, const string& str2) const
    {
        string str1LowerCase, str2LowerCase;
        str1LowerCase.resize(str1.size());
        transform(str1.begin(), str1.end(), str1LowerCase.begin(), ::tolower);
        str2LowerCase.resize(str2.size());
        transform(str2.begin(), str2.end(), str2LowerCase.begin(), ::tolower);

        return (str1LowerCase < str2LowerCase);
    }
};
template <typename T>
void DisplayContents(const T& conatiner)
{
    for (auto element = conatiner.cbegin(); element != conatiner.cend(); ++ element)
        cout << *element << endl;
}

void stl_test::functor_predicate_test()
{
/*一元函数*/
    vector<int> numsInVec{22, 2017, -1, 999, 43, 901};
    DisplayelementKeepCount<int> result;
    /*for_each的第三个参数是 要对指定范围内的每个元素调用的函数*/
    result = for_each(numsInVec.begin(), numsInVec.end(), DisplayelementKeepCount<int>());
    cout << endl << "Functor invoked " << result.count << " times" << endl;
/*一元谓词：返回布尔值的一维函数，这种函数可供STL算法用于判断。一元谓词被大量用于STL算法中，
例如partition()使用一元谓词来划分范围，算法stable_partition()也使用一元谓词来划分范围，但
保持元素的相对顺序不变。诸如find_if()等查找函数以及remove_if()等删除元素的函数也使用一元谓词，
其中remove_if()删除指定范围内满足谓词条件的元素。*/
    vector<int> numsInVec1{25, 26, 27, 28, 29, 30, 31};
    int divisor = 4;
    auto element = find_if(numsInVec1.begin(), numsInVec1.end(), IsMultiple<int>(divisor));
    if (element != numsInVec1.end())
    {
        cout << "First element in vector divisible by " << divisor << " : " << *element << endl;
    }
/*二元函数：可用于对两个操作数执行运算，如加减乘除等*/
    vector<int> multiplicands{0, 1, 2, 3, 4};
    vector<int> multipliers{100, 101, 102, 103, 104};
    vector<int> vecResult(5);
    transform(multiplicands.begin(), multiplicands.end(), multipliers.begin(), vecResult.begin(), Multiply<int>());
    cout << "The result of the multiplication is: " << endl;
    for(size_t index = 0; index < 5; ++index)
        cout << vecResult[index] << ' ';
        cout << endl;
/*二元谓词: 接受两个参数并返回一个布尔值的函数。这种函数用于注入std::sort()等STL算法中。*/
    vector<string> names;
    names.push_back("jim");
    names.push_back("Jack");
    names.push_back("Sam");
    names.push_back("Anna");
    cout << "Names after sorting using default std::less<>: "<< endl;
    sort(names.begin(), names.end());
    DisplayContents(names);
    cout << "Sorting using predicate that ignores case: " << endl;
    sort(names.begin(), names.end(), CompareStringNoCase());
    DisplayContents(names);

}