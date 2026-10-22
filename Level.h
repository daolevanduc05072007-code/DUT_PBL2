#pragma once
#include <vector>
#include <string>

using namespace std;

class Level
{
    private:
        vector< vector<string> > data;

    public:
        Level();
        int GetSizeLevel() const;
        vector<string> &get(int index);

};