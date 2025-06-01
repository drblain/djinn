#include <iostream>

#include "djinn/components/SpatialComponents.hpp"
#include "djinn/components/PhysicsComponents.hpp"
#include "djinn/Engine.hpp"
#include "djinn/Entity.hpp"

int main(int argc, char* argv[])
{
    djinn::Engine ng;
    djinn::Entity* e1 = ng.addEntity<djinn::Entity>();
    djinn::Entity* e2 = ng.addEntity<djinn::Entity>();
    djinn::Entity* e3 = ng.addEntity<djinn::Entity>();

    e1->addComponent<djinn::Position>();
    e1->addComponent<djinn::Velocity>();

    e2->addComponent<djinn::Position>();

    e3->addComponent<djinn::Scale>();
    e3->addComponent<djinn::Velocity>();

    std::cout << "Hello world!" << std::endl;
    return 0;
}