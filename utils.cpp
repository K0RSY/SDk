#include <iostream>
#include <vector>
#include <filesystem>

#pragma once

using namespace std;

class Utils
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