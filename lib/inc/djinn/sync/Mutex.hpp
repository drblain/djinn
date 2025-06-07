#pragma once

#include <condition_variable>
#include <mutex>

namespace djinn
{

class Mutex
{
private:
    std::mutex mut_;
    std::condition_variable_any cv_;
    bool is_locked_;

public:
    Mutex();
    ~Mutex();

    void wait();

    void signal();
};

class SignalGate
{
private:
    std::mutex mut_;
    std::condition_variable_any cv_;
    bool signaled_;

public:
    SignalGate();

    void waitForSignal();

    void signal();
};

class ScopedLock
{
private:
    Mutex* mut_;

public:
    ScopedLock();
    ScopedLock(Mutex& mut);
    ~ScopedLock();

    void operator()(Mutex& mut);
};

}