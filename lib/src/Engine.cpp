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

void Engine::run()
{
    // TODO
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