#include "djinn/components/InputComponents.hpp"
#include "djinn/components/PhysicsComponents.hpp"

#include "djinn/entities/PlayerEntity.hpp"

using namespace djinn;

Player::Player()
{
    addComponent<PlayerInput>();
    addComponent<Position>();
    addComponent<Velocity>();
    addComponent<Acceleration>();
}