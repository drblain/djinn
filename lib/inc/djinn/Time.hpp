#pragma once

#include <chrono>

namespace djinn
{

using SystemClock = std::chrono::steady_clock;
using SystemTimePoint = SystemClock::time_point;

struct TimeDuration
{
    double s_;

    TimeDuration(const TimeDuration&) = default;
    TimeDuration& operator=(const TimeDuration&) = default;
};

struct TimeStamp
{
    static SystemTimePoint start_time_;

    double s_;

    TimeStamp();
    TimeStamp(double s);
    TimeStamp(const TimeStamp&) = default;
    TimeStamp& operator=(const TimeStamp&) = default;

    void setNow();

    static TimeStamp now();

    // Dummy struct used to set the initial time for the binary
    struct InitialTimeStamp
    {
        InitialTimeStamp()
        {
            TimeStamp::start_time_ = SystemClock::now();
        }
    };
};

inline TimeDuration operator+(const TimeDuration& lhs, const TimeDuration& rhs)
{
    return TimeDuration{lhs.s_ + rhs.s_};
}

inline TimeStamp operator+(TimeStamp lhs, const TimeDuration& rhs)
{
    lhs.s_ += rhs.s_;
    return lhs;
}
inline TimeStamp operator+(const TimeDuration& lhs, TimeStamp rhs)
{
    return rhs + lhs;
}


inline TimeDuration operator-(const TimeStamp& lhs, const TimeStamp& rhs)
{
    return lhs.s_ > rhs.s_ ?
        TimeDuration{lhs.s_ - rhs.s_} :
        TimeDuration{0};
}

inline TimeStamp operator-(const TimeStamp& lhs, const TimeDuration& rhs)
{
    return lhs.s_ > rhs.s_ ?
        TimeStamp(lhs.s_ - rhs.s_) :
        TimeStamp(0);
}
inline TimeStamp operator-(const TimeDuration& lhs, const TimeStamp& rhs)
{
    return rhs - lhs;
}

}