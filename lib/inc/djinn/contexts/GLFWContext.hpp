#pragma once

#include <string>

#include "djinn/Context.hpp"

class GLFWwindow;

namespace djinn
{

struct GLFWContextParams : public ContextParams
{
    int width_;
    int height_;
    std::string title_;
};

class GLFWContext : public Context
{
private:
    GLFWwindow* window_;

public:
    GLFWContext(GLFWwindow* window);

    ~GLFWContext();

    void pollEvents() override;

    void makeCurrent() override;

    void swapBuffers() override;

    bool shouldClose() override;


};

class GLFWContextManager : public ContextManager
{
public:
    GLFWContextManager();

    ~GLFWContextManager();

    Context* createContext(ContextParams* params) override;

    void pollAllEvents() override;
};

};