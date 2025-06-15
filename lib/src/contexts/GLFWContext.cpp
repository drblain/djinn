#include <GLFW/glfw3.h>

#include "djinn/contexts/GLFWContext.hpp"

using namespace djinn;

GLFWContext::GLFWContext()
{
    /* initialize window_ with glfwCreateWindow */
}

GLFWContext::~GLFWContext()
{
    glfwDestroyWindow(window_.get());
}

void GLFWContext::makeCurrent()
{
    glfwMakeContextCurrent(window_.get());
}

void GLFWContext::swapBuffers()
{
    glfwSwapBuffers(window_.get());
}

GLFWContextManager::GLFWContextManager():
    init_(false),
    context_(nullptr)
{

}

GLFWContextManager::~GLFWContextManager()
{
    if (context_)
        delete context_;
        context_ = nullptr;

    if (init_)
        glfwTerminate();
}

bool GLFWContextManager::initialize()
{
    if (!init_)
        init_ = 0 == glfwInit();

    if (init_)
        context_ = new GLFWContext();

    return init_;
}

void GLFWContextManager::pollEvents()
{
    glfwPollEvents();
}