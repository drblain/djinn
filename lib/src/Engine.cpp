#include <iostream>

#include "djinn/Engine.hpp"
#include "djinn/System.hpp"
#include "djinn/Time.hpp"

#include "djinn/sync/Thread.hpp"

using namespace djinn;

Engine::Engine(double tick_rate, uint8_t updates_before_throttle):
    tick_rate_(tick_rate),
    updates_before_throttle_(updates_before_throttle),
    stopped_(false)
{

}

Engine::~Engine()
{
    
}

void Engine::run()
{
    const TimeDuration tick_dur{1.0/tick_rate_};

    TimeStamp t_start;
    TimeDuration t_accum{0};

    ThreadPool* pool = ThreadPool::GetThreadPool();

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
        if (num_updates < updates_before_throttle_)
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