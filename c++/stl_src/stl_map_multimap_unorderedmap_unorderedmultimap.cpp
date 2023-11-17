#include "stl.h"
#include <map>
#include <unordered_map>
#include <iostream>

using namespace std;

/*
1) map与multimap的区别在于后者能够存储重复的键，而前者只能存储唯一的键。要使用map或multimap需要包含
头文件<map>。在实例化map/multimap时，需要指定键和值的类型和可选的谓词(它帮助map/multimap类对插入的
元素进行排序)，比如对于multimap，其实例化的语法格式如下：
    multimap<keytype, valuetype, Predicate>> mmapObj;
    其中第三个参数是可选的，如果省略将把std::less<>用作排序标准。
2) 比如可提供一个谓词：一个实现了operator()的类或结构。
template<typename keyType>
class ReverseSort
{
public:
    bool operator()(const keyType& key1, const keyType& key2)
    {
        return (key1 > key2);
    }
};
3) 从C++11开始，STL支持散列映射,即unordered_map/unordered_multimap类。
4) 散列表将键-值对存储在桶(bucket)中，每个桶都有索引，指出了它在散列表中的相对位置(类似于数组)。这种索引
是使用散列函数根据键值计算得到的：Index = HashFunction(key, TableSize);
使用find()根据键查找元素时，将使用HashFunction()计算元素的位置，并返回该位置的值，就像数组返回其存储的元素
那样。如果HashFunction()不佳，将导致多个元素的索引相同，进而存储在同一个桶中，即桶变成了元素列表，这种情形
称为冲突(collision),将降低查找速度，使查找时间不再是固定的。
5) 与map/multimap一样，可以对unordered_map/unordered_multimap执行实例化、插入和查找操作。然而一个重要的
特点是，后者包含一个散列函数，用于计算排列顺序：
    unordered_map<int, string>::hasher hFn = umapIntStr.hash_function();
    要获悉键对应的索引，可调用该散列函数，并将键传递给它：
    size_t hashingVal = hFn(1000);
6) 鉴于unordered_map将键-值存储在桶中，在元素数达到或接近桶数时，它将自动负载均衡：
    cout << "Load factor: " << umapIntStr.load_factor() << endl;
    cout << "Max Load factor: " << umapIntStr.max_load_factor() << endl;
    cout << "Max bucker cout: " << umapIntStr.max_bucket_count() << endl;
    其中load_factor()指出了unordered_map桶的填满程度。因插入元素导致load_factor()超过max_load_factor()时，
    unordered_map将重新组织以增加桶数，并重建散列表。
*/

template<typename T>
void DisplayContents(const T& cont)
{
    for (auto element = cont.cbegin(); element != cont.cend(); ++element)
        cout << element->first << "->" << element->second << endl;
    cout << endl;
}

typedef map<int, string> MAP_INT_STRING;
typedef multimap<int, string> MMAP_INT_STRING;

void stl_test::stl_map_multimap_unorderedmap_unorderedmultimap_test()
{
    MAP_INT_STRING mapIntStr;
    mapIntStr.insert(MAP_INT_STRING::value_type(3, "Three"));
    mapIntStr.insert(make_pair(-1, "Minus One"));
    mapIntStr.insert(pair<int, string>(1000, "One Thousand"));
    mapIntStr[1000000] = "One Million";
    cout << "The map contains " << mapIntStr.size();
    cout << " key-value pairs. There are: " << endl;
    DisplayContents(mapIntStr);

    MMAP_INT_STRING mmapIntStr(mapIntStr.cbegin(), mapIntStr.cend());
    DisplayContents(mmapIntStr);
}