#pragma once

#include <memory>

namespace djinn
{

class Context
{
public:
    virtual ~Context() = default;
};

class ContextManager
{
protected:
    std::unique_ptr<Context> context_;

public:
    virtual ~ContextManager() = default;

    virtual bool init() = 0;

    template <typename T, typename... Args>
    inline T* addContext(Args&&... args)
    {
        static_assert(std::is_base_of<Context, T>::value, "Template parameter must be of Context type");
        context_ = std::make_unique<T>(std::forward<Args>(args)...);
        return dynamic_cast<T*>(context_.get());
    }

    virtual Context* getContext()
    {
        return context_.get();
    }
};

};