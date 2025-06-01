#include "djinn/components/PhysicsComponents.hpp"

using namespace djinn;

Velocity::Velocity(double sx, double sy, double sz):
    scomponents_{sx, sy, sz},
    sx_(scomponents_[0]),
    sy_(scomponents_[1]),
    sz_(scomponents_[2])
{

}

Velocity::Velocity(const Velocity& other):
    Velocity(other.sx_, other.sy_, other.sz_)
{

}

Position Velocity::operator*(const Time& other) const
{
    return Position(
        sx_ * other.s_,
        sy_ * other.s_,
        sz_ * other.s_
    );
}