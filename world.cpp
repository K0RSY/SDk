#include <iostream>
#include <vector>
#include <filesystem>
#include <lua5.3/lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include "utils.cpp"
#include "engine.cpp"

#pragma once

using namespace std;
using namespace luabridge;

class World
{
public:
    // Temp funcions
    static inline void print()
    {
        cout << "Yo test" << endl;
    }

    // Init func
    static inline void init()
    {
        // Expose functions to lua
        getGlobalNamespace(Engine::L)
            .beginNamespace("world")
                .addFunction("print", print)
            .endNamespace();
    }
};