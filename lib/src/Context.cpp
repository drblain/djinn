#include "djinn/Context.hpp"

using namespace djinn;

Context::Context()
{

}

Context* ContextManager::getContext()
{
    return context_.get();
}