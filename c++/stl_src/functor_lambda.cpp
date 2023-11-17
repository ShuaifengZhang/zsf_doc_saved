#include "stl.h"
#include <algorithm>
#include <list>
#include <vector>
#include <iostream>

using namespace std;
/*
1) lambda表达式(也叫lambda函数)是一种定义匿名函数对象的简洁方式，这是C++11新增的。可将lambda表达式视为
包含公有opertor()的匿名结构或类，从这种意义上来说，lmabda属于函数对象。先看下面：
    template <typename elementType>
    struct DisplayElement
    {
        void operator()(const elementType& element) const
        {
            cout << element << ' ';
        }
    }
    上述这个函数对象使用cout将element显示到屏幕上，通常用于for_each()等算法中：
    for_each(numsInVec.cbegin(), numsInVec.cend(), DisplayElement<int>());
    如果使用lambda表达式，可将上述代码(包括函数对象的定义)简化为下述三行(可以发现使用lambda可使代码更简洁)：
    for_each(numsInVec.cbegin(), numsInvec.cend(), [](const int& element) {cout << element << ' ';});

    编译器见到上述Lambda表达式时，自动将其展开为类似于结构DisplayElement<int>的表示：
    struct NoName
    {
        void operator() (const int& element) const
        {
            cout << element << ' ';
        }
    };
2) lambda表达式的定义必须以[]打头,并且接受多个状态变量，[]为捕获列表，可在其内指定这些状态变量，并用逗号分隔。
   在其后面是一个参数列表，该参数列表与不使用lambda表达式时提供给operator()的参数列表相同：
    [stateVar1, stateVar2](Type1 var1, Type2 var2) {//lambda code here;};
    如果要在lambda表达式中修改这些状态变量，可添加关键字mutable:
    [stateVar1, stateVar2](Type1 var1, Type2 var2) mutable {//lambda code here;};
    这样，便可在lambda表达式中修改捕获列表中指定的变量,但在离开lambda表达式后这些修改将无效。要确保在lambda
    表达式内部对状态变量的修改在其外部也有效，应按引用传递这些状态变量。

    另外如果要向编译器明确地指定返回类型，可使用->,如下所示：
    [stateVar1, stateVar2](Type1 var1, Type2 var2) -> ReturnType {//lambda code here;};

3) 尽量不要使用很长(包含多条语句)的lambda表达式，这种情况应转而使用函数对象，因为每次使用lambda表达式时都要重新
定义它，这无助于提高代码的可重用性。

4) 在lambda表达式中，可使用函数中的局部变量吗？
    答：可使用捕获列表来传递局部变量: [var1, var2,...N](Type& param1, ...) {...expression;}
    要传递所有的局部变量，可使用如下语法：[=](Type& param1,...) {...expression;}
 */
template <typename T>
void DisplayContents(const T& input)
{
    for (auto element = input.cbegin(); element != input.cend(); ++element)
        cout << *element << endl;
}

void stl_test::functor_lambda_test()
{
/*一元函数等价的lambda表达式*/
    list<char> charsInList {'a', 'h', 'z', 'k', 'l'};
    for_each(charsInList.cbegin(), charsInList.cend(), [](auto& element) {cout << element << ' ';});
    cout << endl;

/*一元谓词等价的lambda表达式*/
    vector<int> numsInVec{25, 101, 2017, -50};
    //算法find_if对指定范围内的每个元素调用该一元谓词。如果谓词返回true,find_if将返回一个指向相应元素的迭代器evenNum,指出
    //找到了一个满足条件的元素。
    auto evenNum = find_if(numsInVec.cbegin(), numsInVec.cend(), [](const int& num) {return ((num % 2) == 0);});
    if (evenNum != numsInVec.cend())
        cout << "Even number in collection is: " << *evenNum << endl;
    //上述lambda的除数是2，如果让它更通用，可以让用户指定需要怎么做？使用捕获列表(一系列以状态变量的方式传递的参数[...])!
    int divisor = 0;
    cin >> divisor;
    vector<int>::iterator element;
    //divisor是一个状态变量，可将状态变量传递给lambda表达式。
    element = find_if(numsInVec.begin(), numsInVec.end(), [divisor](int num){return ((num % divisor) == 0);});
    if (element != numsInVec.end())
        cout << "First element in vector divisible by " << divisor << ": " << *element << endl;

/*二元函数等价的lambda表达式*/
    vector<int> vecMultiplicand{0, 1, 2, 3, 4};
    vector<int> vecMultiplier{100, 101, 102, 103, 104};
    vector<int> vecResult;
    vecResult.resize(vecMultiplier.size());

    transform(vecMultiplicand.begin(), vecMultiplicand.end(), vecMultiplier.begin(), vecResult.begin(), [](int a, int b) {return a * b;});
    cout << "The result of the multiplication is: " << endl;
    for (size_t index = 0; index < vecResult.size(); ++index)
        cout << vecResult[index] << ' ';
    cout << endl;

/*二元谓词等价的lambda表达式*/
    vector <string> namesInVec{"jim", "Jack", "Sam", "Anna"};
    sort(namesInVec.begin(), namesInVec.end(), [](const string& str1, const string& str2) -> bool 
        {
            string str1LC, str2LC;
            str1LC.resize(str1.size());
            str2LC.resize(str2.size());
            transform(str1.begin(), str1.end(), str1LC.begin(), ::tolower);
            transform(str2.begin(), str2.end(), str2LC.begin(), ::tolower);

            return (str1LC < str2LC);
        });
    DisplayContents(namesInVec);
}