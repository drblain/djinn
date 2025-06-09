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
    std::thread* thread_;

public:
    Thread();

    virtual ~Thread();

    void create();

    virtual bool stopped() = 0;

    virtual void main() = 0;

    void join();
};

class ThreadWorker : public Thread
{
private:
    ThreadPool* parent_;

public:
    ThreadWorker(ThreadPool* parent);

    bool stopped();

    void main();
};

class ThreadPool
{
private:
    friend class ThreadWorker;

    typedef std::vector<ThreadWorker*> WorkerVec;

    static ThreadPool* the_pool_;
    SignalGate work_gate_;
    std::queue<ThreadWork*> work_queue_;
    Mutex thread_mut_;
    WorkerVec threads_;
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