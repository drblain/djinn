#include "djinn/components/SpatialComponents.hpp"

using namespace djinn;

Scale::Scale(double hx, double hy, double hz):
    scales_{hx, hy, hz},
    hx_(scales_[0]),
    hy_(scales_[1]),
    hz_(scales_[2])
{

}

Scale::Scale(const Scale& other):
    Scale(other.hx_, other.hy_, other.hz_)
{
    
}

Position::Position(double x, double y, double z):
    coords_{x, y, z},
    x_(coords_[0]),
    y_(coords_[1]),
    z_(coords_[2])
{

}

Position::Position(const Position& other):
    Position(other.x_, other.y_, other.z_)
{

}

Position Position::operator+(const Position& other) const
{
    Position result(*this);
    result.x_ += other.x_;
    result.y_ += other.y_;
    result.z_ += other.z_;
    return result;
}

Position Position::operator-(const Position& other) const
{
    Position result(*this);
    result.x_ -= other.x_;
    result.y_ -= other.y_;
    result.z_ -= other.z_;
    return result;
}

Position Position::operator*(const Scale& other) const
{
    Position result(*this);
    result.x_ *= other.hx_;
    result.y_ *= other.hy_;
    result.z_ *= other.hz_;
    return result;
}