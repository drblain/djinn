#pragma once

#include <memory>
#include <queue>
#include <vector>

#include "djinn/sync/Mutex.hpp"

namespace djinn
{

class ThreadPool;

class ThreadWork
{
public:
    virtual void operator()() = 0;
};

class Thread
{
private:
    ThreadPool* parent_pool_;

    void finish(); // return self to available_threads_
public:
    void work(std::unique_ptr<ThreadWork> work);
};

class ThreadPool
{
private:
    std::queue<std::unique_ptr<ThreadWork>> work_queue_;
    std::vector<std::unique_ptr<Thread>> threads_;
    std::vector<Thread*> available_threads_;

    static Mutex thread_mut_;

    ThreadPool();

public:
    ~ThreadPool();

    static ThreadPool* CreateThreadPool();
    static ThreadPool* CreateThreadPool(size_t num_threads);

    static void queueWork(std::unique_ptr<ThreadWork> work);
};

}