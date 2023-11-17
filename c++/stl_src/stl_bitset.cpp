#include "stl.h"
#include <bitset>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
/*
bitset不是STL容器类，因为它不能动态调整长度。这也是bitset的缺点之一，仅当在编译阶段直到序列将
存储多少位才能使用bitset。为了克服这种缺点，STL向程序员提供了vector<bool>类(在有些STL的实现中
为bit_vector)。
*/

void stl_test::stl_bitset_test()
{
    /*需要通过一个模板参数指定位序列包含的位数。位数在编译阶段确定，而不是动态的。指定后就不能插入
    更多的位了，不像vector等那样调整在编译阶段指定的长度。*/
    bitset<4> fourBits;    //4 bits initialized to 0000
    bitset<5> fiveBits("10101");    //5 bits 10101
    bitset<6> sixBits(0b100001);    //C++14 binary literal
    bitset<8> eightBits(255);   //8 bit initialized to long int 255。(11111111)
    bitset<8> eightBitsCopy(eightBits);

    /*bitset的运算符*/
    /*bitset的成员方法*/

    /*vector<bool>*/
    vector<bool> boolFlag(8, true);
    boolFlag.push_back(true);
    boolFlag.flip();    //类似于bit_set<>::flip()
}