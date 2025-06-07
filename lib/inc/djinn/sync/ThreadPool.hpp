#pragma once

#include <functional>
#include <memory>
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
    ThreadWork* work_;
    bool stopped_;
    std::thread thread_;
    SignalGate work_gate_;

public:
    Thread(ThreadPool* parent);

    ~Thread();

    void assignWork(ThreadWork* work);

    void executeWork();

    bool stopIssued() const;

    void stopWork();
};

class ThreadPool
{
private:
    Mutex pool_mut_;
    SignalGate thread_gate_;
    std::queue<ThreadWork*> work_;
    std::vector<Thread*> threads_;
    size_t num_threads_;
    std::thread pool_thread_;

    static ThreadPool* the_pool_;


    ThreadPool(size_t num_threads);

    void addThread(ScopedLock& lock);

    size_t getNumTotalThreads(ScopedLock& lock);
    size_t getNumAvailThreads(ScopedLock& lock);

    void dispatchWork(ScopedLock& lock, ThreadWork* work);

public:
    static ThreadPool* GetThreadPool(size_t num_threads = 0);
    static void sEnqueueWork(ThreadWork* work);

    void monitorWork();

    void enqueueWork(ThreadWork* work);

    void returnToPool(Thread* thread);
};

}