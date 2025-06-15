#pragma once

#include "djinn/Context.hpp"

class GLFWwindow;

namespace djinn
{

class GLFWContext : public Context
{
private:
    std::unique_ptr<GLFWwindow> window_;

public:
    GLFWContext();

    ~GLFWContext();

    void makeCurrent() override;

    void swapBuffers() override;

};

class GLFWContextManager : public ContextManager
{
private:
    bool init_;
    GLFWContext* context_;

public:
    GLFWContextManager();

    ~GLFWContextManager();

    bool initialize() override;

    void pollEvents() override;

};

};