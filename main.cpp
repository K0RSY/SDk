#include "engine.cpp"
#include "world.cpp"

int main(int argc, char const *argv[])
{
    Engine::init();
    World::init();

    Engine::run_resource_method("world", "entities", "test:random_entity", "tick");
    return 0;
}
