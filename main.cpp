#include "engine.hpp"

int main(int argc, char const *argv[])
{
    Engine::init();
    Engine::run_resource_method("world", "entities", "test:random_entity", "tick");
    return 0;
}
