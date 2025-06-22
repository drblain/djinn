#include <cassert>
#include <GLFW/glfw3.h>

#include "djinn/contexts/GLFWContext.hpp"

using namespace djinn;

GLFWContext::GLFWContext(GLFWwindow* window):
    window_(window)
{
}

GLFWContextManager::GLFWContextManager()
{
    assert((GLFW_TRUE == glfwInit()) && "Unable to initialize GLFW");
}

GLFWContextManager::~GLFWContextManager()
{
    for(ContextVec::iterator c_iter = contexts_.begin(); c_iter != contexts_.end(); ++c_iter)
    {
        // make sure context is not current
    }

    glfwTerminate();
}

Context* GLFWContextManager::createContext(ContextParams* params)
{
    Context* context = nullptr;
    GLFWContextParams* glfw_params = nullptr;

    assert((glfw_params = dynamic_cast<GLFWContextParams*>(params)) && "ContextParams must be of type GLFWContextParams");

    GLFWwindow* window = 
        glfwCreateWindow(
            glfw_params->width_,
            glfw_params->height_,
            glfw_params->title_.c_str(),
            /* GLFWMonitor */ NULL,
            /* GLFWWindow */ NULL);

    if (window)
    {
        glfwMakeContextCurrent(window);
        // glfwSwapInterval - 1 for vsync, 0 for not
        contexts_.push_back(std::make_unique<GLFWContext>(window));
        context = contexts_.back().get();
    }

    return context;
}