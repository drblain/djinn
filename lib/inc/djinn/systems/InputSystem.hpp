#pragma once

#include <deque>

#include "djinn/System.hpp"

namespace djinn
{

typedef char KeyT;

class InputSystem: public System
{
private:
    std::deque<KeyT> input_sequence_;

    KeyT pollInputs();

public:
    InputSystem(EntityManager& manager):
        System(manager)
    {}

    void input() override;
};

}