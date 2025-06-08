#include "djinn/System.hpp"

using namespace djinn;

System::System(EntityManager& manager):
    manager_(manager)
{

}

const DependencyVec& System::getDependencies() const
{
    return dependencies_;
}