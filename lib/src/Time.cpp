#include <chrono>

#include "djinn/Time.hpp"

using namespace djinn;

SystemTimePoint TimeStamp::start_time_;

namespace
{
// Dummy struct used to set the initial time for the binary
struct InitialTimeStamp
{
    InitialTimeStamp()
    {
        TimeStamp::start_time_ = SystemClock::now();
    }
};

InitialTimeStamp initial_time_stamp;

} // namespace

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