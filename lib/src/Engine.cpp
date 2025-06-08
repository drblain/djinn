#include <iostream>

#include "djinn/Engine.hpp"
#include "djinn/System.hpp"
#include "djinn/Time.hpp"

using namespace djinn;

Engine::Engine():
    stopped_(false)
{

}

Engine::~Engine()
{
    
}

void Engine::run()
{
    // TODO temp calculation of tick speed
    const double fps(60.0);
    const TimeDuration frame_dur{1.0/fps};
    const TimeDuration tick_dur{frame_dur};

    const uint8_t max_updates_before_throttle(5);

    TimeStamp t_start;
    TimeDuration t_accum{0};

    while (!stopped_)
    {
        TimeStamp t_frame;
        TimeDuration t_delta = t_frame - t_start;
        t_start = t_frame;

        t_accum += t_delta;

        input();

        uint8_t num_updates(0);
        while (t_accum > tick_dur)
        {
            // update
            update(tick_dur);
            t_accum -= tick_dur;
            ++num_updates;
        }

        // render as often as possible, unless updates are suffering
        if (num_updates < max_updates_before_throttle)
            render();
    }
}

void Engine::stop()
{
    stopped_ = true;
}

void Engine::input()
{
    for (SystemVec::iterator s_iter = systems_.begin(); s_iter != systems_.end(); ++s_iter)
    {
        s_iter->get()->input();
    }
}

void Engine::update(const TimeDuration& deltaTime)
{
    for (SystemVec::iterator s_iter = systems_.begin(); s_iter != systems_.end(); ++s_iter)
    {
        s_iter->get()->update(deltaTime);
    }
}

void Engine::render()
{
    for (SystemVec::iterator s_iter = systems_.begin(); s_iter != systems_.end(); ++s_iter)
    {
        s_iter->get()->render();
    }
}