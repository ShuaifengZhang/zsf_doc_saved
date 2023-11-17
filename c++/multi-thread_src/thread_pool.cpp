#include "multi-thread.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>

/*
为什么要使用线程池，因为线程的开辟和销毁都是一个非常消耗资源和耗时间的一件事，所以提前开辟好一堆线程专门等着
你任务进来我去取任务，这样可以提高效率。
符合生产者与消费者模型：提前维护一个线程数组和一个任务队列，线程数组不断派线程去队列去取任务去完成，而用户
不停地往任务队列里加任务。

如何管理线程去去任务？
*/

class ThreadPool {
public:
    ThreadPool(int numThreads): stop(false) {
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back([this] {
                while (1) {
                    std::unique_lock<std::mutex> lock(mtx);
                    condition.wait(lock, [this] {return !tasks.empty() || stop;});

                    if (stop && tasks.empty()) {
                        return;        
                    }

                    std::function<void()> task(std::move(tasks.front()));
                    tasks.pop();
                    lock.unlock();
                    task();      
                }
            });            
        }
    }

    template<class F, class... Args>
    void enqueue(F &&f, Args&&... args) {
        std::function<void()>task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        {   
            std::unique_lock<std::mutex> lock(mtx);
            tasks.emplace(move(task));
        }//加括号指定锁的作用域范围

        condition.notify_one();          
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(mtx);
            stop = true;
        }

        condition.notify_all();
        for (auto& t : threads) {
            t.join();
        }
    }
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;

    std::mutex mtx;
    std::condition_variable condition;
    bool stop;
};

void multi_thread_test::thread_pool_test()
{
    ThreadPool pool(4);

    for(int i = 0; i < 10; i++) {
        pool.enqueue([i] {
            std::cout << "task : " << i << " is runing" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "task : " << i << " is done" << std::endl;
        });
    }
}