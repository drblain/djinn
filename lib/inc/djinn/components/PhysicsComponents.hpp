#pragma once

#include <array>

#include "djinn/Component.hpp"
#include "djinn/components/SpatialComponents.hpp"

// TODO define operator * for multiplying by a time and giving a position

namespace djinn
{

struct Time : public Component
{
    double s_;
};

struct Velocity : public Component
{
    std::array<double, 3> scomponents_;
    double& sx_;
    double& sy_;
    double& sz_;

    Velocity(double sx, double sy, double sz);
    Velocity(const Velocity& other);

    Position operator*(const Time& other) const;
};

}