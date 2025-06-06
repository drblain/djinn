#include "djinn/sync/Mutex.hpp"

using namespace djinn;

Mutex::Mutex():
    mut_(),
    cv_(),
    is_locked_(false)
{

}

Mutex::~Mutex()
{

}

void Mutex::Wait()
{
    mut_.lock();
    while(is_locked_)
    {
        mut_.unlock();
        cv_.wait(mut_);
        mut_.lock();
    }
    is_locked_ = true;
    mut_.unlock();
}

void Mutex::Signal()
{
    mut_.lock();
    is_locked_ = false;
    cv_.notify_one();
    mut_.unlock();
}

ScopedLock::ScopedLock():
    mut_(nullptr)
{

}

ScopedLock::ScopedLock(Mutex& mut):
    mut_(&mut)
{
    mut_->Wait();
}

ScopedLock::~ScopedLock()
{
    if (mut_) mut_->Signal();
}

void ScopedLock::lock(Mutex& mut)
{
    if (mut_) mut_->Signal();

    mut_ = &mut;
    mut_->Wait();
}