#include <cassert>
#include <iostream>

#include "djinn/components/SpatialComponents.hpp"
#include "djinn/components/PhysicsComponents.hpp"
#include "djinn/Engine.hpp"
#include "djinn/Entity.hpp"
#include "djinn/System.hpp"
#include "djinn/Time.hpp"

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

        emanager_.forEachWith<djinn::Velocity>(fn);
    }
};

class PrintPositionSystem : public djinn::System
{
public:
    PrintPositionSystem(djinn::EntityManager& em):
        System(em)
    {
        // Mimic position depending on changes from velocity
        addDependencies<PrintVelocitySystem>();
    }

    void render()
    {
        djinn::EntityComponentFn<djinn::Position> fn = [](djinn::Entity& e, djinn::Position& p) {
            std::cout << "PrintPositionSystem: &e: " << &e << ", &p: " << &p << "\n";
        };

        emanager_.forEachWith<djinn::Position>(fn);
    }
};

int main(void)
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

    (void)ng.addSystem<PrintPositionSystem>(ng);
    (void)ng.addSystem<PrintVelocitySystem>(ng);

    ng.render();

    return 0;
}