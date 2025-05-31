#pragma once

#include "djinn/Component.hpp"

// TODO define operator + for adding another position

namespace djinn
{

struct Position : public Component
{
    template<typename... Args>
    Position(Args... args);
};

}