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

    void run();

    template<typename T, typename... Args>
    inline T* addSystem(Args&&... args)
    {
        static_assert(std::is_base_of<System, T>::value, "Template parameter must be of System type");
        systems_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return dynamic_cast<T*>(systems_.back().get());
    }

    void input();

    void update();

    void render();
};

} // namespace djinn