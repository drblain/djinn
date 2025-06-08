#pragma once

#include "djinn/System.hpp"

namespace djinn
{

class InputSystem: public System
{
public:
    InputSystem(EntityManager& manager):
        System(manager)
    {}

    void input() override;
};

}