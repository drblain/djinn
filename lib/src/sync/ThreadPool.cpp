#include "djinn/sync/ThreadPool.hpp"

using namespace djinn;

ThreadPool* ThreadPool::the_pool_ = nullptr;

Thread::Thread(ThreadPool* parent):
    parent_(parent),
    work_(nullptr),
    stopped_(false),
    thread_([this](){ this->executeWork(); })
{

}

Thread::~Thread()
{
    if (thread_.joinable()) thread_.join();
}

void Thread::assignWork(ThreadWork* work)
{
    work_ = work;
    work_gate_.signal();
}

void Thread::executeWork()
{
    while (!stopIssued())
    {
        while (!work_)
        {
            work_gate_.waitForSignal();
        }

        // execute work functor
        (*work_)();

        delete work_;
        work_ = nullptr;
        parent_->returnToPool(this);
    }

    // become joinable
}

bool Thread::stopIssued() const
{
    return stopped_;
}

void Thread::stopWork()
{
    stopped_ = true;
}

ThreadPool::ThreadPool(size_t num_threads):
    pool_mut_(),
    num_threads_(0),
    pool_thread_([this]() { this->monitorWork(); })
{
    ScopedLock lock(pool_mut_);
    for (size_t i = 0; i < num_threads; ++i)
    {
        addThread(lock);
    }
}

void ThreadPool::addThread(ScopedLock& lock)
{
    lock(pool_mut_);
    threads_.push_back(new Thread(this));
    ++num_threads_;
    thread_gate_.signal();
}

size_t ThreadPool::getNumTotalThreads(ScopedLock& lock)
{
    lock(pool_mut_);
    return num_threads_;
}

size_t ThreadPool::getNumAvailThreads(ScopedLock& lock)
{
    lock(pool_mut_);
    return threads_.size();
}

void ThreadPool::dispatchWork(ScopedLock& lock, ThreadWork* work)
{
    lock(pool_mut_);
    Thread* worker = threads_.back();
    threads_.pop_back();

    worker->assignWork(work);
}

ThreadPool* ThreadPool::GetThreadPool(size_t num_threads)
{
    if (the_pool_)
    {
        ScopedLock lock;
        size_t curr_num_threads = the_pool_->getNumTotalThreads(lock);
        if (num_threads > curr_num_threads)
        {
            for (size_t i = 0; i < (num_threads - curr_num_threads); ++i)
            {
                the_pool_->addThread(lock);
            }
        }

        return the_pool_;
    }

    the_pool_ = new ThreadPool(num_threads);
    return the_pool_;
}

void ThreadPool::sEnqueueWork(ThreadWork* work)
{
    ThreadPool* pool = GetThreadPool();
    pool->enqueueWork(work);
}

void ThreadPool::monitorWork()
{
    while (true)
    {
        {
            ScopedLock lock(pool_mut_);
            while ((work_.size() > 0) && (getNumAvailThreads(lock) > 0))
            {
                ThreadWork* work = work_.front();
                work_.pop();
                dispatchWork(lock, work);
            }
        }
        
        thread_gate_.waitForSignal();
    }
}

void ThreadPool::enqueueWork(ThreadWork* work)
{
    ScopedLock lock;
    if (getNumAvailThreads(lock) == 0)
    {
        work_.push(work);
        return;
    }

    dispatchWork(lock, work);
}

void ThreadPool::returnToPool(Thread* thread)
{
    ScopedLock lock(pool_mut_);
    threads_.push_back(thread);
    thread_gate_.signal();
}
