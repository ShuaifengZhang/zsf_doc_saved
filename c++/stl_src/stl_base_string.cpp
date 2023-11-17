#include "stl.h"
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
/*
std::string和std::wstring实际上是同一个模板类(std::basic_string<T>)的具体化，即分别针对char和wchar_t的
具体化(如果编写的程序需要更好地支持非拉丁字母，比如中文和日文，应该使用std::wstring)：
    template<class _Elem, class _Traits, class _Ax>
    class basic_string
1) 在该类模板中，最重要的是第一个参数，它指定了basic_string对象将存储的数据类型。因此std::string
是使用_Elem=char具体化模板basic_string的结果，而wchar是使用_Elem=wchar_t具体化模板basic_string
的结果。换句话说:
    STL string类的定义如下：
        typedef basic_string<char, char_traits<char>, allocator<char>> string;
    而STL wstring类的定义如下：
        typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t>> wstring;
2) 相比C风格字符串使用string和wstring这两个容器的优点是：程序员不用再专门负责字符串的内存管理、比较等操作。
*/

void stl_test::stl_base_string_test()
{
   const char* my_string1 = "Hello C++";

    /*复制STL string*/
    string my_string2(my_string1);  //等价于string my_string2 = my_string1;或string my_string2("Hello C++");
    cout << "my_string2 = " << my_string2 << endl;
    string my_string3(my_string1, 5);   //部分拷贝
    cout << "my_string3 = " << my_string3 << endl;
    string my_string4(10, 'a'); //初始化为包含多个相同的字符
    cout << "my_string4 = " << my_string4 << endl;

    /*访问stl::string的字符内容，可用迭代器，也可用类似于数组的下标[]。当然要获得string对象的C风格表示，可使用成员
    函数c_string()*/
    int charOffset = 0;
    for (auto charlocator = my_string2.cbegin(); charlocator != my_string2.cend(); ++charlocator)
        cout << "my_string1[" << charOffset++ << "] is: " << *charlocator << endl;

    /*拼接字符串，既可以使用运算符+=，也可以使用成员函数append()*/
    my_string4.append(my_string3);  //my_string4 += my_string3;
    cout << "my_string4 = " << my_string4 << endl;

    /*在string中查找字符或子字符串*/
    size_t charPos = my_string4.find("He", 0);
    if (charPos != string::npos)    //string::npos值为1
        cout << "First instance of \"He\" was found at position " << charPos << endl;
    else
        cout << "Substring not found." << endl;
    
    /*截短STL string*/
    string my_string5 = "Hello C++, I love you";
    cout << "my_string5 = " << my_string5.erase(9, 100) << endl;   //删除给定位置和数量的字符串
    string::iterator iChar = find(my_string5.begin(), my_string5.end(), '+');
    if (iChar != my_string5.end())
       my_string5.erase(iChar); //指定字符的迭代器来删除字符
    cout << "my_string5 = " << my_string5 << endl;
    my_string5.erase(my_string5.begin(), my_string5.begin() + 5);   //使用两个迭代器指定删除范围
    cout << "my_string5 = " << my_string5 << endl;

    /*反转*/
    reverse(my_string5.begin(), my_string5.end());
    cout << "my_string5 = " << my_string5 << endl;

    /*字符串的大小写转换，transform()算法会对集合中的每个元素执行一个用户指定的函数。在这里集合就是string对象本身*/
    string my_string6 = "HHHHaaaa";
    //transform(my_string6.begin(), my_string6.end(), my_string6.begin(), ::toupper); //指定toupper函数
    transform(my_string6.begin(), my_string6.end(), my_string6.begin(), ::tolower); //指定toupper函数
    cout << "my_string6 = " << my_string6 << endl;

    /*c++14标准库支持将用双引号括起来的字符串转换为std::basic_string<t>的operator""s */
    string my_string7("Hello \0C++14"s);    //若没有后面的s将仅输出"Hello "
    cout << "my_string7 = " << my_string7 << endl;

}