#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "djinn/Component.hpp"

namespace djinn
{

class Entity;

typedef std::vector<std::unique_ptr<Entity>> EntityVec;

template<typename... Components>
using EntityComponentFn = std::function<void(Entity&, Components&...)>;

typedef size_t EntityId;

template<typename T>
EntityId getEntityTypeId();

class Entity
{
private:
    ComponentMap components_;

public:
    template<typename T, typename... Args>
    T* addComponent(Args... args);

    template<typename T>
    T* getComponent();

    template<typename T>
    bool hasComponent();
};

class EntityManager
{
protected:
    EntityVec entities_;

public:
    virtual ~EntityManager() = default;

    template<typename T, typename... Args>
    T* addEntity(Args... args);

    template<typename... Components>
    void forEachWith(EntityComponentFn<Components...>& fn);
};

} // namespace djinn