#pragma once

#include <queue>
#include <thread>
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
    ThreadPool* parent_;
    bool stopped_;
    std::thread thread_;

public:
    Thread(ThreadPool* parent);

    void runWork();

    void join();
};

class ThreadPool
{
private:
    friend class Thread;

    static ThreadPool* the_pool_;
    SignalGate work_gate_;
    std::queue<ThreadWork*> work_queue_;
    Mutex thread_mut_;
    std::vector<Thread*> threads_;
    bool stopped_;

    ThreadPool(size_t num_threads);

public:
    static ThreadPool* GetThreadPool(size_t num_threads_required = 0);

    // must be called under lock
    void addThread();

    void enqueueWork(ThreadWork* work);

    bool stopped();

    bool hasWork();

    void shutdown();
};

}