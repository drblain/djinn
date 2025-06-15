#pragma once

#include <memory>

namespace djinn
{

class Context
{
public:
    Context();

    virtual ~Context() = default;
};

class ContextManager
{
protected:
    std::unique_ptr<Context> context_;

public:
    virtual ~ContextManager() = default;

    Context* getContext();
};

};