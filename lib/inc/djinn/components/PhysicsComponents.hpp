#pragma once

#include <array>

#include "djinn/Time.hpp"
#include "djinn/Component.hpp"
#include "djinn/components/SpatialComponents.hpp"

namespace djinn
{
    
struct Velocity : public Component
{
    double sx_;
    double sy_;
    double sz_;

    Velocity(double sx, double sy, double sz):
        sx_(sx), sy_(sy), sz_(sz)
    {}
};

Position operator*(const Velocity& lhs, const TimeDuration& rhs)
{
    return Position(
        lhs.sx_ * rhs.s_,
        lhs.sy_ * rhs.s_,
        lhs.sz_ * rhs.s_
    );
}

}