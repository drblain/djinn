#pragma once

#include <functional>
#include <vector>
#include <queue>

#include "djinn/sync/Mutex.hpp"

namespace djinn
{

typedef std::function<void()> ThreadWorkFn;

class Thread
{
private:

public:

};

class ThreadPool
{
private:
    friend class Thread;

    static ThreadPool* the_pool_;
    std::queue<ThreadWorkFn> work_queue_;
    std::vector<Thread*> threads_;

    ThreadPool(size_t num_threads);

public:
    static ThreadPool* GetThreadPool(size_t num_threads_required);

};

}