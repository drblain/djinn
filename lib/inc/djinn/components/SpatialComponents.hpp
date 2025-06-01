#pragma once

#include <array>

#include "djinn/Component.hpp"

namespace djinn
{

struct Scale : public Component
{
    double hx_;
    double hy_;
    double hz_;

    Scale(double h):
        hx_(h), hy_(h), hz_(h)
    {}
    Scale(double hx, double hy, double hz):
        hx_(hx), hy_(hy), hz_(hz)
    {}
};

struct Position : public Component
{
    double x_;
    double y_;
    double z_;

    Position(double x, double y, double z):
        x_(x), y_(y), z_(z)
    {}
};

Position operator+(const Position& lhs, const Position& rhs)
{
    return Position(
        lhs.x_ + rhs.x_,
        lhs.y_ + rhs.y_,
        lhs.z_ + rhs.z_
    );
}

Position operator-(const Position& lhs, const Position& rhs)
{
    return Position(
        lhs.x_ - rhs.x_,
        lhs.y_ - rhs.y_,
        lhs.z_ - rhs.z_
    );
}

Position operator*(const Position& lhs, const Scale& rhs)
{
    return Position(
        lhs.x_ * rhs.hx_,
        lhs.y_ * rhs.hy_,
        lhs.z_ * rhs.hz_
    );
}

}