#include <iostream>
#include <vector>
#include <filesystem>

using namespace std;

class Engine
{
public:
    // Variables
    vector<string> addons;
    vector<string> loaded_entities;

    // Functions
    void load_addons()
    {
        addons = get_addons();
        loaded_entities = get_entities();
    }

    vector<string> get_addons()
    {
        vector<string> result;
        for(auto& file : filesystem::directory_iterator("./addons")) 
            if (file.is_directory())
                result.push_back(file.path().filename().string());
        return result;
    }

    vector<string> get_entities()
    {
        vector<string> result;
        for(string& addon : addons)
            for(auto& file : filesystem::directory_iterator("./addons/" + addon + "/world/entities"))
                if (file.path().extension().string() == ".json")
                    result.push_back(file.path().stem().string());
        return result;
    }

    void print()
    {
        for (auto i: addons)
            cout << i << ' ';
        cout << endl;
        
        for (auto i: loaded_entities)
            cout << i << ' ';
        cout << endl;
    }

    // Init class
    Engine() {
        load_addons();
    }
};