#pragma once

#include <cassert>

#include "djinn/Context.hpp"
#include "djinn/Entity.hpp"
#include "djinn/System.hpp"

namespace djinn
{

class TimeDuration;

class Engine : public EntityManager, public ContextManager
{
private:
    SystemVec systems_;
    double tick_rate_;
    uint8_t updates_before_throttle_;
    bool stopped_;

public:
    Engine(double tick_rate = 60.0, uint8_t updates_before_throttle = 5);

    ~Engine();

    void run();

    void stop();

    // add a system to the engine. Assumes no cyclic dependencies exist
    template<typename T, typename... Args>
    inline T* addSystem(Args&&... args)
    {
        static_assert(std::is_base_of<System, T>::value, "Template parameter must be of System type");

        SystemVec::iterator insert_pos = systems_.end();

        for (SystemVec::iterator sys_iter = systems_.begin(); sys_iter != systems_.end(); ++sys_iter)
        {
            const DependencyVec& deps((*sys_iter)->getDependencies());

            if(std::find(deps.begin(), deps.end(), getSystemTypeId<T>()) != deps.end())
            {
                insert_pos = sys_iter;
            }
        }

        SystemVec::iterator sys_elem = systems_.insert(insert_pos, std::make_unique<T>(std::forward<Args>(args)...));
        return dynamic_cast<T*>(sys_elem->get());
    }

    void input();

    void update(const TimeDuration& deltaTime);

    void render();
};

} // namespace djinn