#pragma once

namespace djinn
{

template<class Derived>
class DimensionalMixin
{
public:
    double x_;
    double y_;
    double z_;

    DimensionalMixin():
        x_(0.0), y_(0.0), z_(0.0)
    {}

    DimensionalMixin(double x, double y, double z):
        x_(x), y_(y), z_(z)
    {}

    Derived& operator+=(const Derived& other)
    {
        x_ += other.x_;
        y_ += other.y_;
        z_ += other.z_;
        return static_cast<Derived&>(*this);
    }

    Derived& operator-=(const Derived& other)
    {
        x_ -= other.x_;
        y_ -= other.y_;
        z_ -= other.z_;
        return static_cast<Derived&>(*this);
    }

};

}