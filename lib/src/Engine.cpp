#include <memory>
#include <type_traits>

#include "djinn/Engine.hpp"
#include "djinn/System.hpp"

using namespace djinn;

Engine::Engine()
{

}

Engine::~Engine()
{
    
}

template<typename T, typename... Args>
T* Engine::addSystem(Args... args)
{
    static_assert(std::is_base_of<System, T>::value, "Template parameter must be of System type");
    systems_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    return systems_.back().get();
}

void Engine::update()
{
    for (SystemVec::iterator s_iter = systems_.begin(); s_iter != systems_.end(); ++s_iter)
    {
        s_iter->get()->update();
    }
}

void Engine::render()
{
    for (SystemVec::iterator s_iter = systems_.begin(); s_iter != systems_.end(); ++s_iter)
    {
        s_iter->get()->render();
    }
}