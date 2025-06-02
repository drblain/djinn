#pragma once

#include <array>

#include "djinn/Component.hpp"
#include "djinn/Time.hpp"
#include "djinn/components/Mixins.hpp"
#include "djinn/components/SpatialComponents.hpp"

namespace djinn
{
    
struct Velocity : public DimensionalMixin<Velocity>, public Component
{
    using DimensionalMixin<Velocity>::DimensionalMixin;
};

struct Acceleration : public DimensionalMixin<Acceleration>, public Component
{
    using DimensionalMixin<Acceleration>::DimensionalMixin;
};

inline Position operator*(const Velocity& lhs, const TimeDuration& rhs)
{
    return Position(
        lhs.x_ * rhs.s_,
        lhs.y_ * rhs.s_,
        lhs.z_ * rhs.s_
    );
}
inline Position operator*(const TimeDuration& lhs, const Velocity& rhs)
{
    return rhs * lhs;
}

inline Velocity operator*(const Acceleration& lhs, const TimeDuration& rhs)
{
    return Velocity(
        lhs.x_ * rhs.s_,
        lhs.y_ * rhs.s_,
        lhs.z_ * rhs.s_
    );
}
inline Velocity operator*(const TimeDuration& lhs, const Acceleration& rhs)
{
    return rhs * lhs;
}

}