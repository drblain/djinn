#include <chrono>
#include <iostream>
#include <thread>

#include "djinn/Time.hpp"

int main(void)
{
    djinn::TimeStamp before;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    djinn::TimeStamp after;

    djinn::TimeDuration duration = after - before;

    std::cout << "Before time: " << before.s_ << " After time: " << after.s_ << " Duration: " << duration.s_ << "\n";

    return 0;
}