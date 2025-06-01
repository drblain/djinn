#pragma once

#include <cstddef>
#include <memory>
#include <unordered_map>

namespace djinn
{

class Component;

typedef unsigned long long Tick;
typedef size_t ComponentId;
typedef std::unordered_map<ComponentId, std::unique_ptr<Component>> ComponentMap;

template<typename T>
inline ComponentId getComponentTypeId()
{
    static const char id = 0;
    return reinterpret_cast<ComponentId>(&id);
}

class Component
{
public:
    virtual ~Component() = default;
};

} // namespace djinn