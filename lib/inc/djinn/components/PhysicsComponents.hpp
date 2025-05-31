#pragma once

#include "djinn/Component.hpp"

// TODO define operator * for multiplying by a time and giving a position

namespace djinn
{

struct Velocity : public Component
{
    template<typename... Args>
    Velocity(Args... args);

    /* Position operator*(Time t) */
};

}