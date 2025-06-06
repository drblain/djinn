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

    // protected constructor to disallow construction of this base class
    System(EntityManager& manager);

public:

    virtual ~System() = default;

    virtual void input() { /* no input processing by default */ }

    virtual void update() { /* no updating by default */ }

    virtual void render() { /* no rendering by default */ }
};

} // namespace djinn