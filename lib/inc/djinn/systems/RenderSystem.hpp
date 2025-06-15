#pragma once

#include "djinn/Context.hpp"
#include "djinn/Entity.hpp"
#include "djinn/System.hpp"

namespace djinn
{

class RenderSystem: public System
{
private:
    ContextManager& cmanager_;

public:
    RenderSystem(EntityManager& emanager, ContextManager& cmanager):
        System(emanager),
        cmanager_(cmanager)
    {}

    void render() override;
};

}