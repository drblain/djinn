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

    void acquire();

    void release();
};

class SignalGate
{
private:
    std::mutex mut_;
    std::condition_variable_any cv_;
    bool signaled_;

public:
    SignalGate();

    void lock();

    // caller has already called lock
    void wait();

    void unlock();

    void lockAndWait();

    void signal();

    void broadcast();
};

class ScopedLock
{
private:
    Mutex* mut_;

    ScopedLock() = delete;
public:
    ScopedLock(Mutex& mut);
    ~ScopedLock();
};

class ScopedGate
{
private:
    SignalGate* gate_;
    bool gate_locked_;

    ScopedGate() = delete;
public:
    ScopedGate(SignalGate& gate);
    void wait();
    ~ScopedGate();
};

}