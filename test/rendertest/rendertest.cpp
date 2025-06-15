#include "djinn/Engine.hpp"
#include "djinn/contexts/GLFWContext.hpp"
#include "djinn/systems/RenderSystem.hpp"

int main(int argc, char* argv[])
{
    djinn::Engine ng;
    djinn::GLFWContextManager* cm =
        ng.addContextManager<djinn::GLFWContextManager>();

    if (!cm->init())
        exit(1);

    ng.addSystem<djinn::RenderSystem>(ng, *cm);

    return 0;
}