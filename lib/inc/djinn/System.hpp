#pragma once

#include <memory>
#include <vector>

namespace djinn
{

class EntityManager;
class TimeDuration;

class System;

typedef std::vector<std::unique_ptr<System>> SystemVec;

typedef size_t SystemId;

template<typename T>
inline SystemId getSystemTypeId()
{
    static const char id = 0;
    return reinterpret_cast<SystemId>(&id);
}

typedef std::vector<SystemId> DependencyVec;

class System
{
protected:
    EntityManager& manager_;

    DependencyVec dependencies_;

    // protected constructor to disallow construction of this base class
    System(EntityManager& manager);

    template<typename... Deps>
    void addDependencies()
    {
        (dependencies_.push_back(getSystemTypeId<Deps>()), ...);
    }

public:

    virtual ~System() = default;

    const DependencyVec& getDependencies() const;

    virtual void input() { /* no input processing by default */ }

    virtual void update(const TimeDuration& deltaTime) { /* no updating by default */ }

    virtual void render() { /* no rendering by default */ }
};

} // namespace djinn