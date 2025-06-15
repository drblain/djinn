#include <GLFW/glfw3.h>

#include "djinn/contexts/GLFWContext.hpp"

using namespace djinn;

bool GLFWContextManager::init_ = false;

bool GLFWContextManager::init()
{
    if (!init_ || (0 != glfwInit()))
        return false;

    Context* c = addContext<GLFWContext>();

    return nullptr != c;
}