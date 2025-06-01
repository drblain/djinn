#pragma once

#include <memory>
#include <vector>

#include "djinn/Entity.hpp"

namespace djinn
{

class System;

typedef std::vector<std::unique_ptr<System>> SystemVec;

class System
{
protected:
    EntityManager& manager_;

public:
    System(EntityManager& manager);

    virtual ~System() = default;

    virtual void update() = 0;

    inline virtual void render() { /* no rendering by default */ }
};

} // namespace djinn