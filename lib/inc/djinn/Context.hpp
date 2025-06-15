#pragma once

#include <memory>

namespace djinn
{

class Context
{
public:
    virtual ~Context() = default;

    virtual void makeCurrent() = 0;

    virtual void swapBuffers() = 0;
};

class ContextManager
{
public:
    virtual ~ContextManager() = default;

    virtual bool initialize() = 0;

    virtual void pollEvents() = 0;
};

};