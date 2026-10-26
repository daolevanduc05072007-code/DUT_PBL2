#pragma once
#include <vector>
#include <string>

using namespace std;

class Level
{
    private:
        vector<vector<string>> LevelData;

    public:
        Level();
        int GetSizeLevel() const;
        vector<string>& GetLevel(int Index);

};