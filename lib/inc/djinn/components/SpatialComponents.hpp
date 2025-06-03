#pragma once

#include <array>

#include "djinn/Component.hpp"
#include "djinn/components/Mixins.hpp"

namespace djinn
{

struct Scale : public DimensionalMixin<Scale>, public Component
{
    using DimensionalMixin<Scale>::DimensionalMixin;

    Scale(double s):
        DimensionalMixin(s, s, s)
    {}
};

struct Position : public DimensionalMixin<Position>, public Component
{
    using DimensionalMixin<Position>::DimensionalMixin;
};

inline Position operator*(Position lhs, const Scale& rhs)
{
    lhs.x_ *= rhs.x_;
    lhs.y_ *= rhs.y_;
    lhs.z_ *= rhs.z_;
    return lhs;
}
inline Position operator*(const Scale& lhs, Position rhs)
{
    return rhs * lhs;
}

}