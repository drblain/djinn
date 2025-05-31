#include "djinn/Component.hpp"

using namespace djinn;

template<typename T>
ComponentId getComponentTypeId()
{
    static const char id;
    return reinterpret_cast<ComponentId>(&id);
}