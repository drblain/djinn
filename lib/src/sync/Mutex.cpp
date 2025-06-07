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

void Mutex::wait()
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

void Mutex::signal()
{
    mut_.lock();
    is_locked_ = false;
    cv_.notify_one();
    mut_.unlock();
}

SignalGate::SignalGate():
    mut_(),
    cv_(),
    signaled_(false)
{

}

void SignalGate::waitForSignal()
{
    mut_.lock();
    while (!signaled_)
    {
        cv_.wait(mut_);
    }
    signaled_ = false;
    mut_.unlock();
}

void SignalGate::signal()
{
    mut_.lock();
    signaled_ = true;
    mut_.unlock();
    cv_.notify_one();
}

ScopedLock::ScopedLock():
    mut_(nullptr)
{

}

ScopedLock::ScopedLock(Mutex& mut):
    mut_(&mut)
{
    mut_->wait();
}

ScopedLock::~ScopedLock()
{
    if (mut_) mut_->signal();
}

void ScopedLock::operator()(Mutex& mut)
{
    if (mut_ != &mut)
    {
        if (mut_) mut_->signal();

        mut_ = &mut;
        mut_->wait();
    }
}