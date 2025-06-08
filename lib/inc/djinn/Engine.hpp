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
        systems_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return dynamic_cast<T*>(systems_.back().get());
    }

    void input();

    void update(const TimeDuration& deltaTime);

    void render();
};

} // namespace djinn