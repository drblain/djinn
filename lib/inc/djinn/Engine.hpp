#pragma once

#include "djinn/Entity.hpp"
#include "djinn/System.hpp"

namespace djinn
{

class Engine : public EntityManager
{
private:
    SystemVec systems_;

public:
    Engine();

    ~Engine();

    template<typename T, typename... Args>
    T* addSystem(Args... args);
};

} // namespace djinn