#include <cassert>
#include <iostream>

#include "djinn/components/SpatialComponents.hpp"
#include "djinn/components/PhysicsComponents.hpp"
#include "djinn/Engine.hpp"
#include "djinn/Entity.hpp"
#include "djinn/System.hpp"

class PrintPositionSystem : public djinn::System
{
public:
    PrintPositionSystem(djinn::EntityManager& em):
        System(em)
    {}

    void render()
    {
        djinn::EntityComponentFn<djinn::Position> fn = [](djinn::Entity& e, djinn::Position& p) {
            std::cout << "PrintPositionSystem: &e: " << &e << ", &p: " << &p << "\n";
        };

        manager_.forEachWith<djinn::Position>(fn);
    }
};

class PrintVelocitySystem : public djinn::System
{
public:
    PrintVelocitySystem(djinn::EntityManager& em):
        System(em)
    {}

    void render()
    {
        djinn::EntityComponentFn<djinn::Velocity> fn = [](djinn::Entity& e, djinn::Velocity& v) {
            std::cout << "PrintVelocitySystem: &e: " << &e << ", &v: " << &v << "\n";
        };

        manager_.forEachWith<djinn::Velocity>(fn);
    }
};

int main(int argc, char* argv[])
{
    djinn::Engine ng;
    djinn::Entity* e1 = ng.addEntity<djinn::Entity>();
    djinn::Entity* e2 = ng.addEntity<djinn::Entity>();
    djinn::Entity* e3 = ng.addEntity<djinn::Entity>();

    e1->addComponent<djinn::Position>(1, 2, 3);
    e1->addComponent<djinn::Velocity>(1, 2, 3);

    e2->addComponent<djinn::Position>(2, 3, 4);

    e3->addComponent<djinn::Scale>(1, 1, 2);
    e3->addComponent<djinn::Velocity>(1, 2, 3);

    PrintPositionSystem* pps = ng.addSystem<PrintPositionSystem>(ng);
    PrintVelocitySystem* pvs = ng.addSystem<PrintVelocitySystem>(ng);

    ng.render();

    return 0;
}