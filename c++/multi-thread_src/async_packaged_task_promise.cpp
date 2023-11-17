#include "multi-thread.h"
#include <iostream>
#include <future>

/*
std::async是C++11引入的一个函数模板，用于异步执行一个函数，并返回一个std::future对象，表示
异步操作的结果。使用std::async可以方便地进行异步编程，避免了手动创建线程和管理线性
的麻烦。
*/
int func()
{
    int i = 0;
    for (i = 0; i < 1000; ++i)
    {
        i++;
    }
    return i;
}

void multi_thread_test::async_packaged_task_promise_test()
{   /*当把func函数传给async后，这个func()其实就开始在后台线程运行了。并不会阻塞，而是往下走*/
    std::future<int> future_result = std::async(std::launch::async, func); 
    /*再次运行一个func()，此时就有两个func()在运行了。一个是在main()函数所在的主线程运行，一个在后台线程运行，
    用这种方法就不需要手动去创建后台的那个线程了*/
    std::cout << func() << std::endl;       //1000
    std::cout << future_result.get() << std::endl;   //1000
}


/*
//std::packaged_task是一个类模板，用于将一个可调用对象函数对象(函数、lambda等)封装成一个异步操作，并返回一个std::future对象，
//表示异步操作的结果。packaged_task可以方便地将一个函数或可调用对象转换成一个异步操作，供其他线程使用

void multi_thread_test::package_task_future_test()
{   
    
    std::packaged_task<int()> task(func);
    auto future_result = task.get_future();
    std::thread t1(std::move(task));

    std::cout << func() << std::endl;  //主线程中运行

    t1.join();
    std::cout << future_result.get() << std::endl;   //获得后台运行子线程的结果
}
*/

/*
在C++中promis是一个类模板，用于在一个线程中产生一个值，并在另一个线程中获取这个值。promise通常与future和async一起
使用，用于实现异步编程
void func(std::promise<int> &f)
{
    f.set_value(10);
}

int main()
{
    std::promise<int> f;
    auto future_result = f.get_future();

    std::thread t1(func, std::ref(f));
    t1.join();

    cout << future_result.get() << endl;   //10
}

*/