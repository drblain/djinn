#pragma once

#include "djinn/Entity.hpp"
#include "djinn/System.hpp"

namespace djinn
{

class TimeDuration;

class Engine : public EntityManager
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

    template<typename T, typename... Args>
    inline T* addSystem(Args&&... args)
    {
        static_assert(std::is_base_of<System, T>::value, "Template parameter must be of System type");
        std::unique_ptr<T> new_sys = std::make_unique<T>(std::forward<Args>(args)...);
        const DependencyVec& new_deps(new_sys->getDependencies());

        SystemVec::iterator after_pos = systems_.end();

        for (SystemVec::iterator sys_iter = systems_.begin(); sys_iter != systems_.end(); ++sys_iter)
        {
            const DependencyVec& deps((*sys_iter)->getDependencies());

            if(std::find(deps.begin(), deps.end(); getSystemTypeId<T>()) != deps.end())
            {
                after_pos = sys_iter;
            }
        }

        SystemVec::iterator sys_elem = systems_.insert(after_pos, std::move(new_sys));
        return dynamic_cast<T*>(sys_elem->get());
    }

    void input();

    void update(const TimeDuration& deltaTime);

    void render();
};

} // namespace djinn