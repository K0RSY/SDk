#include <iostream>
#include <vector>
#include <filesystem>
#include <lua5.3/lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include "tools.hpp"

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

    static inline vector<string> get_entities()
    {
        vector<string> result;
        for (string& addon : addons)
            for (auto& file : filesystem::directory_iterator("./addons/" + addon + "/world/entities"))
                if (file.is_directory())
                    result.push_back(addon + ":" + file.path().filename().string());
        return result;
    }

public:
    // Variables
    static inline vector<string> addons;
    static inline vector<string> loaded_entities;
    static inline lua_State* L = luaL_newstate();

    // Temp funcions
    static inline void print()
    {
        for (auto i: addons)
            cout << i << ' ';
        cout << endl;
        
        for (auto i: loaded_entities)
            cout << i << ' ';
        cout << endl;
    }

    // Lua methods call
    static inline void run_resource_method(string category, string type, string resource, string method)
    {   
        vector<string> splitted_resource = Tools::split_string(resource, ':');
        string path = "./addons/" + splitted_resource[0] + "/" + category + "/" + type + "/" + splitted_resource[1] + "/" + method + ".lua";
        luaL_dofile(L, path.c_str());
    }

    // Init func
    static inline void init()
    {
        luaL_openlibs(L);

        // Expose functions to lua
        getGlobalNamespace(L)
            .beginNamespace("engine")
                .addFunction("print", print)
            .endNamespace();
        
        lua_pcall(L, 0, 0, 0);

        load_resources();
    }
};