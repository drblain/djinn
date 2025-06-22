#pragma once

#include <memory>
#include <vector>

namespace djinn
{

class Context;

typedef std::vector<std::unique_ptr<Context>> ContextVec;

struct ContextParams
{
    virtual ~ContextParams() = default;
};

class Context
{
public:
    virtual ~Context() = default;

    virtual void pollEvents() = 0;

    virtual void makeCurrent() = 0;

    virtual void swapBuffers() = 0;

    virtual bool shouldClose() = 0;
};

class ContextManager
{
protected:
    ContextVec contexts_;

public:
    virtual ~ContextManager() = default;

    virtual Context* createContext(ContextParams* params) = 0;

    virtual void pollAllEvents() = 0;
};

};