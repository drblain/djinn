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

void Mutex::acquire()
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

void Mutex::release()
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

void SignalGate::lock()
{
    mut_.lock();
}

void SignalGate::wait()
{
    while (!signaled_)
    {
        cv_.wait(mut_);
    }
    signaled_ = false;
}

void SignalGate::unlock()
{
    mut_.unlock();
}

void SignalGate::lockAndWait()
{
    lock();
    wait();
    unlock();
}

void SignalGate::signal()
{
    mut_.lock();
    signaled_ = true;
    mut_.unlock();
    cv_.notify_one();
}

void SignalGate::broadcast()
{
    mut_.lock();
    signaled_ = true;
    mut_.unlock();
    cv_.notify_all();
}

ScopedLock::ScopedLock(Mutex& mut):
    mut_(&mut)
{
    mut_->acquire();
}

ScopedLock::~ScopedLock()
{
    if (mut_) mut_->release();
}

ScopedGate::ScopedGate(SignalGate& gate):
    gate_(&gate)
{
    gate_->lock();
}

void ScopedGate::wait()
{
    gate_->wait();
}

ScopedGate::~ScopedGate()
{
    gate_->unlock();
}