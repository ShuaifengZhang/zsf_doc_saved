#include "stl.h"
#include <stack>
#include <queue>
#include <iostream>
#include <vector>
#include <list>
#include <functional> //使用其中的greater()

using namespace std;

/*
1) STL提供了一些这样的容器，即使用其他容器模拟栈和队列的行为。这种内部使用一种容器但呈现另一种容器的行为特征的
容器称为自适应容器(adaptive container)。
2) stack、queue、priority是3种自适应容器，这些容器使用顺序容器并对其进行改造，以满足内部数据存储需求，再通过
成员函数呈现出独特的行为特性。
3) STL算法使用迭代器，然而由于自适应容器没有提供标记范围两端的迭代器，因为无法将STL算法用于这些容器。
4) 要使用priority_queue也必须包含头文件<queue>，priority和queue的不同在于，包含最大值(或二元谓词认为是最大值)
的元素位于队首。

*/

void stl_test::stl_stack_queue_priorityqueue_test()
{
    stack<int> numsInStack;
    stack<double> dblsInStack;
    /*stack使用的默认底层容器是deque,即默认在内部使用deque来存储数据，但可指定使用vector或list来存储数据*/
    stack<double, vector<double>> doublesStackedInVec;
    stack<int> numsInStackCopy(numsInStack);

    queue<int> numsInQ;
    queue<double> dblsInQ;
    /*queue默认使用deque作为底层容器来管理内容，这里显式指定使用list。*/
    queue<double, list<double>> dblsInQInList;
    queue<int> copyQ(numsInQ);

    priority_queue<int> numsInPrioQ;
    priority_queue<double> dblsInProQ;
    priority_queue<int> copyPQ(numsInPrioQ);
    /*priority_queue默认使用vector作为底层容器来管理内存。默认使用std::less提供的比较标准；因此如果不显式
    指定的话，该队列就会将包含的值最大的元素放在队首(优先级队列将元素自动降序排列)，然而这里显式指定谓词为
    std::greater，该谓词将导致最小的元素位于队首。*/
    priority_queue<int, deque<int>, greater<int>> numsInDescendingQ;
    numsInDescendingQ.push(10);
    numsInDescendingQ.push(5);
    numsInDescendingQ.push(-1);
    numsInDescendingQ.push(20);
    while (!numsInDescendingQ.empty())
    {
        cout << "Delete topmost element " << numsInDescendingQ.top() << endl;
        numsInDescendingQ.pop();
    }
}