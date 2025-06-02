#include <chrono>

#include "djinn/Time.hpp"

using namespace djinn;

SystemTimePoint TimeStamp::start_time_;

TimeStamp::InitialTimeStamp initial_time_stamp;

TimeStamp::TimeStamp()
{
    setNow();
}

TimeStamp::TimeStamp(double s):
    s_(s)
{}

void TimeStamp::setNow()
{
    *this = now();
}

TimeStamp TimeStamp::now()
{
    return TimeStamp{
        std::chrono::duration<double>(SystemClock::now() - start_time_).count()};
}