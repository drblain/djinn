#pragma once

namespace djinn
{

struct TimeDuration
{
    double s_;

    TimeDuration(const TimeDuration&) = default;
    TimeDuration& operator=(const TimeDuration&) = default;
};

struct TimeStamp
{
    double sdelta_;

    TimeStamp(const TimeStamp&) = default;
    TimeStamp& operator=(const TimeStamp&) = default;

    void setNow();

    static TimeStamp now();
};

inline TimeDuration operator+(const TimeDuration& lhs, const TimeDuration& rhs)
{
    return TimeDuration{lhs.s_ + rhs.s_};
}

inline TimeStamp operator+(const TimeStamp& lhs, const TimeDuration& rhs)
{
    return TimeStamp{lhs.sdelta_ + rhs.s_};
}

inline TimeDuration operator-(const TimeStamp& lhs, const TimeStamp& rhs)
{
    return lhs.sdelta_ > rhs.sdelta_ ?
        TimeDuration{lhs.sdelta_ - rhs.sdelta_} :
        TimeDuration{0};
}

inline TimeStamp operator-(const TimeStamp& lhs, const TimeDuration& rhs)
{
    return lhs.sdelta_ > rhs.s_ ?
        TimeStamp{lhs.sdelta_ - rhs.s_} :
        TimeStamp{0};
}

}