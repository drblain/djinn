#pragma once

#include "djinn/System.hpp"

namespace djinn
{

class BehaviorSystem: public System
{
public:
    BehaviorSystem(EntityManager& manager):
        System(manager)
    {}

    void update(const TimeDuration& deltaTime) override;
};

}