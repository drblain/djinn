#include <memory>
#include <type_traits>

#include "djinn/Component.hpp"
#include "djinn/Entity.hpp"

using namespace djinn;

template<typename T>
EntityId getEntityTypeId()
{
    static const char id;
    return reinterpret_cast<EntityId>(&id);
}

template<typename T, typename... Args>
T* Entity::addComponent(Args... args)
{
    static_assert(std::is_base_of<Component, T>::value, "Template parameter must be of Component type");
    components_[getComponentTypeId<T>()] = std::make_unique<T>(std::forward<Args>(args)...);
    return components_[getComponentTypeId<T>()].get();
}

template<typename T>
T* Entity::getComponent()
{
    ComponentMap::iterator comp = components_.find(getComponentTypeId<T>());

    if (comp != components_.end())
    {
        return comp->second.get();
    }

    return nullptr;
}

template<typename T>
bool Entity::hasComponent()
{
    return components_.find(getComponentTypeId<T>()) != components_.end();
}

template<typename T, typename... Args>
T* EntityManager::addEntity(Args... args)
{
    static_assert(std::is_base_of<Entity, T>::value, "Template parameter must be of Entity type");
    entities_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    return entities_.back().get();
}

template<typename... Components>
void EntityManager::forEachWith(EntityComponentFn<Components...>& fn)
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