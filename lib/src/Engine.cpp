#include <memory>
#include <type_traits>

#include "djinn/Engine.hpp"

using namespace djinn;

template<typename T, typename... Args>
T* Engine::addSystem(Args... args)
{
    static_assert(std::is_base_of<System, T>::value, "Template parameter must be of System type");
    systems_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    return systems_.back().get();
}