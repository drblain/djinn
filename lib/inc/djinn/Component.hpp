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
ComponentId getComponentTypeId();

class Component
{
public:
    virtual ~Component() = default;
};

} // namespace djinn