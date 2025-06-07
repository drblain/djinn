#include "djinn/sync/ThreadPool.hpp"

using namespace djinn;

ThreadPool* ThreadPool::the_pool_ = nullptr;

Thread::Thread(ThreadPool* parent):
    parent_(parent),
    thread_([this]() { this->runWork(); })
{

}

void Thread::runWork()
{
    while (!parent_->stopped() || parent_->hasWork())
    {
        ThreadWork* work = nullptr;

        {
            ScopedGate gate(parent_->work_gate_);
            while (!parent_->hasWork() && !parent_->stopped())
            {
                gate.wait();
            }

            if (parent_->stopped() && !parent_->hasWork()) return;

            work = parent_->work_queue_.front();
            parent_->work_queue_.pop();
        }

        (*work)();
        delete work;
    }

    // become joinable
}

void Thread::join()
{
    thread_.join();
}

ThreadPool::ThreadPool(size_t num_threads):
    stopped_(false)
{
    ScopedLock lock(thread_mut_);
    for (size_t i = 0; i < num_threads; ++i)
    {
        addThread();
    }
}

ThreadPool* ThreadPool::GetThreadPool(size_t num_threads_required)
{
    if (the_pool_)
    {
        ScopedLock lock(the_pool_->thread_mut_);
        if (num_threads_required > the_pool_->threads_.size())
        {
            for (size_t i = 0; i < (num_threads_required - the_pool_->threads_.size()); ++i)
            {
                the_pool_->addThread();
            }
        }
    }
    else
    {
        the_pool_ = new ThreadPool(num_threads_required);
    }

    return the_pool_;
}

void ThreadPool::addThread()
{
    threads_.push_back(new Thread(this));
}

void ThreadPool::enqueueWork(ThreadWork* work)
{
    {
        ScopedLock lock(thread_mut_);
        work_queue_.push(work);
    }
    work_gate_.signal();
}

bool ThreadPool::stopped()
{
    return stopped_;
}

bool ThreadPool::hasWork()
{
    return !work_queue_.empty();
}

void ThreadPool::shutdown()
{
    {
        ScopedLock lock(thread_mut_);
        stopped_ = true;
    }

    work_gate_.broadcast();

    for (std::vector<Thread*>::iterator thread = threads_.begin();
         thread != threads_.end(); ++ thread)
    {
        (*thread)->join();
    }
}