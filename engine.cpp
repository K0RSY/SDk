#include <iostream>
#include <vector>
#include <filesystem>
#include <lua5.3/lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include "utils.cpp"

#pragma once

using namespace std;
using namespace luabridge;

class Engine
{
private:
    // Resource loading functions
    static inline void load_resources()
    {
        addons = get_addons();
        loaded_entities = get_entities();
    }

    static inline vector<string> get_addons()
    {
        vector<string> result;
        for (auto& file : filesystem::directory_iterator("./addons")) 
            if (file.is_directory())
                result.push_back(file.path().filename().string());
        return result;
    }

    static inline vector<string> get_resources(string type)
    {
        vector<string> result;
        for (string& addon : addons)
            for (auto& file : filesystem::directory_iterator("./addons/" + addon + "/" + type))
                if (file.is_directory())
                    result.push_back(addon + ":" + file.path().filename().string());
        return result;
    }

    static inline vector<string> get_entities()
    {
        return get_resources("entities");
    }

public:
    // Variables
    static inline vector<string> addons;
    static inline vector<string> loaded_entities;
    static inline lua_State* L = luaL_newstate();

    // Lua methods call
    static inline void run_resource_method(string type, string resource, string method)
    {   
        vector<string> splitted_resource = Utils::split_string(resource, ':');
        string path = "./addons/" + splitted_resource[0] + "/" + type + "/" + splitted_resource[1] + "/" + method + ".lua";
        luaL_dofile(L, path.c_str());
    }

    static inline void run_entity_method(string resource, string method)
    {   
        run_resource_method("entities", resource, method);
    }

    // Init func
    static inline void init()
    {
        luaL_openlibs(L);
        lua_pcall(L, 0, 0, 0);

        load_resources();
    }
};