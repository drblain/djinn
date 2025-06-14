#pragma once

#include "djinn/Component.hpp"

namespace djinn
{

struct Camera : public Component
{
    size_t width_;
    size_t height_;
    double fov_;
};

};