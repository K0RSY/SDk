#include <iostream>
#include <vector>
#include <filesystem>

using namespace std;

class Tools
{
public:
    static inline vector<string> split_string(string str, char symbol)
    {
        stringstream stream(str);
        string temp;
        vector<string> result;

        while (getline(stream, temp, symbol))
            result.push_back(temp);

        return result;
    }
};