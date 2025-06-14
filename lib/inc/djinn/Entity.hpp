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
inline EntityId getEntityTypeId()
{
    static const char id = 0;
    return reinterpret_cast<EntityId>(&id);
}

class Entity
{
private:
    ComponentMap components_;

public:
    template<typename T, typename... Args>
    inline T* addComponent(Args&&... args)
    {
        static_assert(std::is_base_of<Component, T>::value, "Template parameter must be of Component type");
        components_[getComponentTypeId<T>()] = std::make_unique<T>(std::forward<Args>(args)...);
        return dynamic_cast<T*>(components_[getComponentTypeId<T>()].get());
    }

    template<typename T>
    inline T* getComponent()
    {
        ComponentMap::iterator comp = components_.find(getComponentTypeId<T>());

        if (comp != components_.end())
        {
            return dynamic_cast<T*>(comp->second.get());
        }

        return nullptr;
    }

    template<typename T>
    inline void removeComponent()
    {
        components_.erase(getComponentTypeId<T>());
    }

    template<typename T>
    inline bool hasComponent()
    {
        return components_.find(getComponentTypeId<T>()) != components_.end();
    }
};

class EntityManager
{
protected:
    EntityVec entities_;

public:
    virtual ~EntityManager() = default;

    template<typename T, typename... Args>
    inline T* addEntity(Args&&... args)
    {
        static_assert(std::is_base_of<Entity, T>::value, "Template parameter must be of Entity type");
        entities_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return entities_.back().get();
    }

    template<typename... Components>
    inline void forFirstWith(EntityComponentFn<Components...>& fn)
    {
        EntityVec::iterator e_iter = entities_.begin();

        while (e_iter != entities_.end() && !(e_iter->get()->hasComponent<Components>() && ...))
            ++e_iter;

        if (e_iter != entities_.end())
        {
            Entity* e = e_iter->get();
            fn(*e, *(e->getComponent<Components>()) ...);
        }
    }

    template<typename... Components>
    inline void forEachWith(EntityComponentFn<Components...>& fn)
    {
        for (EntityVec::iterator e_iter = entities_.begin(); e_iter != entities_.end(); ++e_iter)
        {
            Entity* e = e_iter->get();
            if ((e->hasComponent<Components>() && ...))
            {
                fn(*e, *(e->getComponent<Components>())...);
            }
        }
    }
};

} // namespace djinn