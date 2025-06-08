#pragma once

#include "djinn/System.hpp"

namespace djinn
{

class RenderSystem: public System
{
public:
    RenderSystem(EntityManager& manager):
        System(manager)
    {}

    void render() override;
};

}