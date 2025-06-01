#pragma once

#include <array>

#include "djinn/Component.hpp"

namespace djinn
{

struct Scale : public Component
{
    std::array<double, 3> scales_;
    double& hx_;
    double& hy_;
    double& hz_;

    Scale(double hx, double hy, double hz);
    Scale(const Scale& other);
};

struct Position : public Component
{
    std::array<double, 3> coords_;
    double& x_;
    double& y_;
    double& z_;

    Position(double x, double y, double z);
    Position(const Position& other);

    Position operator+(const Position& other) const;
    Position operator-(const Position& other) const;
    Position operator*(const Scale& other) const;
};

}