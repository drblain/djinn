#include "djinn/System.hpp"

using namespace djinn;

System::System(EntityManager& manager):
    emanager_(manager)
{

}

const DependencyVec& System::getDependencies() const
{
    return dependencies_;
}