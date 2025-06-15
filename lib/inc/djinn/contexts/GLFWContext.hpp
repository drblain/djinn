#pragma once

#include "djinn/Context.hpp"

namespace djinn
{

class GLFWContext : public Context
{
public:

};

class GLFWContextManager : public ContextManager
{
private:
    static bool init_;

public:
    bool init() override;
};

};