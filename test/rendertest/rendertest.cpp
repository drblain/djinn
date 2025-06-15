#include "djinn/Engine.hpp"
#include "djinn/systems/RenderSystem.hpp"

int main(int argc, char* argv[])
{
    djinn::Engine ng;

    ng.addSystem<djinn::RenderSystem>(ng, ng);

    return 0;
}