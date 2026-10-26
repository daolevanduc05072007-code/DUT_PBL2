#include "Level.h"

Level::Level()
{
    // Adapted from completed user-created levels in Graphite.Unity.Sokoban.
    LevelData =
    {
        {
            "#######",
            "#     #",
            "# @$ .#",
            "#     #",
            "#######"
        },
        {
            "########",
            "### .###",
            "### $###",
            "#      #",
            "# @#.$ #",
            "#      #",
            "###$ ###",
            "###. ###",
            "########"
        },
        {
            "########",
            "###  ###",
            "##.  .##",
            "#  $$  #",
            "#   $  #",
            "# @    #",
            "##   .##",
            "###  ###",
            "########"
        },
        {
            "########",
            "##.##.##",
            "# $    #",
            "#  #   #",
            "# @  $ #",
            "#  ### #",
            "########"
        }
    };
}

int Level::GetSizeLevel() const
{
    return static_cast<int>(LevelData.size());
}

vector<string>& Level::GetLevel(int Index)
{
    return LevelData[Index];
}
