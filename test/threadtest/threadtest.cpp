#include <iostream>
#include <random>
#include <string>

#include "djinn/sync/Thread.hpp"

class PrintWork : public djinn::ThreadWork
{
private:
    std::string str_;
    int t_;

public:
    PrintWork(const std::string& str, int t):
        str_(str), t_(t)
    {

    }

    void operator()()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(t_));

        std::cout << "Work " << this << " on thread " << std::this_thread::get_id() << " printing payload " << str_ << std::endl;
    }
};

int main(int argc, char* argv[])
{
    
    djinn::ThreadPool * pool = djinn::ThreadPool::GetThreadPool(4);
    int sum = 0;
    for (int i = 0; i < 20; ++i)
    {
        pool->enqueueWork(new PrintWork(std::to_string(i), std::rand() % 100));
        sum += i;
    }

    // sometimes hangs?
    pool->shutdown();
    
    return 0;
}